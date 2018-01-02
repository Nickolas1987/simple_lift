#include <restxtreader.h>
#include <stdexcept>
namespace lift_np{
    restxtreader::restxtreader(const std::string& name):file(name){
      if(!file.is_open())
        throw std::runtime_error("can't open file " + name);
      std::string line;
      while(std::getline(file, line)){
         line.erase(std::remove(line.begin(),line.end(),'\r'),line.end());
         size_t pos = line.find(' ');
         if(pos != std::string::npos)
           res[line.substr(0,pos)] = line.substr(pos + 1);
      }
    }
    restxtreader::~restxtreader(){
      file.close();
    }
    std::unordered_map<std::string,std::string> restxtreader::get(){
      return res;
    }
}
