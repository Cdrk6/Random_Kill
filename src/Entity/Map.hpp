#ifndef MAP_HPP
#define MAP_HPP

//#include "../Display.hpp"
#include "Entity.hpp"

class Map : public Entity {
  public:
	static const int C;
	static const int NSTEP; //Nombre d'execution de calculate par déplacement
	static const float STEP;
	
	Map(int, int, Texture*);
	~Map();
	void draw(SDL_Renderer*) override;
	void calculate(float) override;
	void move(int) override;
	void setCoord(int, int);

  private:
	int cx = 0;
	int cy = 0;
	int moving = 0;
	int dir = 0;
	float speed = 0.25; //Temps pour parcourir une case en seconde
	float time = 0;
};

#endif /* MAP_HPP */

