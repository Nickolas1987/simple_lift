#pragma once
#include <istrategy.h>
namespace lift_np {
    class open_door_strategy : public istrategy {
    public:
        virtual void run(size_t);
    };
}
