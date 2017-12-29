#pragma once
#include <cstdio>
namespace lift_np {
    class istrategy {
    public:
        virtual void run(size_t) = 0;
        virtual ~istrategy() {};
    };
}
