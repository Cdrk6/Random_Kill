#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../Texture.hpp"
#include "Entity.hpp"

class Player : public Entity {
  public:
	Player(Texture*);
	~Player();
	void draw(SDL_Renderer*);
	void calculate(float);

  private:

};

#endif /* PLAYER_HPP */
