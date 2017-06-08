/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NPC.hpp
 * Author: cedric
 *
 * Created on June 8, 2017, 9:47 AM
 */

#ifndef NPC_HPP
#define NPC_HPP

#include <iostream>
#include <fstream>
#include <string>
#include "Entity.hpp"

using namespace std;

class NPC : public Entity {
public:
    NPC();
    NPC(const NPC& orig);
    virtual ~NPC();
    
    /*void copyArray(string* array1, string* array2);
    void copyArray(string** array1, string** array2);
    void copyArray(int* array1, int* array2);
    void copyArray(int** array1, int** array2);*/
    
private:
    int coord[2];
    string name;
    string* lines;
    string** options;
    int* choices;
    bool questState;
    int* routines[2];

};

#endif /* NPC_HPP */

