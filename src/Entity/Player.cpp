#include "Player.hpp"

const int Player::C = 32;
const int Player::NSTEP = 10;

Player::Player(int cx, int cy, Texture* t, Map* m) : Entity(cx*C, cy*C, C, C, t) {
    Player::cx = cx;
    Player::cy = cy;
    Player::map = m;
}

Player::~Player() {

}

void Player::draw(SDL_Renderer* r) {
    t->render(x, y, anim*C, dir*C, C, C);
}

void Player::calculate(float timeStep) {
    if (moving == NSTEP + 1) {
        time = 0;
        moving--;
    }
    time += timeStep;
    //cout << "Time " << speed / nStep << endl;
    if (time < speed / NSTEP)
        return;
    time -= speed / NSTEP;
    if (moving) {
        moving--;
        /*switch (dir) {
            case 0: //Down
                y += C / (float)nStep;
                break;
            case 1: //Left
                x -= C / (float)nStep;
                break;
            case 2: //Right
                x += C / (float)nStep;
                break;
            case 3: //Up
                y -= C / (float)nStep;
                break;
        }*/
        if(moving % 2 == 0)
            if (anim > 1)
                anim = 0;
            else
                anim += 1;
        if (!moving){
            //cout << x << "; " << y << endl;
            
        }
    }
}

void Player::move(int d) {
    if (moving)
        return;
    dir = d;
    //if(!Collisions)
    //return;
    moving = NSTEP + 1;
    switch (d) {
        case 0: //Down
            cy++;
            break;
        case 1: //Left
            cx--;
            break;
        case 2: //Right
            cx++;
            break;
        case 3: //Up
            cy--;
            break;
    }
    map->move(d);
}
