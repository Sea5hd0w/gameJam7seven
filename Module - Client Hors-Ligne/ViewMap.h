#pragma once
#include "SDL.h"

#include <map>
#include <tuple>
#include <chrono>
#include <thread>
#include <time.h>
#include <iostream>

#include "World.h"
#include "Island.h"
#include "Dimension.h"
#include "Area.h"
#include "MotionLess.h"

using namespace std;

class ViewMap
{
public:
	ViewMap(SDL_Window* pWindow, World* world);
	~ViewMap();

	int getScreen(); //Print the screen make by the object
	
private:
	SDL_Window* pWindow; //Pointer on MainWindow to print on it

	World* world; //Object world to acccess to map & mobiles

	long convertX(long x, long y, long z, int xS, int yS, int xSize, int ySize); //Convert the position of an element in X position on the window : relative to the window
	long convertY(long x, long y, long z, int xS, int yS, int xSize, int ySize); //Convert the position of an element in Y position on the window : relative to the window
	long convertXHero(long x, long y, long z, int xS, int yS, int xSize, int ySize, long xW, long yW); //Convert the position of an element in Y position on the window : centered on the position given by MainHero
	long convertYHero(long x, long y, long z, int xS, int yS, int xSize, int ySize, long xW, long yW); //Convert the position of an element in Y position on the window : centered on the position given by MainHero

	int sizeSprite_L = 128; //Size of width classic sprite
	int sizeSprite_H = 128; //Size of height classic sprite


	int heightCase = 40; //Size of height classic case
	int wighthCase = 80; //Size of width classic case
	int positionCase = 20; //Distance from image's bottom and case's bottom
	int positionCasesSide = 24; //Distance from image's side and case's side
};

