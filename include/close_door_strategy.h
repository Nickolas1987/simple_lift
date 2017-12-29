#pragma once
#include "istrategy.h"
namespace lift_np {
    class close_door_strategy : public istrategy {
    public:
        explicit close_door_strategy(size_t ms);
        virtual void run(size_t);
    private:
        size_t interval;
    };
}
