#include "Connector.h"

#include "PressureSensor.h"
#include "ContinuousPressureSensor.h"
#include "Door.h"


Connector::Connector(World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDMotionLess, bool status)
	: MotionLess(world, controler, iDIsland, iDDimension, point, permeability, sprite, orientation, iDMotionLess), status(status)
{
}


Connector::~Connector()
{
}

MotionLess * Connector::getConnector(long iDMotionLess, World * world, SOCKControler * controler, long iDIsland, long iDDimension, tuple<long, long, long> point, string sprite, bool status)
{
	switch (iDMotionLess)
	{
	case 12:
		return GetPressureSensor(world, controler, iDIsland, iDDimension, point, sprite, status);
		break;
	case 13:
		return GetContinuousPressureSensor(world, controler, iDIsland, iDDimension, point, sprite, status);
		break;
	case 14:
		return GetDoor(world, controler, iDIsland, iDDimension, point, sprite, status);
		break;
	}
}

bool Connector::getStatus()
{
	return this->status;
}

void Connector::setSatus(bool status)
{
	this->status = status;
}

MotionLess * Connector::GetPressureSensor(World * world, SOCKControler * controler, long iDIsland, long iDDimension, tuple<long, long, long> point, string sprite, bool status)
{
	return new PressureSensor(world, controler, iDIsland, iDDimension, point, true, sprite, 1, 12, status);
}

MotionLess * Connector::GetContinuousPressureSensor(World * world, SOCKControler * controler, long iDIsland, long iDDimension, tuple<long, long, long> point, string sprite, bool status)
{
	return new ContinuousPressureSensor(world, controler, iDIsland, iDDimension, point, true, sprite, 1, 13, status);
}

MotionLess * Connector::GetDoor(World * world, SOCKControler * controler, long iDIsland, long iDDimension, tuple<long, long, long> point, string sprite, bool status)
{
	return new Door(world, controler, iDIsland, iDDimension, point, true, sprite, 1, 14, status);
}
