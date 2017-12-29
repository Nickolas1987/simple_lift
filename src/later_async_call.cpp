#include <later_async_call.h>
namespace lift_np {
    later_async_call::later_async_call() :cancel_token(false) {
    }
    later_async_call::~later_async_call() {
        stop();
    }
    void later_async_call::stop() {
        cancel_token.store(false);
    }
    void later_async_call::wakeup() {
        wake_var.notify_one();
    }
}
