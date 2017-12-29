#pragma once
#include <pubsub.h>
#include <lift_message.h>
#include <istrategy.h>
#include <memory>
namespace lift_np {
    class ilift_cabine : public subscriber<lift_message> {
    public:
        virtual void move() = 0;
        virtual void set_open_door_strategy(const std::shared_ptr<istrategy>&) = 0;
        virtual void set_close_door_strategy(const std::shared_ptr<istrategy>&) = 0;
        virtual void set_move_strategy(const std::shared_ptr<istrategy>&) = 0;
        virtual ~ilift_cabine() {};
    };
}
