#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SDL2/SDL.h>

using namespace std;

class Entity {
  public:
	Entity();
	virtual ~Entity();
	int getX(); //Getters
	int getY(); //
	int getW(); //
	int getH(); //
	virtual void draw(SDL_Renderer*) = 0; //Dessine l'entité
	void move(int, int); //Essaye de déplacer l'entité en (x, y)
	
  private:
	int x; //Position x
	int y; //Position y
	int w; //Largueur (Collision)
	int h; //Hauteur (Collision)
	bool collision(int x, int y);
};

#endif /* ENTITY_HPP */

