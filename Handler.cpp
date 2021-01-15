Handler::Handler(size_t max_count_){
    max_count = max_count_;
    running = true;
    thread = std::thread(print,this);
}

Handler::~Handler(){
    running = false;
    cv.notify_one();
    thread.join();
}

void Handler::print(Handler* h) {
    while(h->running){
        std::unique_lock<std::mutex> ul(h->mutex);
        h->cv.wait(ul,[h](){
            return h->running == false || h->is_full();
        });
        for(auto& el : h->handlers){
            el(h->figures);
        }
        h->figures.clear();
        ul.unlock();
        h->cv.notify_one();
    }
}

void Handler::add_to_handler(std::function<void(std::vector<std::shared_ptr<Figure>>&)>&& func){
    handlers.push_back(func);
}

bool Handler::is_full(){
    return figures.size() == max_count;
}

void Handler::push(std::shared_ptr<Figure> el){
    figures.push_back(el);
    std::unique_lock<std::mutex> ul(mutex);
    if (is_full()){
        cv.notify_one();
        cv.wait(ul,[this](){
            return figures.empty();
        });
    }

}