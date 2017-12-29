#include <lift_listener.h>
#include <iostream>
#include <limits>
namespace lift_np {
    lift_listener::lift_listener(size_t fc, const std::unordered_map<std::string, std::string>& txts) : texts(txts),floor_count(fc), stop_sym('q'), pult_sym('p'), cab_sym('c') {
    }
    bool lift_listener::listen() {
        std::cout << texts["start_mes"] << std::endl;
        char call_place = 0;
        size_t floor_num = 0;
        while ((call_place = std::cin.get()) != stop_sym) {
            std::cin.ignore(std::numeric_limits <std::streamsize> ::max(), '\n');
            if (call_place != pult_sym && call_place != cab_sym) {
                std::cout << texts["err_place_mes"] << std::endl;
                continue;
            }
            std::cout << texts["enter_mes"] << std::endl;
            std::cin >> floor_num;
            std::cin.ignore(std::numeric_limits <std::streamsize> ::max(), '\n');
            if (floor_num <= 0 || floor_num > floor_count) {
                std::cout << texts["err_floor_mes"] << std::endl;
                continue;
            }
            switch (call_place) {
            case 'p': {
                lift_message msg(floor_num, MESSAGE_TYPE::PULT_CALL);
                this->send(msg);
                std::cout << texts["pult_call_mes"] << floor_num << std::endl;
                break;
            }
            case 'c': {
                lift_message msg(floor_num, MESSAGE_TYPE::CABINE_CALL);
                this->send(msg);
                std::cout << texts["cab_call_mes"] << floor_num << std::endl;
                break;
            }
            default:
                break;
            }
            std::cout << texts["ask_mes"] << std::endl;
        }
        return true;
    }
}
