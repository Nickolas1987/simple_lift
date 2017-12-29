#pragma once
#include <thread>
#include <chrono>
#include <atomic>
#include <future>
#include <condition_variable>
#include <mutex>
namespace lift_np {
    class later_async_call {
    public:
        later_async_call();
        ~later_async_call();
        template <class F, class... Args>
        std::future<void> start(size_t interval, F&& f, Args&&... args);
        void stop();
        void wakeup();
    private:
        later_async_call(const later_async_call&) = delete;
        later_async_call& operator=(const later_async_call&) = delete;
        std::atomic<bool> cancel_token;
        std::mutex wake_mut;
        std::condition_variable wake_var;
    };
    template <class F, class... Args>
    std::future<void> later_async_call::start(size_t interval, F&& f, Args&&... args){
        cancel_token.store(true);
        auto cb = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
        auto ret = std::async(std::launch::async, [=]() mutable {
            while (cancel_token.load()) {
                //std::this_thread::sleep_for(std::chrono::milliseconds(interval));
                std::chrono::milliseconds msec(interval > 0 ? interval : 0);
                std::unique_lock<std::mutex> locker(wake_mut);
                wake_var.wait_for(locker,msec);
                cb();
            }
        });
        return ret;
    }
}
