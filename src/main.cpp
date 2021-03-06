#include <iostream>
#include <lift_logic.h>
#include <restxtreader.h>
using namespace std;
using namespace lift_np;
int main(int argc, char* argv[]) {
  try{
     lift_logic logic;
     if(!logic.init(std::make_shared<restxtreader>("./res/strings.txt"),argc,argv))
        std::cout<< "bad input parametres" <<std::endl;
     if(!logic.run())
        std::cout<< "error in listen process" <<std::endl;
    }
    catch(std::runtime_error& e){
        std::cout << e.what() <<std::endl;
    }
    catch(...){
        std::cout << "unexpected error" <<std::endl;
    }
    return 0;
}
