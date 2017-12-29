#include <iostream>
#include <lift_logic.h>
using namespace std;
using namespace lift_np;
int main(int argc, char* argv[]) {
    lift_logic logic;
    if(!logic.init(argc,argv))
        std::cout<< "bad input parametres" <<std::endl;
    if(!logic.run())
        std::cout<< "error in listen process" <<std::endl;
    return 0;
}