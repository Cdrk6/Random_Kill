#include "Dialog.hpp"
#include "../Display.hpp"

bool Dialog::flagStop = false;

Dialog::Dialog(int x, int y, Texture* bulle1, Texture* bulle2, vector<TTF_Font*> fnts, Map* map, vector<vector < string*>> npcDat) : Entity(x, y, bulle1) {
    Dialog::bulle1 = bulle1;
    Dialog::bulle2 = bulle2;
    Dialog::fnts = fnts;
    Dialog::map = map;
    Dialog::npcDat = npcDat;
}

Dialog::~Dialog() {
}

void Dialog::draw(SDL_Renderer* r) {
    if (Map::REDRAW)
        map->redraw();
    if (state != -1) {
        bulle1->render(Display::W / 2 - t->getWidth() / 2, Display::H - t->getHeight());
        bulle2->render(Display::W - 200, Display::H - bulle2->getHeight());
        Texture txt(30 + Display::W / 2 - t->getWidth() / 2, 5 + Display::H - t->getHeight(), *npcDat[npc][5], fnts[2], r);
        Texture txt2(50 + Display::W / 2 - t->getWidth() / 2, 50 + Display::H - t->getHeight(), *npcDat[npc][6 + state], fnts[3], r);
    }
}

void Dialog::calculate(float timeStep) {

}

void Dialog::move(int d) {

}

void Dialog::setDialog(int npc) {
    if (npc == -1) {
        if (npcDat[Dialog::npc].size() == 6 + state + 1) {
            state = -1;
            flagStop = true;
        } else
            state++;
    } else {
        state = 0;
        Dialog::npc = npc;
    }
}
