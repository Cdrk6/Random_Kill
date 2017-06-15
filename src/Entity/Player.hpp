#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../Texture.hpp"
#include "Entity.hpp"
#include "Map.hpp"
#include <vector>

class NPC;
class Dialog;

class Player : public Entity {
  public:
	static int cMap;
	Player(int, int, Texture*, Map*, vector<vector<string*>>, vector<NPC*>, Dialog* d);
	~Player();
	void draw(SDL_Renderer*) override;
	void calculate(float) override;
	void move(int) override;
	bool collision(int, int); //True collision, False pas de collision
	void relativeMove(int);
	void stopMoving();
	void startDialog();
	int checkNPC(int, int); //Renvoie -1 ou l'index du PNJ

  private:
	Map* map = NULL;
	Dialog* dia = NULL;
	vector<vector<string*>> col;
	vector<NPC*> npcs;
	int cx = 0;
	int cy = 0;
	int tcx = 0;
	int tcy = 0;
	int dir = 0;
	int fDir = -1;
	int anim = 1;
	float speed = 0.25; //Temps pour parcourir une case en seconde
	int moving = 0;
	float time = 0;
	bool walking = false;
	bool stop = true;
	bool dialog = false;
	int npc = -1;
};

#endif /* PLAYER_HPP */
