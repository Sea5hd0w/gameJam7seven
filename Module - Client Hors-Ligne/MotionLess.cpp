#include "MotionLess.h"
#include "PressureSensor.h"



#include "Mobile.h"

MotionLess::MotionLess(World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDMotionLess)
	: Element(world, controler, iDIsland, iDDimension, point, permeability, sprite, orientation, 0), iDMotionLess(iDMotionLess)
{
}


MotionLess::~MotionLess()
{
}

const long MotionLess::getIDMotionLess() {
	return this->iDMotionLess;
}

MotionLess * MotionLess::getMotionLess(long iDMotionLess, World * world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, string sprite)
{
	switch (iDMotionLess)
	{
	case 1:
		return GetHole(world, controler, iDIsland, iDDimension, point, sprite);
		break;
	case 2:
		return GetFloor(world, controler, iDIsland, iDDimension, point, sprite);
		break;
	case 3:
		return GetBlock(world, controler, iDIsland, iDDimension, point, sprite);
		break;
	case 4:
		return GetSlopeUpRight(world, controler, iDIsland, iDDimension, point, sprite);
		break;
	case 5:
		return GetSlopeUpLeft(world, controler, iDIsland, iDDimension, point, sprite);
		break;
	case 6:
		return GetSlopeDownRight(world, controler, iDIsland, iDDimension, point, sprite);
		break;
	case 7:
		return GetSlopeDownLeft(world, controler, iDIsland, iDDimension, point, sprite);
		break;
	case 8:
		return GetLadderUpRight(world, controler, iDIsland, iDDimension, point, sprite);
		break;
	case 9:
		return GetLadderUpLeft(world, controler, iDIsland, iDDimension, point, sprite);
		break;
	case 10:
		return GeLadderDownRight(world, controler, iDIsland, iDDimension, point, sprite);
		break;
	case 11:
		return GetLadderDownLeft(world, controler, iDIsland, iDDimension, point, sprite);
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


MotionLess * MotionLess::GetHole(World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, string sprite)
{
	return new MotionLess(world, controler, iDIsland, iDDimension, point, false, sprite, 0, 1);
}

MotionLess * MotionLess::GetFloor(World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, string sprite)
{
	return new MotionLess(world, controler, iDIsland, iDDimension, point, true, sprite, 0, 2);
}

MotionLess * MotionLess::GetBlock(World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, string sprite)
{
	return new MotionLess(world, controler, iDIsland, iDDimension, point, false, sprite, 0, 3);
}

MotionLess * MotionLess::GetSlopeUpRight(World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, string sprite)
{
	return new MotionLess(world, controler, iDIsland, iDDimension, point, false, sprite, 1, 4);
}

MotionLess * MotionLess::GetSlopeUpLeft(World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, string sprite)
{
	return new MotionLess(world, controler, iDIsland, iDDimension, point, false, sprite, 7, 5);
}

MotionLess * MotionLess::GetSlopeDownRight(World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, string sprite)
{
	return new MotionLess(world, controler, iDIsland, iDDimension, point, false, sprite, 3, 6);
}

MotionLess * MotionLess::GetSlopeDownLeft(World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, string sprite)
{
	return new MotionLess(world, controler, iDIsland, iDDimension, point, false, sprite, 5, 7);
}

MotionLess * MotionLess::GetLadderUpRight(World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, string sprite)
{
	return new MotionLess(world, controler, iDIsland, iDDimension, point, false, sprite, 1, 8);
}

MotionLess * MotionLess::GetLadderUpLeft(World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, string sprite)
{
	return new MotionLess(world, controler, iDIsland, iDDimension, point, false, sprite, 7, 9);
}

MotionLess * MotionLess::GeLadderDownRight(World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, string sprite)
{
	return new MotionLess(world, controler, iDIsland, iDDimension, point, false, sprite, 3, 10);
}

MotionLess * MotionLess::GetLadderDownLeft(World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, string sprite)
{
	return new MotionLess(world, controler, iDIsland, iDDimension, point, false, sprite, 5, 11);
}