#include "Map.hpp"

const int Map::C = 32;
const int Map::NSTEP = 10;
const float Map::STEP = C / (float) NSTEP;

Map::Map(int cx, int cy, Texture* t) : Entity(cx*C, cy*C, t) {
    Map::cx = cx;
    Map::cy = cy;
}

Map::~Map() {
}

void Map::draw(SDL_Renderer* r) {
    t->render(0, 0, x, y, 1280, 768);
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
