#include "GateDimension.h"

#include "LibraryCommunication.h"

#include "Mobile.h"

GateDimension::GateDimension(World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDMotionLess, bool status, long iDIslandDestination, long iDimensionDestination, tuple<long, long, long> pointDestination)
	: Gate(world, controler, iDIsland, iDDimension, point, permeability, sprite, orientation, iDMotionLess, status, iDIslandDestination, iDimensionDestination, pointDestination)
{
	if (status) this->enable();
	else this->disable();
}


GateDimension::~GateDimension()
{
}

void GateDimension::walkOn(Mobile* mobile)
{
	if(status) mobile->teleportHere(this->getIDimensionDestination(), this->getPointDestination());
}

void GateDimension::walkOff(Mobile* mobile)
{
}

void GateDimension::enable()
{
	this->status = true;
	this->setPermeability(true);
	this->sprite = { 128,0,128,128 };
}

void GateDimension::disable()
{
	this->status = false;
	this->setPermeability(false);
	this->sprite = { 0,0,128,128 };
}
