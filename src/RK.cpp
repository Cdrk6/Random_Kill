#include "RK.hpp"

using namespace std;

RK::RK() {
    controller = new Controller(DEFAULT_TIMEOUT, DEFAULT_NB_BUTTONS_USED);
    display = new Display();
    map = new Map();
}

RK::~RK() {
    delete controller;
    delete display;
    delete map;
}

int main(int argc, char* args[]) {
    
    cout << "RandomKill - V pre-alpha\n";
    RK rk;
    start();
    return 0;
}
