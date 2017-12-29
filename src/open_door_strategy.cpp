#include <open_door_strategy.h>
#include <iostream>
namespace lift_np {
    void open_door_strategy::run(size_t val) {
        std::cout << "open door at floor " << val << std::endl;
    }
}
