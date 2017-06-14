#include "Map.hpp"

const int Map::C = 32;
const int Map::NSTEP = 15; //3 pour le Raspi
const bool Map::REDRAW = true; //False pour le Raspi
const float Map::STEP = C / (float) NSTEP;
const int Map::MINCX = 19;
const int Map::MINCY = 11; //Trust
const int Map::MAXCX = 144;
const int Map::MAXCY = 139;
const int Map::CXSCREEN = 40;
const int Map::CYSCREEN = 24;

Map::Map(int cx, int cy, vector<Texture*> t) : Entity(cx*C, cy*C, t[0]) {
    Map::textures = t;
}

Map::~Map() {
}

void Map::draw(SDL_Renderer* r) {
    if (cMap == 0) {
        if (Map::REDRAW)
            textures[0]->render(0, 0, x, y, 1280, 768);
        else
            textures[8]->render(0, 0, x, y, 1280, 768);
    } else
        textures[cMap]->render(intx, inty);
}

void Map::redraw() {
    if (cMap == 0)
        textures[7]->render(0, 0, x, y, 1280, 768);
}

void Map::calculate(float timeStep) {
    if (moving == NSTEP + 1) {
        time = 0;
        moving--;
    }
    time += timeStep;
    if (time < speed / NSTEP)
        return;
    time -= speed / NSTEP;
    if (moving) {
        moving--;
        switch (dir) {
            case 0: //Down
                y += STEP;
                break;
            case 1: //Left
                x -= STEP;
                break;
            case 2: //Right
                x += STEP;
                break;
            case 3: //Up
                y -= STEP;
                break;
        }
        if (!moving) {
            //x = cx * C;
            //y = cy * C;
        }
    }
}

void Map::move(int d) {
    dir = d;
    moving = NSTEP + 1;
}

void Map::setMap(int nMap) {
    cMap = nMap;
    intx = (1280 - textures[cMap]->getWidth()) / 2;
    inty = (768 - textures[cMap]->getHeight()) / 2;
}
