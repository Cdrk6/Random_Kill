#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../Texture.hpp"
#include "Entity.hpp"
#include "Map.hpp"
#include "NPC.hpp"
#include <vector>

class Player : public Entity {
  public:
	static int cMap;
	Player(int, int, Texture*, Map*, vector<vector<string*>>);
	~Player();
	void draw(SDL_Renderer*) override;
	void calculate(float) override;
	void move(int) override;
	bool collision(int, int); //True collision, False pas de collision
	void relativeMove(int);

  private:
	Map* map = NULL;
	vector<vector<string*>> col;
	int cx = 0;
	int cy = 0;
	int tcx = 0;
	int tcy = 0;
	int dir = 0;
	int anim = 1;
	float speed = 0.25; //Temps pour parcourir une case en seconde
	int moving = 0;
	float time = 0;
	bool walking = false;
	bool stop = true;
};

#endif /* PLAYER_HPP */
