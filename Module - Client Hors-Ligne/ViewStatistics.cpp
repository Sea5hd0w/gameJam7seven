#include "ViewStatistics.h"

#include "LibraryCommunication.h"

#include "View.h"

ViewStatistics::ViewStatistics(World* world) 
	: world(world)
{
	//Get curent time
	this->timeSecond = time(NULL);
	//Iitialize both FPS to 0
	this->actualFPS, this->saveFPS = 0;

	//Load font
	//this->font = TTF_OpenFont("ressources/font/Pixeled.ttf", 14);
	//Check if font is loaded
	//if (this->font == NULL) err("Font");

	//Initialize font color 
	this->fontColor = { 255,255,255 };
}


ViewStatistics::~ViewStatistics()
{
	//Clear font
	//TTF_CloseFont(this->font);
}

void ViewStatistics::drawStatistics(int nbrObjectPrint)
{
	//Check if curent time (second) = the last time saved, if yes increment FPS, else, save the FPS to print
	if (this->timeSecond == time(NULL))
	{
		this->actualFPS++;
	}
	else
	{
		this->saveFPS = this->actualFPS;
		this->timeSecond = time(NULL);
		this->actualFPS = 0;
	}

	//Write FPS
	this->write("FPS : " + to_string(this->saveFPS), this->messageDestination = { 10, 0, 70, 30 });

	//Write nbr of element
	this->write("NBR ELEMENT : " + to_string(nbrObjectPrint), this->messageDestination = { 10, 20, 220, 30 });

	//Write nbr of sprite loaded
	this->write("NBR SPRITES : " + to_string(Sprites::getNbrSprites()), this->messageDestination = { 10, 40, 220, 30 });
	
}


/***********WARNING : LEAK MEMORY************/
void ViewStatistics::write(string txt, SDL_Rect messageDestination)
{
	/*this->surfaceMessage = TTF_RenderText_Solid(this->font, txt.c_str(), this->fontColor);
	this->Message = SDL_CreateTextureFromSurface(View::renderer, surfaceMessage);
	SDL_RenderCopy(View::renderer, this->Message, NULL, &messageDestination);/**/
}

