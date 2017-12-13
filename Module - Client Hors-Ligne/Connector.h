#pragma once

#include "MotionLess.h"

class Connector : public MotionLess
{
public:
	Connector(World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDMotionLess, bool status);
	~Connector();

	static MotionLess* getConnector(long iDMotionLess, World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, string sprite, bool status);


	bool getStatus();

protected:
	void setSatus(bool status);

private:
	bool status;

	//ID_MotionLess PressureSensor = 12
	static MotionLess* GetPressureSensor(World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, string sprite, bool status);
	//ID_MotionLess ContinuousPressureSensor = 13
	static MotionLess* GetContinuousPressureSensor(World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, string sprite, bool status);
	//ID_MotionLess ContinuousPressureSensor = 14
	static MotionLess* GetDoor(World * world, SOCKControler * controler, long iDIsland, long iDDimension, tuple<long, long, long> point, string sprite, bool status);
};

