#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <string>
using namespace std;

class Display {
  public:
	// Constantes:
	static const int W = 800; //Largeur de l'écran
	static const int H = 600; //Hauteur de l'écran
	static const string TITLE;

	// Méthodes:
	Display();
	//Display(const Display& orig);
	~Display();
  private:

};

//const string Display::TITLE = "Random Kill";

#endif

