#pragma once

#include "Connector.h"

class Door : public Connector
{
public:
	Door(World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDMotionLess, bool status);
	~Door();

	void enable();
	void disable();
};

