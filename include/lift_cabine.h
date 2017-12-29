#pragma once
#include <istrategy.h>
#include <lift_queue.h>
#include <lift_message.h>
#include <ilift_cabine.h>
#include <mutex>
#include <later_async_call.h>
namespace lift_np {
    class lift_cabine : public ilift_cabine {
    public:
        lift_cabine(size_t velocity, size_t start);
        ~lift_cabine();
        void move();
        bool action_on_msg(const publisher<lift_message>& pub, const lift_message& msg);
        void set_open_door_strategy(const std::shared_ptr<istrategy>&);
        void set_close_door_strategy(const std::shared_ptr<istrategy>&);
        void set_move_strategy(const std::shared_ptr<istrategy>&);
    private:
        lift_cabine(const lift_cabine&) = delete;
        lift_cabine& operator=(const lift_cabine&) = delete;
        bool set_target(bool is_need_clear = false);
        lift_queue<size_t> pult_queue;
        lift_queue<size_t> cabine_queue;
        std::mutex queue_mut;
        size_t time_for_one_floor;
        size_t cur_floor;
        size_t target_floor;
        lift_np::later_async_call move_th;
        std::shared_ptr<istrategy> open_action;
        std::shared_ptr<istrategy> close_action;
        std::shared_ptr<istrategy> move_action;
        std::future<void> move_future;
    };
}
