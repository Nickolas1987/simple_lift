#pragma once
#include <istrategy.h>
namespace lift_np {
    class lift_move_strategy : public istrategy {
    public:
        virtual void run(size_t);
    };
}