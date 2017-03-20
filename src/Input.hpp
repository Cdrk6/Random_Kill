#ifndef INPUT_HPP
#define INPUT_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_joystick.h>
#include <SDL2/SDL_ttf.h>

#define toString(name) # name
#define DEFAULT_TIMEOUT 5
#define DEFAULT_NB_BUTTONS_USED 19

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

    bool isJoystickModeEnabled();

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

/**
 * @Documentation
 * 
 * The config arrays :
 * 
 * Both of the config arrays (myJoystickConfig and myKeyboardConfig) have values
 * in JoystickButton or KeyboardKey enums. The indexes of the arrays are defined
 * like so :
 * 
 * For NES Controller :
 * 0.  A
 * 1.  B
 * 2.  ?
 * 3.  X
 * 4.  Y
 * 5.  ?
 * 6.  L1
 * 7.  R1
 * 8.  L2
 * 9.  R2
 * 10. SELECT
 * 11. START
 * 12. ?
 * 13. L_BUTTON
 * 14. R_BUTTON
 * 15. UP (hat 0 -> val 1)
 * 16. DOWN (hat 0 -> val 4)
 * 17. LEFT (hat 0 -> val 8)
 * 18. RIGHT (hat 0 -> val 2)
 * 19. L_UP
 * 20. L_DOWN
 * 21. L_LEFT
 * 22. L_RIGHT
 * 23. R_UP
 * 24. R_DOWN
 * 25. R_LEFT
 * 26. R_RIGHT
 * 
 */

#endif /* INPUT_HPP */
