#include <lift_move_strategy.h>
#include <iostream>
namespace lift_np {
    lift_move_strategy::lift_move_strategy(const std::string& val):text(val){
    }
    void lift_move_strategy::run(size_t val) {
        std::cout << text << val << std::endl;
    }
}
