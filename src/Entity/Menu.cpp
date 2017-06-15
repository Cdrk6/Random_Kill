#include "Menu.hpp"

int Menu::state = 0;

Menu::Menu(vector<Texture*> texs) : Entity(0, 0, texs[0]) {
    Menu::textures = texs;
}

Menu::~Menu() {
}

void Menu::draw(SDL_Renderer* r) {
    t->render(0, 0);
    if (state == 0) {
        textures[2]->render(350, 250, textures[2]->getWidth() / 2, 0, textures[2]->getWidth() / 2, textures[2]->getHeight());
        textures[4]->render(350, 330, 0, 0, textures[4]->getWidth() / 2, textures[4]->getHeight());
    } else {
        textures[2]->render(350, 250, 0, 0, textures[2]->getWidth() / 2, textures[2]->getHeight());
        textures[4]->render(350, 330, textures[4]->getWidth() / 2, 0, textures[4]->getWidth() / 2, textures[4]->getHeight());
    }
}

void Menu::calculate(float timeStep) {
}

void Menu::move(int d) {
    //if(d < 0 && )
    state = d;
}

