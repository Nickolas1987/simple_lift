#include <lift_move_strategy.h>
#include <iostream>
namespace lift_np {
    void lift_move_strategy::run(size_t val) {
        std::cout << "lift now at floor " << val << std::endl;
    }
}