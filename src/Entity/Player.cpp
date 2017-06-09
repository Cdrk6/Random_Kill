#include "Player.hpp"

Player::Player(int cx, int cy, Texture* t, Map* m, vector<vector<string>> col) : Entity(20 * Map::C, 12 * Map::C, Map::C, Map::C, t) {
    Player::cx = cx;
    Player::cy = cy;
    Player::map = m;
    Player::col = col;
}

Player::~Player() {

}

void Player::draw(SDL_Renderer* r) {
    //if(cMap == 0)
        t->render(x, y, anim * Map::C, dir * Map::C, Map::C, Map::C);
    //else
    //    t->render(x, y, anim * Map::C, dir * Map::C, Map::C, Map::C);
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
            if (!stop)
                Player::move(dir + 4);
        }
    }
}

bool Player::collision(int dx, int dy) {
    //cout << col[cMap][cy+dy][cx+dx] << endl;
    if (col[cMap][cy + dy][cx + dx] == '0') {
        stop = true;
        return true;
    } else if (col[cMap][cy + dy][cx + dx] - '0' > 1) { //Changement de map
        stop = true;
        if (cMap == 0) {
            cMap = col[cMap][cy + dy][cx + dx] - '0' - 1;
            tcx = cx;
            tcy = cy;
            cx = stoi(col[7][(cMap-1)*2]);
            cy = stoi(col[7][(cMap-1)*2+1]);
            x = (1280 - col[cMap][0].size() * Map::C)/2 + cx * Map::C;
            y = (768 - col[cMap].size() * Map::C)/2 + cy * Map::C;
            map->setMap(cMap);
        } else {
            cMap = 0;
            cx = tcx;
            cy = tcy;
            x = 20 * Map::C;
            y = 12 * Map::C;
            map->setMap(0);
        }
    }
    return false;
}

void Player::move(int d) {
    if (d < 4 && !stop)
        stop = true;
    else if (d < 4 && stop)
        stop = false;
    else
        d -= 4;
    if (moving)
        return;
    dir = d;
    //cout << col[cy + 1][cx] << col[cy][cx - 1] << col[cy][cx + 1] << col[cy - 1][cx] << endl;
    switch (dir) {
        case 0: //Down
            if (collision(0, 1))
                return;
            break;
        case 1: //Left
            if (collision(-1, 0))
                return;
            break;
        case 2: //Right
            if (collision(1, 0))
                return;
            break;
        case 3: //Up
            if (collision(0, -1))
                return;
            break;
    }
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
    if (cMap != 0) {
        walking = true;
        return;
    }
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
