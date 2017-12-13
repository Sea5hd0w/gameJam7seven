#pragma once

#include "Gate.h"

class GateDimension : public Gate
{
public:
	GateDimension(World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDMotionLess, bool status, long iDIslandDestination, long iDimensionDestination, tuple<long, long, long> pointDestination);
	~GateDimension();
	
	void walkOn(Mobile* mobile);
	void walkOff(Mobile* mobile);

	void enable();
	void disable();

private:
	bool status;
	long iDIslandDestination;
	long iDimensionDestination;
	tuple<long, long, long> pointDestination;
};

