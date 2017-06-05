#include "Display.hpp"
#include "IO.hpp"
#include "Controller.hpp"

const int Display::W = 1280;
const int Display::H = 720;
const string Display::TITLE = "Random Kill";
const int Display::FPS = 60;
const int Display::TICK_PER_FRAME = 1000 / FPS;

Display::Display() {
	if (!initSDL())
		cerr << "[ECHEC] Initialisation de la SDL" << endl;
	else
		cout << "[OK] Initialisation de la SDL" << endl;
}

Display::~Display() {
	//Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

SDL_Renderer* Display::getRenderer() {
	return gRenderer;
}

bool Display::initSDL() {
	bool success = true; //Initialization flag
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) { //Initialize SDL
		cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
		success = false;
	} else {
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) //Set texture filtering to linear
			cout << "Warning: Linear texture filtering not enabled!";
		gWindow = SDL_CreateWindow(TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W, H, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS | SDL_WINDOW_INPUT_GRABBED); //Create window
		if (gWindow == NULL) {
			cerr << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
			success = false;
		} else {
			//SDL_SetWindowFullscreen(gWindow, 0);//SDL_WINDOW_FULLSCREEN); //Fullsreen
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED); //Create renderer for window
			if (gRenderer == NULL) {
				cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
				success = false;
			} else {
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF); //Initialize renderer color
				int imgFlags = IMG_INIT_PNG; //Initialize PNG loading
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
					success = false;
				}
				if (TTF_Init() == -1) { //Initialize SDL_ttf
					cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << endl;
					success = false;
				}
			}
		}
	}
	return success;
}

void Display::startSDL(IO* io, Controller* c) {
	SDL_Event e; //Event handler
	Timer fpsTimer; //The frames per second timer
	Timer capTimer; //The frames per second cap timer
	//Timer stepTimer; //Keeps track of time between steps
	int frameTicks = 0;
	int countedFPS = 0; //Start counting frames per second
	//float timeStep = 0;
	fpsTimer.start();

	while (!quit) { //While application is running
		capTimer.start(); //Start cap timer
		float avgFPS = countedFPS / (fpsTimer.getTicks() / 1000.f); //Calculate and correct fps
		if (avgFPS > 2000000)
			avgFPS = 0;

		//c->updateButtonsPressed();
		while (SDL_PollEvent(&e) != 0) { //Handle events on queue
			if (e.type == SDL_QUIT) { //If user requests quit
				quit = true;
			}

			//dot.handleEvent(e); //Handle input for the dot
		}
		//float timeStep = stepTimer.getTicks() / 1000.f; //Calculate time step
		//dot.move(timeStep); //Move for time step
		//stepTimer.start(); //Restart step timer

		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
		SDL_RenderClear(gRenderer);

		//Render textures
		io->getImages()[0]->render(10, 100);
		io->getImages()[1]->render(15, 120);
		io->getImages()[3]->render(0, 0);
		Texture fps(to_string(avgFPS), io->getFonts()[0], gRenderer);
		fps.render(20, 20);

		SDL_RenderPresent(gRenderer); //Update screen
		++countedFPS; //Real FPS
		frameTicks = capTimer.getTicks();
		if (frameTicks < TICK_PER_FRAME) { //If frame finished early
			SDL_Delay(TICK_PER_FRAME - frameTicks); //Wait remaining time
		}
	}
}

void Display::exit() {
	quit = true;
}
