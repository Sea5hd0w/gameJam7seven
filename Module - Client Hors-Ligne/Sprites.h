#pragma once
#include "SDL.h"

#include <iostream>
#include <typeinfo>
#include <list>
#include <tuple>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Sprites
{
public:
	Sprites();
	~Sprites();

	static SDL_Texture* Sprites::addSprite(string path); // Load and add sprite to the map
	static void Sprites::deleteSprite(string path); // Remove sprite from map
	static int getNbrSprites(); // Get number of sprites (use for statistics)

private:	
	static map<string, tuple<SDL_Texture*, int>> sprites; // Map of sprites

};

