#include "Hero.h"



Hero::Hero(World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDHero)
	: Mobile(world, controler, iDIsland, iDDimension, point, permeability, sprite, orientation), iDHero(iDHero)
{
}


Hero::~Hero()
{
}

long Hero::getIDHero()
{
	return this->iDHero;
}
