#pragma once
#include <ilistener.h>
#include <unordered_map>
#include <string>
namespace lift_np {
    class lift_listener : public ilistener {
    public:
        explicit lift_listener(size_t, const std::unordered_map<std::string,std::string>&);
        virtual bool listen();
    private:
        lift_listener(const lift_listener&) = delete;
        lift_listener& operator=(const lift_listener&) = delete;
        std::unordered_map<std::string,std::string> texts;
        size_t floor_count;
        const char stop_sym;
        const char pult_sym;
        const char cab_sym;
    };
}