#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../Texture.hpp"
#include "Entity.hpp"
#include "Map.hpp"

class Player : public Entity {
  public:
	Player(int, int, Texture*, Map*);
	~Player();
	void draw(SDL_Renderer*) override;
	void calculate(float) override;
	void move(int) override;

  private:
	Map* map = NULL;
	int cx = 0;
	int cy = 0;
	int dir = 1;
	int anim = 0;
	float speed = 0.25; //Temps pour parcourir une case en seconde
	int moving = 0;
	float time = 0;
	bool walking = false;
	bool stop = true;
};

#endif /* PLAYER_HPP */
