#include "Dialog.hpp"
#include "../Display.hpp"

bool Dialog::flagStop = false;

Dialog::Dialog(int x, int y, Texture* bulle1, Texture* bulle2, vector<TTF_Font*> fnts, Map* map, vector<vector < string*>> npcDat) : Entity(x, y, bulle1) {
	Dialog::bulle1 = bulle1;
	Dialog::bulle2 = bulle2;
	Dialog::fnts = fnts;
	Dialog::map = map;
	Dialog::npcDat = npcDat;
}

Dialog::~Dialog() {
}

void Dialog::draw(SDL_Renderer* r) {
	if (Map::REDRAW)
		map->redraw();
	vector<string> strs;
	if (state != -1) {
		cout << "state" << state << endl;
		boost::split(strs, *npcDat[npc][6 + state], boost::is_any_of("#"));
		bulle1->render(Display::W / 2 - t->getWidth() / 2, Display::H - t->getHeight());
		Texture txt(30 + Display::W / 2 - t->getWidth() / 2, 5 + Display::H - t->getHeight(), *npcDat[npc][5], fnts[2], r);
		Texture txt2(50 + Display::W / 2 - t->getWidth() / 2, 50 + Display::H - t->getHeight(), strs[0], fnts[3], r);
		if (strs.size() == 2) {
			state = -1;
			flagStop = true;
		} else if (strs.size() > 2) {
			bulle2->render(Display::W - 200, Display::H - bulle2->getHeight());
			if (!choice) {
				Texture txt3(20 + Display::W - 200, 30 + Display::H - bulle2->getHeight(), ">" + strs[1], fnts[3], r);
				Texture txt4(20 + Display::W - 200, 70 + Display::H - bulle2->getHeight(), strs[2], fnts[3], r);
			} else {
				Texture txt3(20 + Display::W - 200, 30 + Display::H - bulle2->getHeight(), strs[1], fnts[3], r);
				Texture txt4(20 + Display::W - 200, 70 + Display::H - bulle2->getHeight(), ">" + strs[2], fnts[3], r);
			}
		}
	}
}

void Dialog::calculate(float timeStep) {

}

void Dialog::move(int d) {

}

void Dialog::setDialog(int npc) {
	if (npc == -1) {
		if (npcDat[Dialog::npc].size() >= 6 + state + 1) {
			state = -1;
			flagStop = true;
		} else {
			state++;
			cout << "Hello" <<endl;
			/*vector<string> strs;
			boost::split(strs, *npcDat[npc][6 + state], boost::is_any_of("#"));
			if (strs.size() > 2)
				inChoice = true;*/
		}
		/*if (inChoice) {
			inChoice = false;
			gotoState(choice);
			choice = 0;
		}*/
	} else {
		state = 0;
		Dialog::npc = npc;
	}
}

void Dialog::setChoice(bool cho) {
	choice = cho;
}

void Dialog::gotoState(int choice) {
	/*for(int i = 0; i < npcDat[npc].size(); i++)
		if((*npcDat[npc][6+state+i]).size() == 1 && (*npcDat[npc][6+state+i])[0] - '0' == choice)
			state += i+1;*/
}
