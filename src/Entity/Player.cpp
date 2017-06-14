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
    t->render(x, y, anim * w, dir * h, w, h);
    if (Map::REDRAW)
        map->redraw();
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
        if ((Map::NSTEP - moving) % (Map::NSTEP / 3) == 0)
            anim = ++anim % 3;
        if (!moving) {
            cout << x << "; " << y << endl;
            walking = false;
            anim = 1;
            if (!stop)
                Player::move(dir + 4);
        }
    }
}

bool Player::collision(int dx, int dy) {
    if (cx + dx < 0 || cy + dy < 0 || cx + dx >= col[cMap][0].size() || cy + dy >= col[cMap].size() || col[cMap][cy + dy][cx + dx] == '0') { //Si on est sur le bord de la map ou si collision
        stop = true;
        return true;
    }
    
    // Modification de la map de collision
    if (col[cMap][cy][cx] - '0' < 2)
        col[cMap][cy][cx] = '1';
    if (col[cMap][cy + dy][cx + dx] - '0' < 2)
        col[cMap][cy + dy][cx + dx] = '0';
    
    //Changement de map
    if (col[cMap][cy + dy][cx + dx] - '0' > 1) {
        if (cMap == 0) {
            stop = true;
            cMap = col[cMap][cy + dy][cx + dx] - '0' - 1;
            tcx = cx;
            tcy = cy;
            cx = stoi(col[7][(cMap - 1)*2]);
            cy = stoi(col[7][(cMap - 1)*2 + 1]);
            map->setMap(cMap);
            x = map->intx + cx * Map::C;
            y = map->inty + cy * Map::C;
        } else if (dir == 0) {
            stop = true;
            cMap = 0;
            cx = tcx;
            cy = tcy;
            map->setMap(0);
            //AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHHHHH
            if (cx <= Map::MINCX)
                x = cx * Map::C;
            else if (cx >= Map::MAXCX)
                x = (Map::CXSCREEN - (col[0][0].size() - cx)) * Map::C;
            else
                x = Map::CXSCREEN / 2 * Map::C;
            if (cy <= Map::MINCY)
                y = cy * Map::C;
            else if (cy >= Map::MAXCY)
                y = (Map::CYSCREEN - (col[0].size() - cy)) * Map::C;
            else
                y = Map::CYSCREEN / 2 * Map::C;
        }
    }
    return false;
}

void Player::move(int d) {
    if (d < 4)
        stop = !stop;
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
    if (cMap != 0) {
        walking = true;
        return;
    }
    switch (d) {
        case 0: //Down
            if (cy > Map::MINCY + 1 && cy < Map::MAXCY)
                map->move(d);
            else
                walking = true;
            break;
        case 1: //Left
            if (cx > Map::MINCX && cx < Map::MAXCX - 1)
                map->move(d);
            else
                walking = true;
            break;
        case 2: //Right
            if (cx > Map::MINCX + 1 && cx < Map::MAXCX)
                map->move(d);
            else
                walking = true;
            break;
        case 3: //Up
            if (cy > Map::MINCY && cy < Map::MAXCY - 1)
                map->move(d);
            else
                walking = true;
            break;
    }
}
