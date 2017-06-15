#include "Player.hpp"
#include "NPC.hpp"
#include "Dialog.hpp"

int Player::cMap = 0;

Player::Player(int cx, int cy, Texture* t, Map* m, vector<vector<string*>> col, vector<NPC*> npcs, Dialog* d) : Entity(20 * Map::C, 12 * Map::C, Map::C, Map::C, t) {
	Player::cx = cx;
	Player::cy = cy;
	Player::map = m;
	Player::col = col;
	Player::npcs = npcs;
	Player::dia = d;
}

Player::~Player() {

}

void Player::draw(SDL_Renderer* r) {
	t->render(x, y, anim * w, dir * h, w, h);
}

void Player::calculate(float timeStep) {
	if (Dialog::flagStop) {
		dialog = false;
		npcs[npc]->dialog = false;
		Dialog::flagStop = false;
	}
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
			//cout << x << "; " << y << endl;
			walking = false;
			anim = 1;
			if (!stop) {
				if (fDir != -1) {
					Player::move(fDir);
					fDir = -1;
				} else Player::move(dir);
			}
		}
	}
}

bool Player::collision(int dx, int dy) {
	if (cx + dx < 0 || cy + dy < 0 || cx + dx >= (*col[cMap][0]).size() || cy + dy >= col[cMap].size() || (*col[cMap][cy + dy])[cx + dx] == '0') { //Si on est sur le bord de la map ou si collision
		stop = true;
		return true;
	}

	// Modification de la matrice de collision
	if ((*col[cMap][cy])[cx] - '0' < 2)
		(*col[cMap][cy])[cx] = '1';
	if ((*col[cMap][cy + dy])[cx + dx] - '0' < 2)
		(*col[cMap][cy + dy])[cx + dx] = '0';

	//Changement de map
	if ((*col[cMap][cy + dy])[cx + dx] - '0' > 1) {
		if (cMap == 0) {
			stop = true;
			cMap = (*col[cMap][cy + dy])[cx + dx] - '0' - 1;
			tcx = cx;
			tcy = cy;
			cx = stoi(*col[9][(cMap - 1)*2]);
			cy = stoi(*col[9][(cMap - 1)*2 + 1]);
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
				x = (Map::CXSCREEN - ((*col[0][0]).size() - cx)) * Map::C;
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

void Player::stopMoving() {
	stop = true;
}

void Player::move(int d) {
	if (dialog) {
		if (d == 3)
			dia->setChoice(false);
		else if (d == 0)
			dia->setChoice(true);
		return;
	}
	stop = false;
	if (moving) {
		if (dir != d)
			fDir = d;
		return;
	}
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
	//cout << cx << " ; " << cy << endl;
	if (cMap != 0) {
		walking = true;
		return;
	}
	switch (dir) {
		case 0: //Down
			if (cy > Map::MINCY + 1 && cy < Map::MAXCY)
				relativeMove(dir);
			else
				walking = true;
			break;
		case 1: //Left
			if (cx > Map::MINCX && cx < Map::MAXCX - 1)
				relativeMove(dir);
			else
				walking = true;
			break;
		case 2: //Right
			if (cx > Map::MINCX + 1 && cx < Map::MAXCX)
				relativeMove(dir);
			else
				walking = true;
			break;
		case 3: //Up
			if (cy > Map::MINCY && cy < Map::MAXCY - 1)
				relativeMove(dir);
			else
				walking = true;
			break;
	}
}

void Player::relativeMove(int d) {
	map->move(d);
}

void Player::startDialog() {
	if (dialog) {
		dia->setDialog(-1);
		return;
	}
	if (cMap != 0)
		return;
	int fcx = cx, fcy = cy, look = 0;
	switch (dir) {
		case 0: //Down
			fcy++;
			look = 3;
			break;
		case 1: //Left
			fcx--;
			look = 2;
			break;
		case 2: //Right
			fcx++;
			look = 1;
			break;
		case 3: //Up
			fcy--;
			look = 0;
			break;
	}
	npc = checkNPC(fcx, fcy);
	if ((*col[0][fcy])[fcx] == '1' || npc == -1 || !npcs[npc]->alive)
		return;
	dialog = true;
	npcs[npc]->move(look);
	npcs[npc]->dialog = true;
	dia->setDialog(npc);
}

int Player::checkNPC(int fcx, int fcy) {
	for (int i = 0; i < npcs.size(); i++)
		if (npcs[i]->getCX() == fcx && npcs[i]->getCY() == fcy)
			return i;
	return -1;
}

void Player::shoot() {
	if (moving || dialog)
		return;
	int fcx = 0, fcy = 0;
	switch (dir) {
		case 0: //Down
			fcy++;
			break;
		case 1: //Left
			fcx--;
			break;
		case 2: //Right
			fcx++;
			break;
		case 3: //Up
			fcy--;
			break;
	}
	checkLine(fcx, fcy);
}

void Player::checkLine(int dx, int dy) {
	int fcx = cx+dx;
	int fcy = cy+dy;
	npc2 = checkNPC(fcx, fcy);
	while((*col[0][fcy])[fcx] == '1' || npc2 == -1){
		fcx+=dx;
		fcy+=dy;
		npc2 = checkNPC(fcx, fcy);
	}
	npcs[npc2]->alive = false;
}
