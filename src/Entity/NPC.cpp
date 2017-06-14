#include "NPC.hpp"

NPC::NPC(int cx, int cy, int zw, int zh, Texture* tex, string name, vector<vector<string>> col) : Entity(cx * Map::C, cy * Map::C, Map::C, Map::C, tex) {
    NPC::cx = cx;
    NPC::cy = cy;
    NPC::zw = zw;
    NPC::zh = zh;
    NPC::name = name;
    NPC::col = col;
}

NPC::~NPC() {
}

void NPC::draw(SDL_Renderer* r) {
    t->render(x, y, anim * w, dir * h, w, h);
}

void NPC::generateMove() {
    int randDir = rand() % 4;
    cout << randDir << endl;
    move(randDir);
}

void NPC::calculate(float timeStep) {
    //Reset des timer
    /*if (moving == Map::NSTEP + 1) {
        time = 0;
        moving--;
    }*/
    if (moving == Map::NSTEP + 1) {
        time = 0;
        moving--;
    }

    //Incrémentation des timer
    moveTime += timeStep;
    time += timeStep;

    //Le reste
    if (moveTime >= 2) {
        moveTime -= 2;
        //move(1);
        generateMove();
    } else if (time >= speed / Map::NSTEP) {
        time -= speed / Map::NSTEP;
        if (moving) {
            moving--;
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
                anim = 1;
            }
        }
    }
}

bool NPC::collision(int dx, int dy) {
    if (cx + dx < 0 || cy + dy < 0 || cx + dx >= col[cMap][0].size() || cy + dy >= col[cMap].size() || col[cMap][cy + dy][cx + dx] != '1') { //Si on est sur le bord de la map ou si collision
        return true;
    }

    // Modification de la matrice de collision
    col[cMap][cy][cx] = '1';
    col[cMap][cy + dy][cx + dx] = '0';
    return false;
}

void NPC::move(int d) {
    if (moving)
        return;
    dir = d;
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
    switch (dir) {
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
}

void NPC::relativeMove(int) {

}