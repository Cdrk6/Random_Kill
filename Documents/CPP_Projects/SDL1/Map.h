#ifndef MAP_H
#define MAP_H

#include <SDL/SDL.h>
#include "values.h"

class Map {
   
private :
    bool mapTable[10][10];
    SDL_Rect tilesPos [10][10];
    
public :
    Map();
    void displayMap (SDL_Surface *screen);
    ~Map();
    
};

#endif /* MAP_H */

