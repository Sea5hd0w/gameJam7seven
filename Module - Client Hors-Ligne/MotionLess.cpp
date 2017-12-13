

#include "Mobile.h"

MotionLess::MotionLess(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDMotionLess)
	: Element(world, iDIsland, iDDimension, point, permeability, sprite, orientation, 0), iDMotionLess(iDMotionLess)
{
}


MotionLess::~MotionLess()
{
}

const long MotionLess::getIDMotionLess() {
	return this->iDMotionLess;
}

MotionLess * MotionLess::getMotionLess(long iDMotionLess, World * world, long iDIsland, long iDDimension, tuple<long, long, long> point, string sprite)
{
	switch (iDMotionLess)
	{
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;
	case 10:
		break;
	case 11:
		break;
	default:
		return NULL;
		break;
	}
}

void MotionLess::enable()
{
}

void MotionLess::disable()
{
}

void MotionLess::walkOn(Mobile* mobile)
{
}

void MotionLess::walkOff(Mobile* mobile)
{
}

void MotionLess::Notify(bool onOff) {
}

void MotionLess::setIDMotionLess(long new_IDMotionLess) {
	this->iDMotionLess = new_IDMotionLess;
}