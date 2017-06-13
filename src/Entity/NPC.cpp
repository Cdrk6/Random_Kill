#include "NPC.hpp"

NPC::NPC(int cx, int cy, int zw, int zh, Texture* tex, string name) : Entity(0, 0, Map::C, Map::C, tex) {
    NPC::cx = cx;
    NPC::cy = cy;
    NPC::zw = zw;
    NPC::zh = zh;
    NPC::name = name;
}

NPC::~NPC() {
}

void NPC::draw(SDL_Renderer* r) {
    t->render(x, y, anim * w, dir * h, w, h);
}

void NPC::calculate(float timeStep) {
}

void NPC::move(int dir) {
}