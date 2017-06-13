#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "Timer.hpp"
#include "IO.hpp"
#include "Controller.hpp"
#include "Entity/Entity.hpp"
#include "Entity/Player.hpp"
#include "Entity/Map.hpp"
#include "Entity/Menu.hpp"
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

using namespace std;

class Display {
  public:
	// Constantes:
	static const int W; //Largeur de l'écran
	static const int H; //Hauteur de l'écran
	static const string TITLE; //Titre de la fenêtre
	static const int FPS; //Image par seconde
	static const int TICK_PER_FRAME; //Temps entre chaque images
	static int menu;
	static bool quit; //Détermine si l'affichage doit continuer (false) ou non (true)
	
	// Méthodes:
	Display();
	~Display();
	SDL_Renderer* getRenderer();
	void startSDL(IO*, Controller*);
	void exit();
	
  private:
	//Variables
	SDL_Window* gWindow = NULL;	//The window we'll be rendering to
	SDL_Renderer* gRenderer = NULL; //The window renderer
	vector<TTF_Font*> fnts; //Toutes les polices
	vector<Entity*> ents; //Les entités à afficher
	vector<Entity*> menuEnts; //Les entités du menu
	vector<Entity*> gameEnts; //Les entités du jeu
	SDL_Event e; //Event handler
	float avgFPS = 0; //Moyenne fps par sec
	int time = 0;
	
	//Méthodes
	bool initSDL();
	void handleEvents(Controller*); //Gère tous les évenements
	void calculate(float); //Calcule tout (déplacements...)
	void draw(); //Dessine tout
	void initResources(IO*); //Initialise les ressouces (graphiques...)
	void initMenuEnts(IO*); //Initialise les entités du menu
	void initGameEnts(IO*); //Initialise les entités du jeu
};

#endif

