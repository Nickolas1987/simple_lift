#pragma once
#include "istrategy.h"
#include <string>
namespace lift_np {
    class close_door_strategy : public istrategy {
    public:
        explicit close_door_strategy(const std::string&,size_t ms);
        virtual void run(size_t);
    private:
        size_t interval;
        std::string text;
    };
}
