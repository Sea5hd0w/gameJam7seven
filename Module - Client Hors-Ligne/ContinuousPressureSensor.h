#pragma once

#include "Connector.h"

class ContinuousPressureSensor : public Connector
{
public:
	ContinuousPressureSensor(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDMotionLess, bool status);
	~ContinuousPressureSensor();

	void walkOn(Mobile* mobile);
	void walkOff(Mobile* mobile);

	void enable();
	void disable();
};

