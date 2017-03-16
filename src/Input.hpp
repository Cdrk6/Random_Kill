#ifndef INPUT_HPP
#define INPUT_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_joystick.h>

#define toString(name) # name
#define DEFAULT_TIMEOUT 5
#define DEFAULT_NB_BUTTONS_USED 10

using namespace std;


enum class JoystickButton {
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
    R_BUTTON = 14,

    L_UP = 15,
    L_DOWN = 16,
    L_LEFT = 17,
    L_RIGHT = 18,
    L_BUTTON = 19,

    //Triggers
    L1 = 20,
    L2 = 21,
    R1 = 22,
    R2 = 23,
            
    //Unused
    UNUSED = -1
};

enum class KeyboardKey {
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

string JoystickButton_toString(JoystickButton joystickButton);
string KeyboardKey_toString(KeyboardKey keyboardKey);
string GameMode_toString(GameMode gameMode);


class Input {
public:
    Input(int timeout, int nbButtonsUsed); //Max time (seconds) searching input devices
    Input(const Input& orig);
    virtual ~Input();

    bool isJoystickConnected();

private:
    GameMode gameControlType;
    SDL_Joystick* myJoystick;
    int myNbButtonsUsed;
    JoystickButton* myJoystickConfig;
    JoystickButton* buttonsPressed;
    KeyboardKey* myKeyboardConfig;
    KeyboardKey* keysPressed;

    void configureJoystick(bool defaultConfig, bool NESType);
    void initJoystickButtons();

};

#endif /* INPUT_HPP */
