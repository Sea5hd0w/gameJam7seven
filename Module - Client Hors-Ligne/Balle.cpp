#include "Balle.h"
#include "World.h"
#include "LibraryCommunication.h"
#include <string>

Balle::Balle(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDHero, int vitesse, int degat)
	: Monster(world, iDIsland, iDDimension, point, permeability, sprite, orientation, iDHero)
{
	VX = vitesse;
}


Balle::~Balle()
{
}


tuple<long, long, long> Balle::getPoint()
{
	return point;
}

void Balle::anim_sprite()
{
	if (VX > 0)
	{
		this->sprite = { 0, 0, 16, 16 };
	}
	else
	{
		this->sprite = { 0, 16, 16, 16 };
	}
}

