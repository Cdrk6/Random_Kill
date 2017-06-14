#include "Dialog.hpp"

Dialog::Dialog(int x, int y, Texture* tex, vector<string*> sntcs) : Entity(x, y, tex) {
    Dialog::sntcs = sntcs;
}

Dialog::~Dialog() {
}

void Dialog::draw(SDL_Renderer* r) {
    
}

void Dialog::calculate(float timeStep) {
    
}

void Dialog::move(int d) {
    
}
