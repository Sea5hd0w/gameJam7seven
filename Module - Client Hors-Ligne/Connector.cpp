#include "Connector.h"


Connector::Connector(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDMotionLess, bool status)
	: MotionLess(world, iDIsland, iDDimension, point, permeability, sprite, orientation, iDMotionLess), status(status)
{
}


Connector::~Connector()
{
}

MotionLess * Connector::getConnector(long iDMotionLess, World * world, long iDIsland, long iDDimension, tuple<long, long, long> point, string sprite, bool status)
{
	switch (iDMotionLess)
	{
	case 12:
		break;
	case 13:
		break;
	case 14:
		break;
	}
	return NULL;
}

bool Connector::getStatus()
{
	return this->status;
}

void Connector::setSatus(bool status)
{
	this->status = status;
}

