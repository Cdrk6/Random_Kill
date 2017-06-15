#ifndef DIALOG_HPP
#define DIALOG_HPP

#include "Entity.hpp"
#include "Map.hpp"
#include <vector>

class Dialog : public Entity {
  public:
	static bool flagStop;
	
	Dialog(int, int, Texture*, Texture*, vector<TTF_Font*>, Map*, vector<vector < string*>>);
	~Dialog();
	void draw(SDL_Renderer*) override;
	void calculate(float) override;
	void move(int) override;
	void setDialog(int);

  private:
	vector<vector < string*>> npcDat;
	Texture* bulle1 = NULL;
	Texture* bulle2 = NULL;
	vector<TTF_Font*> fnts;
	Map* map = NULL;
	int state = -1;
	int npc = 0;
};

#endif /* DIALOG_HPP */

