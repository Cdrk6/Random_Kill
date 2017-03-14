#include "Input.hpp"

Input::Input(int timeout, int nbButtonsUsed) {
    //SDL Joystick initialization
    if (SDL_Init(SDL_INIT_JOYSTICK) != 0) {
        fprintf(stdout, "SDL Initialization failure : %s\n", SDL_GetError());
        exit(-1);
    }
    
    //Attributes initialization
    myJoystick = NULL;
    gameControlType = KEYBOARD;
    myNbButtonsUsed = nbButtonsUsed;
    SDL_JoystickEventState(SDL_ENABLE);

    //Joystick connection
    SDL_Event event;
    bool cont = true;
    clock_t begin = clock();
    
    while (cont) {
        SDL_PollEvent(&event);
        
        if (event.type == SDL_JOYDEVICEADDED) {
            cout << "Joystick Connected." << endl;
            cout << "\tJoystick : " << event.jdevice.which << endl;
            myJoystick = SDL_JoystickOpen(event.jdevice.which);
            gameControlType = JOYSTICK;
            cont = false;
        }
        
        if ((clock() - begin)/CLOCKS_PER_SEC >= timeout)
            cont = false;
    }
    
    //Joystick Buttons initialization
    if (isJoystickConnected())
        Input::initJoystickButtons();
}

Input::Input(const Input& orig) {
}

Input::~Input() {
}

bool Input::isJoystickConnected() {
    return (myJoystick != NULL);
}

void Input::initJoystickButtons() {
    int nbButtonsConfigured;
    ifstream file;
    file.open("res/NES_Default_Config");
    
    if (file.is_open())
        file >> nbButtonsConfigured;
    
    if (nbButtonsConfigured == myNbButtonsUsed)
        cout << "Joystick nbButtons match" << endl;
}

/*
 * void Input::checkButtonPressed() {
    static SDL_Event *event;
    
    if(gameControlType == JOYSTICK) {
        
    }
}
*/