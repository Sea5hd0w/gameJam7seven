#pragma once
#include "SDL.h"
//#include "SDL_ttf.h"

#include <chrono>
#include <thread>
#include <time.h>
#include <iostream>

#include "World.h"
#include "Island.h"
#include "Dimension.h"

using namespace std;

class ViewStatistics
{
public:
	ViewStatistics(World* world);
	~ViewStatistics();

	void drawStatistics(int nbrObjectPrint);

private:
	World* world; //Object world to acccess to informations about it

	//TTF_Font* font; //Pointer of the font
	SDL_Color fontColor; //Color of the font
	SDL_Surface* surfaceMessage; //SDL_Surface to print
	SDL_Texture* Message; //SDL_Texture create by the message
	SDL_Rect messageDestination; // Rectangle destination of message


	int actualFPS; // Current FPS : incrementable each frame
	int saveFPS; // Stable FPS to print

	time_t timeSecond; //Time T savec

	void write(string txt, SDL_Rect messageDestination1); //Write stats
};

