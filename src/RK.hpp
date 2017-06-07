#ifndef RK_HPP
#define RK_HPP

#include "Display.hpp"
#include "Entity/Entity.hpp"
#include "IO.hpp"
#include "Controller.hpp"
#include "Sound.hpp"
#include "Stats.hpp"
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
	IO *io;
};

#endif