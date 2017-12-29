#include <lift_cabine.h>
#include <system_error>
#include <stdexcept>
#include <iostream>
namespace lift_np {
    lift_cabine::lift_cabine(size_t time_for, size_t start) :time_for_one_floor(time_for), cur_floor(start), target_floor(0) {
        move_future = move_th.start(time_for_one_floor, std::bind(&lift_cabine::move, this));
    }
    lift_cabine::~lift_cabine() {
        move_th.stop();
        move_future.get();
    }
    bool lift_cabine::set_target(bool is_need_clear) { //Set target floor
        std::unique_lock<std::mutex> locker(queue_mut);
        if (!target_floor || is_need_clear) {
            if (!cabine_queue.empty()) {
                target_floor = cabine_queue.pop();
            }
            else if (!pult_queue.empty()) {
                target_floor = pult_queue.pop();
            }
            else {
                target_floor = 0;
                return false;
            }
        }
        return true;
    }
    void lift_cabine::move() {
      try{
        if (!set_target()) // if there is no target, lift are stayed at place
            return;
        std::unique_lock<std::mutex> locker(queue_mut);
        bool is_removed = (cabine_queue.remove(cur_floor) || pult_queue.remove(cur_floor)); //Check if lift visited floors from queue
        locker.unlock();
        bool is_target_floor = (target_floor == cur_floor);
        if (move_action)
            move_action->run(cur_floor);
        if (is_removed || is_target_floor) { // check if lift need open door
            if (open_action)
                open_action->run(cur_floor);
            if (close_action)
                close_action->run(cur_floor);
        }
        if (is_target_floor) { // Set new target
            if (!set_target(true))
                return;
        }
        if (cur_floor < target_floor) {//Move
            ++cur_floor;
        }
        else {
            --cur_floor;
        }
      }
      catch(std::system_error& e){
       std::cout << e.what() << std::endl;
      }
      catch(std::runtime_error& e){
       std::cout << e.what() << std::endl;
      }
      catch(...){
        std::cout << "undefined exception in move function" << std::endl;
      }
    }
    bool lift_cabine::action_on_msg(const publisher<lift_message>& pub, const lift_message& msg) {
        switch (msg.get_type()) {
        case CABINE_CALL: {
            std::unique_lock<std::mutex> locker(queue_mut);
            cabine_queue.push(msg.get_floor());
            break;
        }
        case PULT_CALL: {
            std::unique_lock<std::mutex> locker(queue_mut);
            pult_queue.push(msg.get_floor());
            break;
        }
        default:
            break;
        }
        std::unique_lock<std::mutex> locker(queue_mut);
        if (!target_floor)
            move_th.wakeup();
        return true;
    }
    void lift_cabine::set_open_door_strategy(const std::shared_ptr<istrategy>& val) {
        open_action = val;
    }
    void lift_cabine::set_close_door_strategy(const std::shared_ptr<istrategy>& val) {
        close_action = val;
    }
    void lift_cabine::set_move_strategy(const std::shared_ptr<istrategy>& val) {
        move_action = val;
    }
}
