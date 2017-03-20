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
            cout << "\tJoystick : " << (int)event.jdevice.which << endl;
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

Input::Input(const Input& orig) {
}

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
        cout << "File is empty" << endl;
        Input::configureJoystick(true, true);
    }

    file >> nbButtonsConfigured;

    //Case : The default config matches with the wanted one
    if (nbButtonsConfigured >= myNbButtonsUsed) {
        myJoystickConfig = new (nothrow) JoystickButton [nbButtonsConfigured];

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
            myJoystickConfig[i] = static_cast<JoystickButton> (joystickButtonValue);
            cout << JoystickButton_toString(myJoystickConfig[i]) << " ";
        }
        cout << endl;
    }//Case : The default config is not sufficient for the wanted one
    else {
        Input::configureJoystick(true, true);
    }

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
    if (TTF_Init() == -1) {
        cout << "TTF_Init failed." << endl;
        exit(-1);
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    TTF_Font* font = TTF_OpenFont("res/typewriter.ttf", 24);
    if (!font) {
        cout << "Font failed loading." << endl;
        exit(-1);
    }

    SDL_Color Black = {0, 0, 0};
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, "Press A", Black);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_Rect MessageCoord;
    MessageCoord.x = 270;
    MessageCoord.y = 190;
    MessageCoord.w = 100;
    MessageCoord.h = 100;

    SDL_RenderCopy(renderer, Message, NULL, &MessageCoord);    
    
    SDL_RenderPresent(renderer);

    SDL_Event event;
    bool cont = true;
    int i;

    SDL_JoystickEventState(SDL_ENABLE);

    while (cont) {

        SDL_PollEvent(&event);

        if (event.type == SDL_JOYBUTTONDOWN)
            cout << "Joystick " << (int) event.jbutton.which << ", Button " << (int) event.jbutton.button << " is in state : " << (int) event.jbutton.state << "." << endl;

        else if (event.type == SDL_JOYBALLMOTION)
            cout << "Joystick " << (int) event.jball.which << ", Trackball " << (int) event.jball.ball << " has moved by X : " << (int) event.jball.xrel << "and by Y : " << (int) event.jball.yrel << "." << endl;

        else if (event.type == SDL_JOYHATMOTION)
            cout << "Joystick " << (int) event.jhat.which << ", Hat " << (int) event.jhat.hat << " has moved by : " << (int) event.jhat.value << "." << endl;

        else if (event.type == SDL_KEYDOWN) {
            cout << "Quit !" << endl;
            cont = false;
        }
    }

    SDL_DestroyWindow(pWindow);

    file.close();
    TTF_CloseFont(font);
}

string JoystickButton_toString(JoystickButton joystickButton) {
    switch (joystickButton) {
        case JoystickButton::UP :
            return "UP";
        case JoystickButton::DOWN :
            return "DOWN";
        case JoystickButton::LEFT :
            return "LEFT";
        case JoystickButton::RIGHT :
            return "RIGHT";
        case JoystickButton::A :
            return "A";
        case JoystickButton::B :
            return "B";
        case JoystickButton::X :
            return "X";
        case JoystickButton::Y :
            return "Y";
        case JoystickButton::SELECT :
            return "SELECT";
        case JoystickButton::START :
            return "START";
        case JoystickButton::R_UP :
            return "R_UP";
        case JoystickButton::R_DOWN :
            return "R_DOWN";
        case JoystickButton::R_LEFT :
            return "R_LEFT";
        case JoystickButton::R_RIGHT :
            return "R_RIGHT";
        case JoystickButton::R_BUTTON :
            return "R_BUTTON";
        case JoystickButton::L_UP :
            return "L_UP";
        case JoystickButton::L_DOWN :
            return "L_DOWN";
        case JoystickButton::L_LEFT :
            return "L_LEFT";
        case JoystickButton::L_RIGHT :
            return "L_RIGHT";
        case JoystickButton::L_BUTTON :
            return "L_BUTTON";
        case JoystickButton::L1 :
            return "L1";
        case JoystickButton::L2 :
            return "L2";
        case JoystickButton::R1 :
            return "R1";
        case JoystickButton::R2 :
            return "R2";
        case JoystickButton::UNUSED :
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
