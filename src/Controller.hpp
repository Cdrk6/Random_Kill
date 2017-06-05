#ifndef INPUT_HPP
#define INPUT_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <type_traits>
#include <SDL2/SDL.h>
#include <SDL2/SDL_joystick.h>
#include <SDL2/SDL_ttf.h>

#define toString(name) # name
#define DEFAULT_TIMEOUT 5
#define DEFAULT_NB_BUTTONS_USED 10

using namespace std;


enum class JoystickButton {
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

    //Options
    SELECT,
    START,

    //Joysticks
    R_UP,
    R_DOWN,
    R_LEFT,
    R_RIGHT,
    R_BUTTON,

    L_UP,
    L_DOWN,
    L_LEFT,
    L_RIGHT,
    L_BUTTON,

    //Triggers
    L1,
    L2,
    R1,
    R2,
            
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

JoystickButton& operator++(JoystickButton& but);
JoystickButton operator++(JoystickButton& but, int);


class Controller {
public:
    Controller(int timeout, int nbButtonsUsed); //Max time (seconds) searching input devices
    //Input(const Input& orig);
    virtual ~Controller();

    bool isJoystickModeEnabled();
    JoystickButton* getButtonsPressed();
	void updateButtonsPressed();

private:
    GameMode gameControlType;
    SDL_Joystick* myJoystick;
    int myNbButtonsUsed;
    int* myJoystickConfig;
    JoystickButton* buttonsPressed;
    int* myKeyboardConfig;
    KeyboardKey* keysPressed;
    
    void configureJoystick(bool defaultConfig, bool NESType);
    void initJoystickButtons();
    int getIndexOfCommand(bool init);
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
 * 2.  --
 * 3.  X
 * 4.  Y
 * 5.  --
 * 6.  L1
 * 7.  R1
 * 8.  L2
 * 9.  R2
 * 10. SELECT
 * 11. START
 * 12. --
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

static const char* configInstructions[24] = {
    "Press UP",
    "Press DOWN",
    "Press LEFT",
    "Press RIGHT",
    "Press A",
    "Press B",
    "Press X",
    "Press Y",
    "Press SELECT",
    "Press START",
    "Incline L Joystick UP",
    "Incline L Joystick DOWN",
    "Incline L Joystick LEFT",
    "Incline L Joystick RIGHT",
    "Press L3",
    "Incline R Joystick UP",
    "Incline R Joystick DOWN",
    "Incline R Joystick LEFT",
    "Incline R Joystick RIGHT"
    "Press R3",
    "Press L1",
    "Press L2",
    "Press R1",
    "Press R2"
};

#endif /* INPUT_HPP */
