#ifndef RK_HPP
#define RK_HPP

#include "Display.hpp"
#include "Entity/Entity.hpp"
#include "IO.hpp"
#include "Controller.hpp"
#include "Sound.hpp"
//#include "State.hpp"
#include "Stats.hpp"
#include "View/View.hpp"
#include "Map.hpp"
#include <vector>
#include <iostream>

using namespace std;

class RK {
  public:
	RK();
	~RK();
	IO* getIO();
  private:
	Display *display;
	Controller *controller;
	Map *map;
	IO *io;
	View myView;
	vector<Entity> myEntity;
	Sound mySound;
	//State myState;
	Stats myStats;
};

#endif