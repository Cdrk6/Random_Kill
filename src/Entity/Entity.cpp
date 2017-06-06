#include "Entity.hpp"

Entity::Entity(int x, int y, int w, int h, Texture* t) {
    Entity::x = x;
    Entity::y = y;
    Entity::w = w;
    Entity::h = h;
    Entity::t = t;
}

Entity::Entity(int x, int y, Texture* t) {
    Entity::x = x;
    Entity::y = y;
    Entity::w = t->getWidth();
    Entity::h = t->getHeight();
    Entity::t = t;
}

Entity::~Entity() {
}

