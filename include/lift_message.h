#pragma once
#include <cstdio>
namespace lift_np {
    enum MESSAGE_TYPE { PULT_CALL, CABINE_CALL };
    class lift_message {
    public:
        lift_message(size_t f_num, MESSAGE_TYPE m_type);
        MESSAGE_TYPE get_type() const;
        size_t get_floor() const;
    private:
        size_t floor_num;
        MESSAGE_TYPE message_type;
    };
}
