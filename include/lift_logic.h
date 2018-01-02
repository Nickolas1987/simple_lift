#pragma once
#include <later_async_call.h>
#include <pubsub.h>
#include <lift_queue.h>
#include <lift_cabine.h>
#include <lift_listener.h>
#include <open_door_strategy.h>
#include <close_door_strategy.h>
#include <lift_move_strategy.h>
#include <ilistener.h>
#include <iresreader.h>
#include <memory>
namespace lift_np {
    class lift_logic {
    public:
        lift_logic();
        bool init(const std::shared_ptr<iresreader>& reader,int argc, char* argv[]);
        bool run();
    private:
        std::shared_ptr<ilistener> listener;
        std::shared_ptr<ilift_cabine> cabine;
        std::shared_ptr<iresreader> reader;
    };
}
