#ifndef MENU_HPP
#define MENU_HPP

#include "Entity.hpp"
#include "../Display.hpp"
#include <vector>

class Menu : public Entity {
  public:
	Menu(vector<Texture*>);
	~Menu();
	void draw(SDL_Renderer*) override;
	void calculate(float) override;
	void move(int) override;
	void validate();
	void unvalidate();

  private:
	vector<Texture*> textures;
	int state = 0;
	int display = 0;
};

#endif /* MENU_HPP */

