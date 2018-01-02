#pragma once
#include <unordered_map>
#include <string>
namespace lift_np {
    class iresreader {
    public:
        virtual ~iresreader(){};
        virtual std::unordered_map<std::string,std::string> get() = 0;
    };
}
