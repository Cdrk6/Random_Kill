#ifndef RK_HPP
#define RK_HPP

#include <vector>

#include "Display.hpp"
#include "Entity/Entity.hpp"
#include "IO.hpp"
#include "Input.hpp"
#include "Sound.hpp"
//#include "State.hpp"
#include "Stats.hpp"
#include "View/View.hpp"

class RK {
  public:
	RK();
	~RK();
  private:
	Sound mySound;
	Display display;
	Input input;
	View myView;
	IO myIO;
	std::vector< Entity > myEntity;
	//State myState;
	Stats myStats;
};

#endif /* RK_HPP */