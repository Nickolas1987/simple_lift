#pragma once
#include <istrategy.h>
#include <string>
namespace lift_np {
    class open_door_strategy : public istrategy {
    public:
        open_door_strategy(const std::string&);
        virtual void run(size_t);
    private:
        std::string text;
    };
}
