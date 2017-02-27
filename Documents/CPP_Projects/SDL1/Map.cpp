#include "Map.h"
#include "values.h"
    
Map::Map() :
    mapTable {
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 1, 0, 0, 1, 1, 1, 1, 0, 0},
        {0, 1, 0, 0, 1, 0, 0, 1, 0, 0},
        {0, 1, 1, 1, 1, 0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 1, 1, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1}
    }
{      
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            tilesPos[i][j] = {i*WIDTH/10, j*HEIGHT/10, WIDTH/10, HEIGHT/10};
        }
    }
}


void Map::displayMap(SDL_Surface *screen) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            SDL_FillRect(screen, &tilesPos[i][j], SDL_MapRGB(screen->format, mapTable[i][j]*255, mapTable[i][j]*255, mapTable[i][j]*255));
        }
    }
}


Map::~Map () {
    for (int i = 0; i < 10; i++) {
        free(mapTable[i]);
        free(tilesPos[i]);
    }
}