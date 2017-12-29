#include <lift_message.h>
namespace lift_np {
    lift_message::lift_message(size_t f_num, MESSAGE_TYPE m_type) : floor_num(f_num), message_type(m_type) {}
    MESSAGE_TYPE lift_message::get_type() const {
        return message_type;
    }
    size_t lift_message::get_floor() const {
        return floor_num;
    }
}