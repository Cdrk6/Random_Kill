#include "Player.hpp"

//const int Player::C = 32;
//const int Player::NSTEP = 10;

Player::Player(int cx, int cy, Texture* t, Map* m) : Entity(20 * Map::C, 12 * Map::C, Map::C, Map::C, t) {
    Player::cx = cx;
    Player::cy = cy;
    Player::map = m;
}

Player::~Player() {

}

void Player::draw(SDL_Renderer* r) {
    t->render(x, y, anim * Map::C, dir * Map::C, Map::C, Map::C);
}

void Player::calculate(float timeStep) {
    if (moving == Map::NSTEP + 1) {
        time = 0;
        moving--;
    }
    time += timeStep;
    //cout << "Time " << speed / nStep << endl;
    if (time < speed / Map::NSTEP)
        return;
    time -= speed / Map::NSTEP;
    if (moving) {
        moving--;
        if (walking)
            switch (dir) {
                case 0: //Down
                    y += Map::STEP;
                    break;
                case 1: //Left
                    x -= Map::STEP;
                    break;
                case 2: //Right
                    x += Map::STEP;
                    break;
                case 3: //Up
                    y -= Map::STEP;
                    break;
            }
        if (moving % 2 == 0)
            if (anim > 1)
                anim = 0;
            else
                anim += 1;
        if (!moving) {
            //cout << x << "; " << y << endl;
            walking = false;
        }
    }
}

void Player::move(int d) {

    if (moving)
        return;
    dir = d;
    //if(!Collisions)
    //return;
    moving = Map::NSTEP + 1;
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
    map->setCoord(cx, cy);
    cout << cx << "; " << cy << endl;
    switch (d) {
        case 0: //Down
            if (cy > 12 && cy < 139)
                map->move(d);
            else
                walking = true;
            break;
        case 1: //Left
            if (cx > 19 && cx < 143)
                map->move(d);
            else
                walking = true;
            break;
        case 2: //Right
            if (cx > 20 && cx < 144)
                map->move(d);
            else
                walking = true;
            break;
        case 3: //Up
            if (cy > 11 && cy < 138)
                map->move(d);
            else
                walking = true;
            break;
    }
}
