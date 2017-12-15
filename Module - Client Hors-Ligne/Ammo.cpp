#pragma comment(lib, "winmm.lib")
#include <windows.h>
#include <mmsystem.h>
#include "Ammo.h"
#include "View.h"
#include "Balle.h"
#include "variable_static.h"
#include <thread>
#include "LibraryCommunication.h"
#include <iostream>


Ammo::Ammo(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, int priority, int vitesse, int degat)
	: Element(world, iDIsland,  iDDimension,  point,  permeability,  sprite,orientation,priority)
{
	
	this->world = world;
	this->iDIsland = iDIsland;
	this->iDDimension = iDDimension;
	this->point = point;
	this->permeability = permeability;
	//this->sprite = sprite;
	this->orientation = orientation;
	this->degat = degat;
	this->vitesse = vitesse;
	this->idBullet = 1000;
	SDL_Init(SDL_INIT_AUDIO);
	initAudio();
	// load WAV file

	this->sounds = createAudio("ressources/sounds/arme3.wav", 0, SDL_MIX_MAXVOLUME / 2);


}


Ammo::~Ammo()
{
	freeAudio(sounds);
}

void Ammo::playSound()
{
	playSoundFromMemory(this->sounds, SDL_MIX_MAXVOLUME/2);
}

void Ammo::shoot(tuple<long, long, long> pointH)
{	
	
	this->playSound();

	Monster* monst;
	if (this->world->getMainHero()->getOrient())
	{
		monst = new Balle(this->getWorld(), iDIsland, iDDimension, pointH, permeability, "ressources/graphics/motionless/Bullet_Debug_Type1.bmp", orientation, this->idBullet, 10, 50, false);
	}
	else monst = new Balle(this->getWorld(), iDIsland, iDDimension, pointH, permeability, "ressources/graphics/motionless/Bullet_Debug_Type1.bmp", orientation, this->idBullet, -10, 50, false);

	this->world->getIsland()->getDimension(0)->addMonster(monst, this->idBullet);
	this->world->getIsland()->getDimension(0)->addElementsToView(monst);

	this->idBullet++;
}

void Ammo::shoot(tuple<long, long, long> pointH, int vitesse, Mobile* mob)
{

	this->playSound();

	Monster* monst;
	if (!mob->getOrient())
	{
		monst = new Balle(this->getWorld(), iDIsland, iDDimension, pointH, permeability, "ressources/graphics/motionless/Bullet_Debug_Type2.bmp", orientation, this->idBullet, vitesse, 50, true);
	}
	else
	{
		monst = new Balle(this->getWorld(), iDIsland, iDDimension, make_tuple(get<0>(pointH) + 64 * 3, get<1>(pointH), 0), permeability, "ressources/graphics/motionless/Bullet_Debug_Type2.bmp", orientation, this->idBullet, -vitesse, 50, true);
	}

	this->world->getIsland()->getDimension(0)->addMonster(monst, this->idBullet);
	this->world->getIsland()->getDimension(0)->addElementsToView(monst);

	this->idBullet++;
}

void Ammo::printSprite(int xPosition, int yPosition)
{
	int y = yPosition;
	if (this->ySize > 64) y = y - (this->ySize - 64);

	SDL_Rect dest = { xPosition,  y, this->xSize, this->ySize };
	try {
		SDL_RenderCopy(View::renderer, this->p_sprite, &this->sprite, &dest);
	}
	catch (exception)
	{
	}
}

