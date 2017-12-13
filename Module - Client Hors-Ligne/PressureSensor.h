#pragma once

#include "Connector.h"

class PressureSensor : public Connector
{
public:
	PressureSensor(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDMotionLess, bool status);
	~PressureSensor();

	void walkOn(Mobile* mobile);
	void walkOff(Mobile* mobile);

	void enable();
	void disable();
};

