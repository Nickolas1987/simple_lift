#pragma once
#include <pubsub.h>
#include <lift_message.h>
namespace lift_np {
    class ilistener : public publisher<lift_message> {
    public:
        virtual bool listen() = 0;
    };
}