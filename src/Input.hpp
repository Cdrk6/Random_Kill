#ifndef INPUT_HPP
#define INPUT_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_joystick.h>

using namespace std;

enum class JoystickButtons {
    //Directions
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3,

    //Actions
    A = 4,
    B = 5,
    X = 6,
    Y = 7,

    //Options
    SELECT = 8,
    START = 9,

    //Joysticks
    R_UP = 10,
    R_DOWN = 11,
    R_LEFT = 12,
    R_RIGHT = 13,

    L_UP = 14,
    L_DOWN = 15,
    L_LEFT = 16,
    L_RIGHT = 17,

    //Triggers
    L1 = 18,
    L2 = 19,
    R1 = 20,
    R2 = 21
};

enum class KeyboardKeys {
    //Directions
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3,

    //Actions
    SPACEBAR = 4,
    A = 5,
    Z = 6,
    E = 7,

    //Options
    BACK = 8,
    ENTER = 9,

    //...
};

enum GameMode {
    JOYSTICK, KEYBOARD
};

class Input {
public:
    Input(int timeout, int nbButtonsUsed); //Max time (seconds) searching input devices
    Input(const Input& orig);
    virtual ~Input();

    bool isJoystickConnected();
    //void checkButtonPressed();

private:
    GameMode gameControlType;
    SDL_Joystick* myJoystick;
    int myNbButtonsUsed;
    JoystickButtons* myJoystickConfig;
    JoystickButtons* buttonsPressed;
    KeyboardKeys* myKeyboardConfig;
    KeyboardKeys* keysPressed;
    
    void initJoystickButtons();

};

#endif /* INPUT_HPP */
