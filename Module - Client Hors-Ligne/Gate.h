#pragma once

#include "Connector.h"

class Gate : public Connector
{
public:
	Gate(World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDMotionLess, bool status, long iDIslandDestination, long iDimensionDestination, tuple<long, long, long> pointDestination);
	~Gate();

	static MotionLess* getGate(long iDMotionLess, World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, string sprite, bool status, long iDIslandDestination, long iDimensionDestination, tuple<long, long, long> pointDestination);


	long getIDIslandDestination();
	long getIDimensionDestination();
	tuple<long, long, long> getPointDestination();

private:
	long iDIslandDestination;
	long iDimensionDestination;
	tuple<long, long, long> pointDestination;

	//ID_MotionLess GateDimension = 15
	static MotionLess* GetGateDimension(World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, string sprite, bool status, long iDIslandDestination, long iDimensionDestination, tuple<long, long, long> pointDestination);
};

