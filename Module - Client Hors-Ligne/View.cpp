#include "View.h"
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <time.h>
#include <iostream>


#include "LibraryCommunication.h"
#include "GlobalVariable.h"

SDL_Renderer* View::renderer;

View::View(World* world)
	: world(world), run(true)
{
	// Create main windows and store it
	this->pWindow = NULL;
	this->pWindow = SDL_CreateWindow("Tale of Crysias - V 0.0.1", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		1200,
		800, SDL_WINDOW_RESIZABLE
		/*SDL_WINDOW_MAXIMIZED*/);
	//Create a static renderer : Every object can create SDL_Texture
	View::renderer = SDL_CreateRenderer(this->pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	//Create loading screen, wait 
	this->loadingScreen = new LoadingScreen(this->pWindow);

	//Create view of the world : all the map and object on it are print here
	this->mapScreen = new ViewMap(this->pWindow,world);

	//Console write object created
	gen("View created");
}


View::~View()
{
	SDL_DestroyWindow(this->pWindow);
}

pair<long, long> View::getWindowSize()
{
	int xF;
	int yF;
	SDL_GetWindowSize(this->pWindow, &xF, &yF);
	return make_pair(xF, yF);
}

void View::runView()
{
	while (run)
	{
		//std::this_thread::sleep_for(std::chrono::milliseconds(10));
		this->refresh();
	}
}

void View::stopProcess()
{
	this->run = false;
}

void View::refresh()
{
	//Delete all old sprite on the renderer : fill by a NULL color)
	SDL_RenderFillRect(View::renderer, NULL);

	//Data for statistic screen : calcultate of object print by loop
	int nbrObjectPrint = 0;

	//Check if loading of map is ending, else print loading screen
	if (this->world->isLoading())
	{
		this->loadingScreen->getScreen();
	}
	else
	{
		if (create)
		{
			for (pair<tuple<long*, long, long*, long*>, Element*> element : this->world->getIsland()->getDimension(this->world->getMainHero()->getIDDimension())->getElementsToView())
			{
				//element.second->produceHitBox(world->getIsland()->getDimension(this->world->getMainHero()->getIDDimension()));
			}
			create = false;
		}
		nbrObjectPrint = this->mapScreen->getScreen();
	}

	//Print the renderer
	SDL_RenderPresent(View::renderer);
}