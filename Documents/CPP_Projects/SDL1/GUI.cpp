#include <iostream>
#include <cstdlib>
#include <SDL2/SDL.h>

#include "values.h"
#include "Map.h"

using namespace std;


void progLoop(SDL_Surface *screen, Map myMap) {
    myMap.displayMap(screen);
}


int main(int argc, char** argv) {
    SDL_Window* window(0);
    SDL_GLContext openGLContext(0);
    
    SDL_Init(SDL_INIT_VIDEO);
    
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    
    window = SDL_CreateWindow("SDL1 GUI", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    
    if(window == 0) {
        std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
        SDL_Quit();

        return -1;
    }
    openGLContext = SDL_GL_CreateContext(window);

    if(openGLContext == 0) {
        std::cout << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();

        return -1;
    }
    
    Map myMap;

    bool end(false);
    SDL_Event closeEvent;
    
    while (!end) {
        SDL_WaitEvent(&closeEvent);
        cout << "Salut !" << endl;
        progLoop(SDL_GetWindowSurface(window), myMap);
        cout << "Salut !" << endl;
        if (closeEvent.type == SDL_QUIT)
            end = true;
        cout << "Salut !" << endl;
        SDL_UpdateWindowSurface(window);
    }
    
    SDL_GL_DeleteContext(openGLContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}