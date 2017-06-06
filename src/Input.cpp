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
            cout << "\tJoystick : " << (int) event.jdevice.which << endl;
            myJoystick = SDL_JoystickOpen(event.jdevice.which);
            gameControlType = JOYSTICK;
            cont = false;
        }

        if ((clock() - begin) / CLOCKS_PER_SEC >= timeout)
            cont = false;
    }

    //Joystick Buttons initialization
    if (isJoystickModeEnabled())
        Input::initJoystickButtons();
}

//Input::Input(const Input& but) {}

Input::~Input() {
    if (isJoystickModeEnabled())
        SDL_JoystickClose(myJoystick);
    if (myJoystickConfig != NULL)
        delete myJoystickConfig;
    if (buttonsPressed != NULL)
        delete buttonsPressed;
    if (myKeyboardConfig != NULL)
        delete myKeyboardConfig;
    if (keysPressed != NULL)
        delete keysPressed;
}

bool Input::isJoystickModeEnabled() {
    return (gameControlType == JOYSTICK);
}

JoystickButton* Input::getButtonsPressed() {
    return buttonsPressed;
}


void Input::initJoystickButtons() {
    int nbButtonsConfigured;
    ifstream file;
    file.open("res/NES_Default_Config");

    //Error in file opening
    if (!file.is_open()) {
        cerr << "Error : res/NES_Default_Config did not open." << endl;
        gameControlType = KEYBOARD;
        exit(-1);
    }

    //Case : The file is empty
    if (file.peek() == std::ifstream::traits_type::eof()) {
        cout << "File is empty." << endl;
        Input::configureJoystick(true, true);
    }

    file.clear();
    file >> nbButtonsConfigured;


    //Case : The default config is not sufficient for the wanted one
    if (nbButtonsConfigured < myNbButtonsUsed) {
        cout << "File has not enough configurations." << endl;
        Input::configureJoystick(true, true);
    }


    myJoystickConfig = new (nothrow) int [nbButtonsConfigured];

    //Error in memory allocation
    if (myJoystickConfig == NULL) {
        cerr << "Error : myJoystickConfig allocation failed" << endl;
        gameControlType = KEYBOARD;
        exit(-1);
    }

    cout << "Joystick nbButtons match : " << nbButtonsConfigured << endl;

    int joystickButtonValue;
    for (int i = 0; i < nbButtonsConfigured; ++i) {
        file >> joystickButtonValue;
        myJoystickConfig[i] = joystickButtonValue;
        cout << JoystickButton_toString(static_cast<JoystickButton> (i)) << " : " << myJoystickConfig[i];
        if (i < nbButtonsConfigured - 1)
            cout << "  |  ";
    }
    cout << endl;


    file.close();
}

void Input::configureJoystick(bool defaultConfig, bool NESType) {
    //Error in joystick connection
    if (!isJoystickModeEnabled()) {
        cerr << "The Joystick can not be configured if it is not connected." << endl;
        gameControlType = KEYBOARD;
        exit(-1);
    }

    ofstream file;

    if (defaultConfig) {
        if (NESType)
            file.open("res/NES_Default_Config", ios::out | ios::trunc);
        else
            file.open("res/Controller_Default_Config", ios::out | ios::trunc);
    } else {
        if (NESType)
            file.open("res/NES_Perso_Config", ios::out | ios::trunc);
        else
            file.open("res/Controller_Perso_Config", ios::out | ios::trunc);
    }

    file << myNbButtonsUsed << endl;

    SDL_Window* pWindow = NULL;
    pWindow = SDL_CreateWindow("Config NES Default",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            640,
            480,
            SDL_WINDOW_SHOWN
            );


    SDL_Renderer* renderer = SDL_CreateRenderer(pWindow, -1, 0);

    //Error in TTF initialization
    if (TTF_Init() == -1) {
        cout << "TTF_Init failed." << endl;
        exit(-1);
    }

    TTF_Font* font = TTF_OpenFont("res/typewriter.ttf", 24);
    if (!font) {
        cout << "Font failed loading." << endl;
        exit(-1);
    }

    SDL_Color Black = {0, 0, 0};

    SDL_Surface** surfaceMessage = new (nothrow) SDL_Surface* [myNbButtonsUsed];
    for (int i = 0; i < myNbButtonsUsed; ++i) {
        surfaceMessage[i] = TTF_RenderText_Solid(font, configInstructions[i], Black);
    }

    SDL_Rect MessageCoord;
    MessageCoord.x = 270;
    MessageCoord.y = 190;
    MessageCoord.w = 100;
    MessageCoord.h = 100;

    SDL_Texture* message;

    SDL_Event event;
    bool cont = true;
    int i = 0;
    bool retry = false;
    int* temp = new (nothrow) int [myNbButtonsUsed];
    JoystickButton but = JoystickButton::UP;

    SDL_JoystickEventState(SDL_ENABLE);

    while (cont) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        message = SDL_CreateTextureFromSurface(renderer, surfaceMessage[(int) but]);
        SDL_RenderCopy(renderer, message, NULL, &MessageCoord);
        SDL_RenderPresent(renderer);
        
        retry = false;
        i = getIndexOfCommand();
        
        for (int j = 0; j < (int)but; ++j) {
            if(temp[j] == i) {
                retry = true;
                cout << "This button is already used." << endl;
            }
        }
        
        if (i >= 0 && !retry) {
            cout << JoystickButton_toString(but) << " = " << (int) but << " -> " << i << endl;
            file << i << endl;
            temp[(int)but] = i;
            but++;
        }

        if ((int) but >= myNbButtonsUsed)
            cont = false;
    }

    delete temp;
    
    SDL_DestroyWindow(pWindow);

    file.close();
    TTF_CloseFont(font);
}

int Input::getIndexOfCommand() {
    SDL_Event event;
    
    SDL_WaitEvent(&event);
    
    if (event.type == SDL_JOYHATMOTION && event.jhat.value == 0)
        return -1;
    
    switch (event.type) {
        case SDL_JOYBUTTONDOWN:
            return event.jbutton.button;
        case SDL_JOYHATMOTION:
            switch (event.jhat.value) {
                case 1:
                    return 15;
                case 2:
                    return 18;
                case 4:
                    return 16;
                case 8:
                    return 17;
            }
            break;
    }
    return -1;
}

void Input::updateButtonsPressed() {
    /*
    //For now we will consider we can only have ONE button pressed at a time.
    int action = getIndexOfCommand();
    buttonsPressed = new (nothrow) JoystickButton[1];
    for (JoystickButton but = JoystickButton::UP; (int)but < myNbButtonsUsed; ++but) {
        if (action == myJoystickConfig[(int)but]) {
            buttonsPressed[0] = but;
            return;
        }
    }
    buttonsPressed = NULL;
    */
    
}



/******************************* Enum operations ******************************/

JoystickButton& operator++(JoystickButton& but) {
    if (but != JoystickButton::R2)
        but = static_cast<JoystickButton> ((int) but + 1);
    else
        but = JoystickButton::UNUSED;
    return but;
}

JoystickButton operator++(JoystickButton& but, int) {
    JoystickButton rVal = but;
    ++but;
    return rVal;
}

string JoystickButton_toString(JoystickButton joystickButton) {
    switch (joystickButton) {
        case JoystickButton::UP:
            return "UP";
        case JoystickButton::DOWN:
            return "DOWN";
        case JoystickButton::LEFT:
            return "LEFT";
        case JoystickButton::RIGHT:
            return "RIGHT";
        case JoystickButton::A:
            return "A";
        case JoystickButton::B:
            return "B";
        case JoystickButton::X:
            return "X";
        case JoystickButton::Y:
            return "Y";
        case JoystickButton::SELECT:
            return "SELECT";
        case JoystickButton::START:
            return "START";
        case JoystickButton::R_UP:
            return "R_UP";
        case JoystickButton::R_DOWN:
            return "R_DOWN";
        case JoystickButton::R_LEFT:
            return "R_LEFT";
        case JoystickButton::R_RIGHT:
            return "R_RIGHT";
        case JoystickButton::R_BUTTON:
            return "R_BUTTON";
        case JoystickButton::L_UP:
            return "L_UP";
        case JoystickButton::L_DOWN:
            return "L_DOWN";
        case JoystickButton::L_LEFT:
            return "L_LEFT";
        case JoystickButton::L_RIGHT:
            return "L_RIGHT";
        case JoystickButton::L_BUTTON:
            return "L_BUTTON";
        case JoystickButton::L1:
            return "L1";
        case JoystickButton::L2:
            return "L2";
        case JoystickButton::R1:
            return "R1";
        case JoystickButton::R2:
            return "R2";
        case JoystickButton::UNUSED:
            return "UNUSED";
    }
    return "Error";
}

string KeyboardKey_toString(KeyboardKey keyboardKey) {
    switch (keyboardKey) {
        case KeyboardKey::UP:
            return "UP";
        case KeyboardKey::DOWN:
            return "DOWN";
        case KeyboardKey::LEFT:
            return "LEFT";
        case KeyboardKey::RIGHT:
            return "RIGHT";
        case KeyboardKey::SPACEBAR:
            return "SPACEBAR";
        case KeyboardKey::A:
            return "A";
        case KeyboardKey::Z:
            return "Z";
        case KeyboardKey::E:
            return "E";
        case KeyboardKey::BACK:
            return "BACK";
        case KeyboardKey::ENTER:
            return "ENTER";
    }
    return "Error";
}

string GameMode_toString(GameMode gameMode) {
    switch (gameMode) {
        case GameMode::JOYSTICK:
            return "JOYSTICK";
        case GameMode::KEYBOARD:
            return "KEYBOARD";
    }
    return "Error";
}
