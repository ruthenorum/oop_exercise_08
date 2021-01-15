#include <iostream>
#include <string>
#include <cmath>

#include "Handler.h"
#include "Factory.h"

const int ARGUMENT_ERROR = -1;

void menu(){
    std::cout << "menu" << std::endl;
    std::cout << "exit" << std::endl;
    std::cout << "add" << std::endl;
}

int main(int argc, char** argv) {

    if (argc != 2){
        std::cout << "buffer size error" << std::endl;
        return ARGUMENT_ERROR;
    }
    if (std::stol(argv[1]) <= 0){
        std::cout << "buffer size error" << std::endl;
        return ARGUMENT_ERROR;
    }

    const size_t buffer_size = std::stol(argv[1]);

    Handler handler(buffer_size);

    handler.add_to_handler([](std::vector<std::shared_ptr<Figure>>& figures) {
        for (const auto& figure : figures) {
            figure->print(std::cout);
        }
    });

    static int file_index = 0;

    handler.add_to_handler([](std::vector<std::shared_ptr<Figure>>& figures) {
        std::ofstream file(std::to_string(file_index) + ".txt");
        for (const auto& items : figures) {
            items->print(file);
        }
        file.close();
        file_index++;
    });

    menu();
    std::string cmd;
    while (true) {
        std::cin >> cmd;
        if (cmd == "menu") {
            menu();
        } else if (cmd == "exit") {
            break;
        } else if (cmd == "add") {
            handler.push(Factory::figure_create(std::cin));
            std::cout << "was added" << std::endl;
        }
    }
    return 0;
}
