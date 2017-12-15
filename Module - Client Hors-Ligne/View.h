#pragma once
#include "SDL.h"

#include <map>
#include <tuple>

#include "World.h"
#include "LoadingScreen.h"
#include "ViewMap.h"

using namespace std;

class View
{
public:
	View(World* world);
	~View();

	static SDL_Renderer* renderer; //Static renderer for alow object to create SDL_Texture & Print
	pair<long, long> getWindowSize(); //Get curent size of main window

	void runView(); //Loop for print screen
	void stopProcess(); //Stop the loop

private:
	LoadingScreen* loadingScreen; //Object loading, print loading screen when map can not be print
	ViewMap* mapScreen; //Object map : print the curent map

	World* world; //Object world to acccess to map & mobiles

	SDL_Window* pWindow; //Pointer on main window

	bool run; //Bool control the main view loop (while(run))
	bool create = true;;
	void refresh(); //Function refresh the main window
};

