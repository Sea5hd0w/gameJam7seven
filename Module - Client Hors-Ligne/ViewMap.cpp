#include "ViewMap.h"

#include "LibraryCommunication.h"

#include "View.h"


ViewMap::ViewMap(SDL_Window* pWindow, World* world)
	: pWindow(pWindow), world(world)
{
}


ViewMap::~ViewMap()
{
}

int ViewMap::getScreen()
{
	SDL_Rect dest = { 0 + this->world->getMainHero()->getX() , 0, 600, 224 };

	SDL_RenderCopy(View::renderer, this->world->getIsland()->getDimension(0)->getBackground(), &dest, NULL);

	//i = number of spirte print by the loop. Initialise to 0
	int i = 0;

	//Loop for each element to print in list of the curent mainHero's dimension
	for (pair<tuple<long*, long, long*, long*>, Element*> element : this->world->getIsland()->getDimension(this->world->getMainHero()->getIDDimension())->getElementsToView())
	{
		//Get coordinate of element
		int x = *get<2>(element.first);
		int y = *get<3>(element.first);
		int z = *get<0>(element.first);

		//Size of the sprite to print : default take for the moment
		int xSize = sizeSprite_L;
		int ySize = sizeSprite_H;

		//Get main window current size
		int xWindow;
		int yWindow;
		SDL_GetWindowSize(this->pWindow, &xWindow, &yWindow);

		element.second->move();
		//Ask to element to print itself, give it the coordinate to print
		element.second->printSprite(convertXHero(x, y, z, wighthCase, heightCase, xSize, ySize, xWindow, yWindow), convertYHero(x, y, z, wighthCase, heightCase, xSize, ySize, xWindow, yWindow));
		i++;
	}
	return i;
}

long ViewMap::convertX(long x, long y, long z, int xS, int yS, int xSize, int ySize)
{
	//Get main window current size
	int xF;
	int yF;
	SDL_GetWindowSize(this->pWindow, &xF, &yF);
	return (0.5 * xF) - (0.5 * xS) + (0.5 * xS * x / 100) - (0.5 * xS * y / 100) - ((xSize - 128) / 2);
}

long ViewMap::convertY(long x, long y, long z, int xS, int yS, int xSize, int ySize)
{
	//Get main window current size
	int xF;
	int yF;
	SDL_GetWindowSize(this->pWindow, &xF, &yF);
	return 0.5 * yS * x / 100 + 0.5 * yS * y / 100 - z / 100.0 * 30 - (ySize - 128);
}

long ViewMap::convertXHero(long x, long y, long z, int xS, int yS, int xSize, int ySize, long xW, long yW)
{
	//Get main window current size
	int xF;
	int yF;
	SDL_GetWindowSize(this->pWindow, &xF, &yF);


	long t = ((x - this->world->getMainHero()->getX()) / 100)*xSize + xW / 2 - xSize/2 ;
	t = ((x - this->world->getMainHero()->getX()))*xSize + xW / 2 - xSize / 2;
	t = x - this->world->getMainHero()->getX() + xF / 2;
	return t;
	//return (0.5 * xF) - (0.5 * xS) + (0.5 * xS * (x - this->world->getMainHero()->getX()) / 100) - (0.5 * xS * (y - this->world->getMainHero()->getY()) / 100) - ((xSize - 128) / 2) - positionCasesSide;
}

long ViewMap::convertYHero(long x, long y, long z, int xS, int yS, int xSize, int ySize, long xW, long yW)
{
	//Get main window current size
	int xF;
	int yF;
	SDL_GetWindowSize(this->pWindow, &xF, &yF);
	
	long t = (y / 100) * xSize;
	t = y;
	return t;
	//return 0.5 * yS * (x - this->world->getMainHero()->getX()) / 100 + 0.5 * yS * (y - this->world->getMainHero()->getY()) / 100 - z / 100.0 * 30 - (ySize - 128) + ((yW/2) - ySize/2);
}