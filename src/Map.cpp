#include "Map.hpp"

#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 808;
const int SCREEN_HEIGHT = 830;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;
SDL_Surface* gHelloWorld2 = NULL;
SDL_Surface* gHelloWorld3 = NULL;

bool init() {
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    } else {
        //Create window
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        } else {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }

    return success;
}

SDL_Surface* loadMedia(char const* img) {
    SDL_Surface* var;

    //Load splash image
    var = SDL_LoadBMP(img);
    //gHelloWorld2 = SDL_LoadBMP( "maison1.bmp" );
    if (var == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", img, SDL_GetError());
    }
    return var;
}

void close() {
    //Deallocate surface
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;

    //Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

void start() {
    //Start up SDL and create window
    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        SDL_Rect positionFond;
        gHelloWorld = loadMedia("res/Fond2.bmp");
        gHelloWorld2 = loadMedia("res/Maison2.bmp");
        positionFond.x = 330;
        positionFond.y = 350;
        gHelloWorld3 = loadMedia("res/maison1.bmp");
        SDL_BlitSurface(gHelloWorld3, NULL, gHelloWorld, &positionFond);

        //Load media
        if (gHelloWorld == NULL || gHelloWorld2 == NULL || gHelloWorld3 == NULL) {
            printf("Failed to load media!\n");
        } else {
            //Apply the image
            SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
            SDL_BlitSurface(gHelloWorld2, NULL, gScreenSurface, NULL);
            SDL_BlitSurface(gHelloWorld3, NULL, gScreenSurface, NULL);


            //Update the surface
            SDL_UpdateWindowSurface(gWindow);

            //Wait two seconds
            SDL_Delay(8000);
        }
    }

    //Free resources and close SDL
    close();
}

Map::Map() {
}

Map::Map(const Map& orig) {
}

Map::~Map() {
}

