#include <open_door_strategy.h>
#include <iostream>
namespace lift_np {
    open_door_strategy::open_door_strategy(const std::string& val):text(val){
    }
    void open_door_strategy::run(size_t val) {
        std::cout << text << val << std::endl;
    }
}
