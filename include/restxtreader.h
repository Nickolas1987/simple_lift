#pragma once
#include <iresreader.h>
namespace lift_np {
    class restxtreader: public iresreader {
    public:
        restxtreader(const std::string&);
        ~restxtreader();
        virtual std::unordered_map<std::string,std::string> get();
    private:
        restxtreader(const restxtreader&) = delete;
        restxtreader& operator=(const restxtreader&) = delete;
        std::ifstream file;
        std::unoredered_map<std::string,std::string> res;
    };
}