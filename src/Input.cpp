#include "Input.hpp"

Input::Input(int timeout) {
    //SDL Joystick initialization
    if (SDL_Init(SDL_INIT_JOYSTICK) != 0) {
        fprintf(stdout, "SDL Initialization failure : %s\n", SDL_GetError());
        exit(-1);
    }

    myJoystick = NULL;
    gameControl = KEYBOARD;
    SDL_JoystickEventState(SDL_ENABLE);

    SDL_Event event;
    bool cont = true;
    clock_t begin = clock();
    
    while (cont) {
        SDL_PollEvent(&event);
        
        if (event.type == SDL_JOYDEVICEADDED) {
            std::cout << "Joystick Connected." << std::endl;
            std::cout << "\tJoystick : " << event.jdevice.which << std::endl;
            myJoystick = SDL_JoystickOpen(event.jdevice.which);
            cont = false;
        }
        
        if ((clock() - begin)/CLOCKS_PER_SEC >= timeout)
            cont = false;
    }
}

Input::Input(const Input& orig) {
}

Input::~Input() {
}

bool Input::isJoystickConnected() {
    return (myJoystick != NULL);
}