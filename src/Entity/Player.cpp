#include "Player.hpp"

Player::Player(Texture* t) : Entity(0, 0, t) {

}

Player::~Player() {
    
}

void Player::draw(SDL_Renderer* r) {
    t->render(x, y);
}

void Player::calculate(float timeStep) {
    x += 1;
}
