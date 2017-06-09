/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/*
 *
 */

/* 
 * File:   NPC.cpp
 * Author: cedric
 * 
 * Created on June 8, 2017, 9:47 AM
 */

#include "NPC.hpp"

NPC::NPC(/*int* aCoord, string aName, string* aLines, string** aOptions, int* aChoices, int** aRoutines*/) : Entity(0, 0, NULL) {
	/*coord = new (nothrow) int[2];
	copyArray(aCoord, coord);
	name = aName;
	lines = new (nothrow) string[vector.size(aLines)];
	copyArray(aLines, lines);
	options = new (nothrow) string*[vector.size(aOptions)];
	for (int i = 0; i < vector.size(aOptions); ++i)
		options[i] = new (nothrow) string[vector.size(aOptions[i])];
	choices = new (nothrow) int[vector.size(aChoices)];*/

}

NPC::~NPC() {
}

void NPC::draw(SDL_Renderer* r) {
}

void NPC::calculate(float timeStep) {
}

void NPC::move(int dir) {
}