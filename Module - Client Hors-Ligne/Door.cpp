#include "Door.h"



Door::Door(World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDMotionLess, bool status)
	: Connector(world, controler, iDIsland, iDDimension, point, permeability, sprite, orientation, iDMotionLess, status)
{
	if (status) this->enable();
	else this->disable();
}


Door::~Door()
{
}

void Door::enable()
{
	this->setSatus(true);
	this->setPermeability(false);
	this->sprite = { 128,0,128,128 };
}

void Door::disable()
{
	this->setSatus(false);
	this->setPermeability(true);
	this->sprite = { 0,0,128,128 };
}
