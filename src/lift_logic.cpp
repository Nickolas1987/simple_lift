#include <lift_logic.h>
#include <stdio.h>
#include <getopt.h>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <system_error>
#include <algorithm>
#define MS_MULTI 1000.0
using namespace std;
namespace lift_np{
    lift_logic::lift_logic(){
    }
    bool lift_logic::init(int argc, char* argv[]){
     try{
      //////////Check command line params
      struct option long_opt[] = {
        {"count", 0, 0, 'c'},
        {"height", 0, 0, 'h'},
        {"velocity", 0, 0, 'v'},
        {"time_open", 0, 0, 't'},
        {0,0,0,0}
      };
      int key,optIdx;
      size_t count = 20, start = 1;
      double height = 3.0, velocity = 1.5, time_open = 2.0; 
      while((key = getopt_long(argc, argv, "c::h::v::t::s::", long_opt, &optIdx)) != -1){
       switch(key){
        case 'c':
          count = atoi(optarg);
          break;
        case 'h':
          height = atof(optarg);
          break;
        case 'v':
          velocity = atof(optarg);
          break;
        case 't':
          time_open = atof(optarg);
          break;
        case 's':
          start = atoi(optarg);
          break;
        case '?':
          return false;
        default:
         break;
       }
      }
      if(count < 5 || count > 20)
        return false;
      if(height <= 0)
        return false;
      if(velocity <= 0)
        return false;
      if(time_open <= 0)
        return false;
      //////////////////////Init interface texts
      std::ifstream file("./res/strings.txt");
      std::string line;
      std::unordered_map<std::string, std::string> texts;
      if(!file.is_open())
        return false;
      while(std::getline(file, line)){
         line.erase(std::remove(line.begin(),line.end(),'\r'),line.end());
         size_t pos = line.find(' ');
         if(pos != std::string::npos)
           texts[line.substr(0,pos)] = line.substr(pos + 1);
      }
      file.close();
      ///////////Create objects
      listener = std::make_shared<lift_listener>(count,texts);
      cabine = std::make_shared<lift_cabine>(static_cast<size_t>((height/velocity)*MS_MULTI),start);
      cabine->set_open_door_strategy(std::make_shared<open_door_strategy>());
      cabine->set_close_door_strategy(std::make_shared<close_door_strategy>(static_cast<size_t>(time_open*MS_MULTI)));
      cabine->set_move_strategy(std::make_shared<lift_move_strategy>());
      listener->subscribe(*(cabine.get()));
     }
     catch(std::system_error& e){
       std::cout << e.what() << std::endl;
       return false;
     }
     catch(std::runtime_error& e){
       std::cout << e.what() << std::endl;
       return false;
     }
     catch(...){
       return false;
     }
     return true;
    }
    bool lift_logic::run(){
      try{
        listener->listen();
      }
      catch(std::system_error& e){
       std::cout << e.what() << std::endl;
       return false;
      }
      catch(std::runtime_error& e){
       std::cout << e.what() << std::endl;
       return false;
      }
      catch(...){
        return false;
      }
      return true;
    }
}
