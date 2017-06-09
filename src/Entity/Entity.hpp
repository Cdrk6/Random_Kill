#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../Texture.hpp"

using namespace std;

class Entity {
  public:
	float x; //Position x
	float y; //Position y
	int w; //Largueur (Collision)
	int h; //Hauteur (Collision)
	Texture* t;
	
	Entity(int, int, int, int, Texture*);
	Entity(int, int, Texture*);
	virtual ~Entity();
	virtual void draw(SDL_Renderer*) = 0; //Dessine l'entité
	virtual void calculate(float) = 0; //Calcule l'entité
	virtual void move(int) = 0; //Essaye de déplacer l'entité en (x, y)
	virtual bool collision(int, int); //True collision; False sinon
	
  private:
};

#endif /* ENTITY_HPP */

