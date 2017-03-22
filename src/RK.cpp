#include "RK.hpp"

using namespace std;

RK::RK() {
    input = new Input(DEFAULT_TIMEOUT, DEFAULT_NB_BUTTONS_USED);
    display = new Display();
    map = new Map();
}

RK::~RK() {
    delete input;
    delete display;
    delete map;
}

int main(int argc, char* args[]) {
    
    cout << "RandomKill - V pre-alpha\n";
    RK rk;
    start();
    return 0;
}
