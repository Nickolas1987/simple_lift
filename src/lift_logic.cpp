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
      //////////Check command line params
      struct option long_opt[] = {
        {"count", 1, 0, 'c'},
        {"height", 1, 0, 'h'},
        {"velocity", 1, 0, 'v'},
        {"time_open", 1, 0, 't'},
        {"start", 1, 0, 's'},
        {"help", 0, 0, 10},
        {0,0,0,0}
      };
      int key,optIdx;
      size_t count = 20, start = 1;
      double height = 3.0, velocity = 1.5, time_open = 2.0; 
      while((key = getopt_long(argc, argv, "c:h:v:t:s:", long_opt, &optIdx)) != -1){
       switch(key){
        case 'c':{
          if(optarg)
            count = atoi(optarg);
          break;
        }
        case 'h':{
          if(optarg)
            height = atof(optarg);
          break;
        }
        case 'v':{
          if(optarg)
            velocity = atof(optarg);
          break;
        }
        case 't':{
          if(optarg)
            time_open = atof(optarg);
          break;
        }
        case 's':{
          if(optarg)
            start = atoi(optarg);
          break;
        }
        case 10:{
          std::cout << texts["help_str"] << std::endl;
          return true;
        }
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
      ///////////Create objects
      listener = std::make_shared<lift_listener>(count,texts);
      cabine = std::make_shared<lift_cabine>(static_cast<size_t>((height/velocity)*MS_MULTI),start);
      cabine->set_open_door_strategy(std::make_shared<open_door_strategy>(texts["open_door_str"]));
      cabine->set_close_door_strategy(std::make_shared<close_door_strategy>(texts["close_door_str"],static_cast<size_t>(time_open*MS_MULTI)));
      cabine->set_move_strategy(std::make_shared<lift_move_strategy>(texts["lift_move_str"]));
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
        if(listener)
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
