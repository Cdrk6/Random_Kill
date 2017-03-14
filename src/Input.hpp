#ifndef INPUT_HPP
#define INPUT_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_joystick.h>

enum class JoystickButtonPressed {
    //Directions
    UP,
    DOWN,
    LEFT,
    RIGHT,

    //Actions
    A,
    B,
    X,
    Y,

    //Option
    SELECT,
    START,

    //Joysticks
    R_UP,
    R_DOWN,
    R_LEFT,
    R_RIGHT,

    L_UP,
    L_DOWN,
    L_LEFT,
    L_RIGHT,

    //Triggers
    L1,
    L2,
    R1,
    R2
};

enum class KeyPressed {
    //Directions
    UP,
    DOWN,
    LEFT,
    RIGHT,

    //Actions
    SPACEBAR,
    A,
    Z,
    E,

    //Options
    ENTER,
    BACK,

    //...
};

enum GameMode {
    JOYSTICK, KEYBOARD
};

class Input {
public:
    Input(int timeout); //Max time (seconds) searching input devices
    Input(const Input& orig);
    virtual ~Input();

    bool isJoystickConnected();

private:
    GameMode gameControl;
    SDL_Joystick* myJoystick;

};

#endif /* INPUT_HPP */
