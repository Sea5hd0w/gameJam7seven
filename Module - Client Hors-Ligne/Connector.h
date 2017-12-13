#pragma once

#include "MotionLess.h"

class Connector : public MotionLess
{
public:
	Connector(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDMotionLess, bool status);
	~Connector();

	static MotionLess* getConnector(long iDMotionLess, World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, string sprite, bool status);


	bool getStatus();

protected:
	void setSatus(bool status);

private:
	bool status;
};

