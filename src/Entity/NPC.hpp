#ifndef NPC_HPP
#define NPC_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Entity.hpp"
#include "Map.hpp"

using namespace std;

class NPC : public Entity {
  public:
	NPC(int, int, int, int, Texture*, string);
	~NPC();
	void draw(SDL_Renderer*) override;
	void calculate(float) override;
	void move(int) override;

  private:
	int anim = 1;
	int dir = 0;
	int cx = 0;
	int cy = 0;
	int zw = 0;
	int zh = 0;
	string name;
};

#endif /* NPC_HPP */

