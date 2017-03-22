#ifndef RK_HPP
#define RK_HPP

#include "Display.hpp"
#include "Entity/Entity.hpp"
#include "IO.hpp"
#include "Input.hpp"
#include "Sound.hpp"
//#include "State.hpp"
#include "Stats.hpp"
#include "View/View.hpp"
#include "Map.hpp"
#include <vector>
#include <iostream>

class RK {
  public:
	RK();
	~RK();
  private:
	Display *display;
	Input *input;
        Map *map;
	View myView;
	IO myIO;
	std::vector< Entity > myEntity;
	Sound mySound;
	//State myState;
	Stats myStats;
};

#endif