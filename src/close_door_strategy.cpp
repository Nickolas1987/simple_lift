#include <close_door_strategy.h>
#include <iostream>
#include <thread>
#include <chrono>
namespace lift_np {
    close_door_strategy::close_door_strategy(size_t ms): interval(ms){
    }
    void close_door_strategy::run(size_t val) {
        std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        std::cout << "close door at floor " << val << std::endl;
    }
}
