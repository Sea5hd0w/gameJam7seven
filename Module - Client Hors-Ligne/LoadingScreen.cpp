#include "LoadingScreen.h"
#include "LibraryCommunication.h"

#include "View.h"

LoadingScreen::LoadingScreen(SDL_Window* pWindow)
	: pWindow(pWindow), gifCycle(0)
{
	this->loadSprites();
}


LoadingScreen::~LoadingScreen()
{
}



void LoadingScreen::getScreen()
{
	//Increment the position of the sprite to print with modulo loop throught 0 to nbr of image
	gifCycle = (gifCycle + 1) % this->spritesLoadingScreen.size() + 1;

	//Get main window current size
	int wWindow = 0;
	int hWindow = 0;
	SDL_GetWindowSize(this->pWindow, &wWindow, &hWindow);

	//Create rectangle destination to print image
	SDL_Rect dest = { wWindow/2 - 50, hWindow/2 - 50, 100, 100 };
	//Print image on renderer
	SDL_RenderCopy(View::renderer, this->spritesLoadingScreen[gifCycle], NULL, &dest);
}

void LoadingScreen::loadSprites()
{
	//Initialise SDL_Surface
	SDL_Surface* loadingSprite = NULL;

	//Loop throught the image of the animation to load them into a list
	for (int x = 1; x < 31; x++)
	{
		loadingSprite = SDL_LoadBMP(("ressources/graphics/loading/loading (" + to_string(x) + ").bmp").c_str());
		
		if (loadingSprite == NULL) err("Path to sprite");

		this->spritesLoadingScreen.insert(pair<int, SDL_Texture*>(x, SDL_CreateTextureFromSurface(View::renderer, loadingSprite)));
	}
}
