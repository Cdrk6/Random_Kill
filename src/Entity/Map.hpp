#ifndef MAP_HPP
#define MAP_HPP

//#include "../Display.hpp"
#include "Entity.hpp"

class Map : public Entity {
  public:
	Map(int, int, Texture*);
	~Map();
	void draw(SDL_Renderer*) override;
	void calculate(float) override;
	void move(int) override;

  private:
	int moving = 0;
};

#endif /* MAP_HPP */

