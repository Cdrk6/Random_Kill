#include "RK.hpp"

RK::RK() {
    controller = new Controller(DEFAULT_TIMEOUT, DEFAULT_NB_BUTTONS_USED);
    display = new Display();
    io = new IO(display->getRenderer());
    display->startSDL(io);
}

RK::~RK() {
    delete controller;
    delete io;
    delete display;
}

int main(int argc, char* args[]) {
    cout << "RandomKill - V pre-alpha" << endl;
    RK rk;
    //start();
    return 0;
}
