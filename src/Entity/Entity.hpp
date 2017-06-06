#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../Texture.hpp"
#include <SDL2/SDL.h>

using namespace std;

class Entity {
  public:
	int x; //Position x
	int y; //Position y
	int w; //Largueur (Collision)
	int h; //Hauteur (Collision)
	Texture* t;
	
	Entity(int, int, int, int, Texture*);
	Entity(int, int, Texture*);
	virtual ~Entity();
	virtual void draw(SDL_Renderer*) = 0; //Dessine l'entité
	virtual void calculate(float) = 0; //Calcule l'entité
	void move(int, int); //Essaye de déplacer l'entité en (x, y)
	bool collision(int x, int y); //True collision; False sinon
	
  private:
};

#endif /* ENTITY_HPP */

