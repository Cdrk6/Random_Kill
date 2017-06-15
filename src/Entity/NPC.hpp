#ifndef NPC_HPP
#define NPC_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Entity.hpp"
#include "Map.hpp"
#include "Player.hpp"

using namespace std;

class NPC : public Entity {
  public:
	NPC(int, int, int, int, int, int, Texture*, string, vector<vector<string*>>);
	~NPC();
	void draw(SDL_Renderer*) override;
	void calculate(float) override;
	void move(int) override; //Mouvement du PNJ
	void relativeMove(int); //Mouvement relatif au joueur
	bool collision(int, int);
	void generateMove();
	int getCX();
	int getCY();
	
	bool dialog = false;

  private:
	vector<vector<string*>> col;
	float moveTime = 0;
	float time = 0;
	int anim = 1;
	int dir = 0;
	int moving = 0;
	float speed = 0.25; //Temps pour parcourir une case en seconde
	int cx = 0;
	int cy = 0;
	int icx = 0;
	int icy = 0;
	int zw = 0;
	int zh = 0;
	int cMap = 0; //Choix de la map
	string name;
};

#endif /* NPC_HPP */

