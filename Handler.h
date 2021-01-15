#ifndef OOP8_HANDLER_H
#define OOP8_HANDLER_H

#include <condition_variable>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <functional>
#include <atomic>
#include <vector>
#include <iostream>
#include <memory>

#include "Figure.h"

class Handler{
public:
private:
    size_t max_count = 0;
    std::mutex mutex;
    std::thread thread;
    std::condition_variable cv;
    std::vector<std::shared_ptr<Figure>> figures;
    std::vector<std::function<void(std::vector<std::shared_ptr<Figure>>&)>> handlers;
public:
    bool running;
    Handler(size_t max_count_);
    ~Handler();
    static void print(Handler* h);
    void add_to_handler(std::function<void(std::vector<std::shared_ptr<Figure>>&)>&& func);
    bool is_full();
    void push(std::shared_ptr<Figure> el);
};

#include "Handler.cpp"
#endif //OOP8_HANDLER_H
