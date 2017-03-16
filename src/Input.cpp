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
    free(myJoystick);
    free(myJoystickConfig);
    free(buttonsPressed);
    free(myKeyboardConfig);
    free(keysPressed);
}

bool Input::isJoystickConnected() {
    return (myJoystick != NULL);
}

void Input::initJoystickButtons() {
    int nbButtonsConfigured;
    ifstream file;
    file.open("res/NES_Default_Config");
        
    //Error in file opening
    if (!file.is_open()) {
        cerr << "Error : res/NES_Default_Config did not open." << endl;
        exit(-1);
    }
    
    file >> nbButtonsConfigured;
    
    //Case : The default config matches with the wanted one
    if (nbButtonsConfigured >= myNbButtonsUsed) {
        myJoystickConfig = new (nothrow) JoystickButtons [nbButtonsConfigured];
        
        //Error in memory allocation
        if (myJoystickConfig == NULL) {
            cerr << "Error : myJoystickConfig allocation failed" << endl;
            exit(-1);
        }
        
        cout << "Joystick nbButtons match : " << nbButtonsConfigured << endl;
        
        int indexJoystickButtons;
        for (int i = 0; i < nbButtonsConfigured; ++i) {
            file >> indexJoystickButtons;
            myJoystickConfig[i] = static_cast<JoystickButtons>(indexJoystickButtons);
            //cout << myJoystickConfig[i] << " ";
        }
        cout << endl;
    }
    
    //Case : The default config is not sufficient for the wanted one
    else {
        /**
         * The function is not created yet.
         * 
         * Input::configureJoystick()
         */
    }
    
    file.close();
}

/*
 * void Input::checkButtonPressed() {
    static SDL_Event *event;
    
    if(gameControlType == JOYSTICK) {
        
    }
}
*/