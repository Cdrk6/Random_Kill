#include "RK.hpp"

using namespace std;

RK::RK() {
    Input *input = new Input(DEFAULT_TIMEOUT, DEFAULT_NB_BUTTONS_USED);
    Display *display = new Display();
}

RK::~RK() {
    delete input;
    delete display;
}

int main(int argc, char* args[]) {
    cout << "RandomKill - V pre-alpha\n";
    RK rk;
    return 0;
}
