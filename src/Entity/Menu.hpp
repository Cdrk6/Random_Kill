#ifndef MENU_HPP
#define MENU_HPP

#include "Entity.hpp"
#include <vector>

class Menu : public Entity {
  public:
	static int state;
	Menu(vector<Texture*>);
	~Menu();
	void draw(SDL_Renderer*) override;
	void calculate(float) override;
	void move(int) override;
	
  private:
	vector<Texture*> textures;
};

#endif /* MENU_HPP */

