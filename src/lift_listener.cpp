#include <lift_listener.h>
#include <iostream>
#include <limits>
#define START_MES "start_mes"
#define ERR_PLACE_MES "err_place_mes"
#define ENTER_MES "enter_mes"
#define ERR_FLOOR_MES "err_floor_mes"
#define PULT_CALL_MES "pult_call_mes"
#define CAB_CALL_MES "cab_call_mes"
#define ASK_MES "ask_mes"
namespace lift_np {
    lift_listener::lift_listener(size_t fc, const std::unordered_map<std::string, std::string>& txts) : texts(txts),floor_count(fc), stop_sym('q'), pult_sym('p'), cab_sym('c') {
    }
    bool lift_listener::listen() {
        std::cout << texts[START_MES] << std::endl;
        char call_place = 0;
        size_t floor_num = 0;
        while ((call_place = std::cin.get()) != stop_sym) {
            std::cin.ignore(std::numeric_limits <std::streamsize> ::max(), '\n');
            if (call_place != pult_sym && call_place != cab_sym) {
                std::cout << texts[ERR_PLACE_MES] << std::endl;
                continue;
            }
            std::cout << texts[ENTER_MES] << std::endl;
            std::cin >> floor_num;
            std::cin.ignore(std::numeric_limits <std::streamsize> ::max(), '\n');
            if (floor_num <= 0 || floor_num > floor_count) {
                std::cout << texts[ERR_FLOOR_MES] << std::endl;
                continue;
            }
            switch (call_place) {
            case 'p': {
                lift_message msg(floor_num, MESSAGE_TYPE::PULT_CALL);
                this->send(msg);
                std::cout << texts[PULT_CALL_MES] << floor_num << std::endl;
                break;
            }
            case 'c': {
                lift_message msg(floor_num, MESSAGE_TYPE::CABINE_CALL);
                this->send(msg);
                std::cout << texts[CAB_CALL_MES] << floor_num << std::endl;
                break;
            }
            default:
                break;
            }
            std::cout << texts[ASK_MES] << std::endl;
        }
        return true;
    }
}
