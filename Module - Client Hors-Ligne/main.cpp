#include <iostream>
#include "SDL.h"
//#include "SDL_ttf.h"

#include "LibraryCommunication.h"
#include "Controler.h"

//		RELEASE ONLY
/*INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
PSTR lpCmdLine, INT nCmdShow)
{/**/
int main(int argc, char* args[])
{
	std::cout << "Module - Client Hors-Ligne" << std::endl;

	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		err("Error initializing SDL2");
		exit(EXIT_FAILURE);
	}
	/*
	if (TTF_Init() == -1)
	{
		err("Error initializing TTF_Init");
		exit(EXIT_FAILURE);
	}*/
	
	new Controler();
	
	SDL_Quit();
	//TTF_Quit();

	return 0;
}