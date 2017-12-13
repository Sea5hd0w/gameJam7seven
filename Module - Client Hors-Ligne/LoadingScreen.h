#pragma once
#include "SDL.h"
#include <ctime>
#include <map>
#include <tuple>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <time.h>
#include <iostream>

using namespace std;

class LoadingScreen
{
public:
	LoadingScreen(SDL_Window* pWindow);
	~LoadingScreen();

	void getScreen(); //Print the screen make by the object

private:
	SDL_Window* pWindow; //Pointer on MainWindow to print on it

	map<int, SDL_Texture*> spritesLoadingScreen; //List of image of the loading
	
	int gifCycle; //Curent position of the image to print

	void loadSprites(); //Load image of the loading animation
};

