#ifndef DIALOG_HPP
#define DIALOG_HPP

#include "Entity.hpp"
#include <vector>

class Dialog : public Entity {
  public:
	Dialog(int, int, Texture*, vector<string*>);
	~Dialog();
	void draw(SDL_Renderer*) override;
	void calculate(float) override;
	void move(int) override;

  private:
	vector<string*> sntcs;
};

#endif /* DIALOG_HPP */

