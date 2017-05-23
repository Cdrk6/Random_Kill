#include "RK.hpp"

RK::RK() {
    controller = new Controller(DEFAULT_TIMEOUT, DEFAULT_NB_BUTTONS_USED);
    display = new Display();
    map = new Map();
    io = new IO();
}

RK::~RK() {
    delete controller;
    delete display;
    delete map;
    delete io;
}

IO* RK::getIO() {
    return io;
}

int main(int argc, char* args[]) {
    cout << "RandomKill - V pre-alpha" << endl;
    RK rk;
    rk.getIO()->loadImages();
    //start();
    return 0;
}
