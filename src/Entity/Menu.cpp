#include "Menu.hpp"

Menu::Menu(vector<Texture*> texs) : Entity(0, 0, texs[0]) {
    Menu::textures = texs;
}

Menu::~Menu() {
}

void Menu::draw(SDL_Renderer* r) {
    switch (display) {
        case 0:
            t->render(0, 0);
            for (int i = 1; i < 5; i++) {
                if (state + 1 == i)
                    textures[i]->render(350, 220 + 65 * (i - 1), textures[i]->getWidth() / 2, 0, textures[i]->getWidth() / 2, textures[i]->getHeight());
                else
                    textures[i]->render(350, 220 + 65 * (i - 1), 0, 0, textures[i]->getWidth() / 2, textures[i]->getHeight());
            }
            break;
        case 1:
            textures[5]->render(0, 0);
            break;
        case 2:
            textures[6]->render(0, 0);
            break;
    }
}

void Menu::calculate(float timeStep) {
}

void Menu::validate() {
    if (display == 0)
        switch (state) {
            case 0:
                Display::menu = 1;
                break;
            case 1:
                display = 1;
                break;
            case 2:
                display = 2;
                break;
            case 3:
                Display::quit = true;
                break;
        }
}

void Menu::unvalidate() {
    state = 0;
    display = 0;
}

void Menu::move(int d) {
    if ((d < 0 && state == 0) || (d > 0 && state == 3))
        return;
    state += d;
}

