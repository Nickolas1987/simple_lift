#include <close_door_strategy.h>
#include <iostream>
#include <thread>
#include <chrono>
namespace lift_np {
    close_door_strategy::close_door_strategy(const std::string& val, size_t ms): interval(ms), text(val){
    }
    void close_door_strategy::run(size_t val) {
        std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        std::cout << text << val << std::endl;
    }
}
