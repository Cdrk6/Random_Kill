/*
 * A completer par equipe graphisme (Find "graph")
 */

/* 
 * File:   Player.hpp
 * Author: cedric
 *
 * Created on February 28, 2017, 11:06 AM
 */

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SDL2/SDL.h>

class Player {
public:
    Player();
    virtual ~Player();
    std::string getUsername();
    //Getters des elements graphiques du joueur
    SDL_Rect getCoordinates();
    
private:
    std::string username;
    //Elements graphiques du joueur
    SDL_Rect coordinates;

};

#endif /* PLAYER_HPP */

