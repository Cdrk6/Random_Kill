#ifndef MAP_HPP
#define MAP_HPP

//#include "../Display.hpp"
#include "Entity.hpp"
#include <vector>

class Map : public Entity {
  public:
	static const int C;
	static const int NSTEP; //Nombre d'execution de calculate par déplacement
	static const float STEP;
	static const int MINCX;
	static const int MINCY;
	static const int MAXCX;
	static const int MAXCY;
	static const int CXSCREEN;
	static const int CYSCREEN;
	static const bool REDRAW; //True : affichage en 2 couches
	
	float intx = 0;
	float inty = 0;
	
	Map(int, int, vector<Texture*>);
	~Map();
	void draw(SDL_Renderer*) override;
	void calculate(float) override;
	void move(int) override;
	void setMap(int);
	void redraw();

  private:
	vector<Texture*> textures;
	int moving = 0;
	int dir = 0;
	float speed = 0.10; //Temps pour parcourir une case en seconde
	float time = 0;
	int cMap = 0;
};

#endif /* MAP_HPP */

