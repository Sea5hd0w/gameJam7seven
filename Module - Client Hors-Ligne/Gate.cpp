#include "Gate.h"

#include "LibraryCommunication.h"

#include "GateDimension.h"

Gate::Gate(World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDMotionLess, bool status, long iDIslandDestination, long iDimensionDestination, tuple<long, long, long> pointDestination)
	: Connector(world, controler, iDIsland, iDDimension, point, permeability, sprite, orientation, iDMotionLess, status), iDIslandDestination(iDIslandDestination), iDimensionDestination(iDimensionDestination), pointDestination(pointDestination)
{
}


Gate::~Gate()
{
}

MotionLess * Gate::getGate(long iDMotionLess, World * world, SOCKControler * controler, long iDIsland, long iDDimension, tuple<long, long, long> point, string sprite, bool status, long iDIslandDestination, long iDimensionDestination, tuple<long, long, long> pointDestination)
{
	switch (iDMotionLess)
	{
	case 15:
		return GetGateDimension(world, controler, iDIsland, iDDimension, point, sprite, status, iDIslandDestination, iDimensionDestination, pointDestination);
		break;
	}
}

long Gate::getIDIslandDestination()
{
	return this->iDimensionDestination;
}

long Gate::getIDimensionDestination()
{
	return iDimensionDestination;
}

tuple<long, long, long> Gate::getPointDestination()
{
	return pointDestination;
}

MotionLess * Gate::GetGateDimension(World * world, SOCKControler * controler, long iDIsland, long iDDimension, tuple<long, long, long> point, string sprite, bool status, long iDIslandDestination, long iDimensionDestination, tuple<long, long, long> pointDestination)
{
	return new GateDimension(world, controler, iDIsland, iDDimension, point, true, sprite, 1, 15, status, iDIslandDestination, iDimensionDestination, pointDestination);
}
