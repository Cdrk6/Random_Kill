#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "Timer.hpp"
#include "IO.hpp"
#include "Controller.hpp"
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

class Display {
  public:
	// Constantes:
	static const int W; //Largeur de l'écran
	static const int H; //Hauteur de l'écran
	static const string TITLE; //Titre de la fenêtre
	static const int FPS; //Image par seconde
	static const int TICK_PER_FRAME; //Temps entre chaque images

	// Méthodes:
	Display();
	~Display();
	SDL_Renderer* getRenderer();
	void startSDL(IO*, Controller*);
	void exit();
	
  private:
	//Variables
	bool quit = false; //Détermine si l'affichage doit continuer (false) ou non (true)
	SDL_Window* gWindow = NULL;	//The window we'll be rendering to
	SDL_Renderer* gRenderer = NULL; //The window renderer
	
	//Méthodes
	bool initSDL();
};

#endif

