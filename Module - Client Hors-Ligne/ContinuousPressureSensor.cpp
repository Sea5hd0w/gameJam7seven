#include "ContinuousPressureSensor.h"

#include "LibraryCommunication.h"


ContinuousPressureSensor::ContinuousPressureSensor(World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDMotionLess, bool status)
	: Connector(world, controler, iDIsland, iDDimension, point, permeability, sprite, orientation, iDMotionLess, status)
{
	if (status) this->enable();
	else this->disable();
}


ContinuousPressureSensor::~ContinuousPressureSensor()
{
}

void ContinuousPressureSensor::walkOn(Mobile* mobile)
{
	debugMessage("[(" + to_string(get<0>(point)) + "," + to_string(get<1>(point)) + "," + to_string(get<2>(point)) + ")] : WalkOn");
	
	if (this->getStatus())
	{
		this->disable();
	}
	else
	{
		this->enable();
	}
}

void ContinuousPressureSensor::walkOff(Mobile* mobile)
{
	debugMessage("[(" + to_string(get<0>(point)) + "," + to_string(get<1>(point)) + "," + to_string(get<2>(point)) + ")] : WalkOff");
}

void ContinuousPressureSensor::enable()
{
	this->setSatus(true);
	this->sprite = { 128,0,128,128 };
}

void ContinuousPressureSensor::disable()
{
	this->setSatus(false);
	this->sprite = { 0,0,128,128 };
}
