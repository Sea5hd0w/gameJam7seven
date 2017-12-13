#include "Hero.h"



Hero::Hero(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDHero)
	: Mobile(world, iDIsland, iDDimension, point, permeability, sprite, orientation), iDHero(iDHero)
{
}


Hero::~Hero()
{
}

long Hero::getIDHero()
{
	return this->iDHero;
}
