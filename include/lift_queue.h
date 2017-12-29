#pragma once
#include <list>
#include <unordered_map>
#include <stdexcept>
namespace lift_np {
    template<class T>
    class lift_queue {
    public:
        T pop();
        void push(const T&);
        bool remove(const T&);
        bool empty();
    private:
        std::unordered_map<T, typename std::list<T>::iterator> additional;
        std::list<T> queue;
    };
    template<class T>
    T lift_queue<T>::pop() {
        T ret;
        if (!queue.empty()) {
            ret = queue.back();
            queue.erase(additional[ret]);
            additional.erase(ret);
        }
        else
            throw std::runtime_error("get from empty");
        return ret;
    }
    template<class T>
    void lift_queue<T>::push(const T& val) {
        if (additional.find(val) == additional.end()) {
            queue.push_front(val);
            additional[val] = queue.begin();
        }
    }
    template<class T>
    bool lift_queue<T>::remove(const T& val) {
        auto find_iter = additional.find(val);
        if (find_iter != additional.end()) {
            queue.erase(find_iter->second);
            additional.erase(find_iter);
            return true;
        }
        return false;
    }
    template<class T>
    bool lift_queue<T>::empty() {
        return additional.empty();
    }
}
