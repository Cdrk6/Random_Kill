#include "Display.hpp"

const int Display::W = 1280;
const int Display::H = 768;
const string Display::TITLE = "Random Kill";
const int Display::FPS = 60;
const int Display::TICK_PER_FRAME = 1000 / FPS;
int Display::menu = 0;
bool Display::quit = false;

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

    //Destroy entities
    for (int i = 0; i < menuEnts.size(); i++)
        delete menuEnts[i];
    for (int i = 0; i < gameEnts.size(); i++)
        delete gameEnts[i];
}

SDL_Renderer* Display::getRenderer() {
    return gRenderer;
}

bool Display::initSDL() {
    bool success = true; //Initialization flag
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK) < 0) { //Initialize SDL
        cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
        success = false;
    } else {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) //Set texture filtering to linear
            cout << "Warning: Linear texture filtering not enabled!";
        gWindow = SDL_CreateWindow(TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W, H, SDL_WINDOW_SHOWN /*| SDL_WINDOW_BORDERLESS | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_INPUT_GRABBED*/); //Create window
        if (gWindow == NULL) {
            cerr << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
            success = false;
        } else {
            //SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN); //SDL_WINDOW_FULLSCREEN); //Fullsreen
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
                //Initialize SDL_mixer 
                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
                    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
                    success = false;
                }
            }
        }
    }
    return success;
}

void Display::startSDL(IO* io, Controller* c) {
    initResources(io);
    Timer fpsTimer; //The frames per second timer
    Timer capTimer; //The frames per second cap timer
    Timer stepTimer; //Keeps track of time between steps
    int frameTicks = 0;
    int countedFPS = 0; //Start counting frames per second
    float timeStep = 0;
    fpsTimer.start();

    while (!quit) { //While application is running
        capTimer.start(); //Start cap timer
        avgFPS = countedFPS / (fpsTimer.getTicks() / 1000.f); //Calculate and correct fps
        if (avgFPS > 2000000)
            avgFPS = 0;

        handleEvents(c);

        timeStep = stepTimer.getTicks() / 1000.f; //Calculate time step
        calculate(timeStep);
        stepTimer.start(); //Restart step timer
        
        if(menu == 1)
            ents = gameEnts;

        draw();

        SDL_RenderPresent(gRenderer); //Update screen
        ++countedFPS; //Real FPS
        frameTicks = capTimer.getTicks();
        if (frameTicks < TICK_PER_FRAME) //If frame finished early
            SDL_Delay(TICK_PER_FRAME - frameTicks); //Wait remaining time
    }
}

void Display::initResources(IO* io) {
    imgs = io->getImages();
    fnts = io->getFonts();
    initMenuEnts();
    initGameEnts(io);
    ents = menuEnts;
}

void Display::handleEvents(Controller* c) {
    c->updateButtonsPressed(ents);
    while (SDL_PollEvent(&e) != 0) { //Handle events on queue
        if (e.type == SDL_QUIT) //If user requests quit
            quit = true;
        //dot.handleEvent(e); //Handle input for the dot
    }
}

void Display::calculate(float timeStep) {
    for (int i = 0; i < ents.size(); i++)
        ents[i]->calculate(timeStep);
}

void Display::draw() {
    //Clear screen
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
    SDL_RenderClear(gRenderer);

    //Render all textures
    for (int i = 0; i < ents.size(); i++)
        ents[i]->draw(gRenderer);

    //imgs[0]->render(10, 100);
    //imgs[1]->render(15, 120);
    Texture fps(20, 20, to_string(avgFPS), fnts[0], gRenderer);
}

void Display::initMenuEnts() {
    menuEnts = vector<Entity*>();
    vector<Texture*> texs;
    texs.push_back(imgs[12]);
    texs.push_back(imgs[13]);
    texs.push_back(imgs[14]);
    texs.push_back(imgs[15]);
    texs.push_back(imgs[16]);
    menuEnts.push_back(new Menu(texs));
}

void Display::initGameEnts(IO* io) {
    gameEnts = vector<Entity*>();
    int initcx = 40;//43;
    int initcy = 43;//112;
    vector<Texture*> texs;
    texs.push_back(imgs[4]);
    texs.push_back(imgs[6]);
    texs.push_back(imgs[7]);
    texs.push_back(imgs[8]);
    texs.push_back(imgs[9]);
    texs.push_back(imgs[10]);
    texs.push_back(imgs[11]);
    Map* m = new Map(initcx - 20, initcy - 12, texs);
    gameEnts.push_back(m);
    gameEnts.push_back(new Player(initcx, initcy, imgs[5], m, io->getData()));
}

void Display::exit() {
    quit = true;
}
