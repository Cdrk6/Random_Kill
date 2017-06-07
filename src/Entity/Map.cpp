#include "Map.hpp"

Map::Map(int x, int y, Texture* t) : Entity(x, y, t) {
}

Map::~Map() {
}

void Map::draw(SDL_Renderer* r) {
    t->render(0, 0, x, y, 1280, 768);
}

void Map::calculate(float timeStep) {
    
}

void Map::move(int dir) {
    //moving = nStep + 1;
}
