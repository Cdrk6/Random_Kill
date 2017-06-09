#include "Map.hpp"

const int Map::C = 32;
const int Map::NSTEP = 10;
const float Map::STEP = C / (float) NSTEP;

Map::Map(int cx, int cy, vector<Texture*> t) : Entity(cx*C, cy*C, t[0]) {
    Map::cx = cx;
    Map::cy = cy;
    Map::textures = t;
}

Map::~Map() {
}

void Map::draw(SDL_Renderer* r) {
    if (cMap == 0)
        textures[0]->render(0, 0, x, y, 1280, 768);
    else
        textures[cMap]->render((1280 - textures[cMap]->getWidth()) / 2, (768 - textures[cMap]->getHeight()) / 2);
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

void Map::setCoord(int ncx, int ncy) {
    cx = ncx;
    cy = ncy;
}

void Map::setMap(int nMap) {
    cMap = nMap;
}
