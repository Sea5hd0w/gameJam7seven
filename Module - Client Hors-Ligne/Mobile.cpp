#include "Mobile.h"

#include "World.h"
#include "Dimension.h"
#include "AStar.h"

#include "LibraryCommunication.h"

Mobile::Mobile(World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation)
	: Element(world, controler, iDIsland, iDDimension, point, permeability, sprite, orientation, 1)
{
	this->path = new AStar(world, this);
	this->speed_run = 200;
	this->split = 10;
}


Mobile::~Mobile()
{
}

bool Mobile::isMovePossible(long iDDimension_parameter, tuple<long, long, long> element, int orientation)
{
	if (this->getWorld()->getIsland()->getDimension(iDDimension_parameter)->isElement(element))
	{
		return this->getWorld()->getIsland()->getDimension(iDDimension_parameter)->getElement(element)->getPermeability();
	}
	else
	{
		return false;
	}
}

bool Mobile::isMoveOutOfDimension(long iDDimension_parameter, tuple<long, long, long> element, int orientation)
{
	return false;
}

void Mobile::moveAStar(long xDestination, long yDestination)
{
	if(this->getX() != xDestination && this->getY() != yDestination) this->path->calculateShortWay(xDestination, yDestination);
}

void Mobile::moveDirection(bool run, int distance, int direction)
{
	switch (direction)
	{
	case 0:
		this->moveTop(run, distance);
		break;
	case 1:
		this->moveTopRight(run, distance);
		break;
	case 2:
		this->moveRight(run, distance);
		break;
	case 3:
		this->moveDownRight(run, distance);
		break;
	case 4:
		this->moveDown(run, distance);
		break;
	case 5:
		this->moveDownLeft(run, distance);
		break;
	case 6:
		this->moveLeft(run, distance);
		break;
	case 7:
		this->moveTopLeft(run, distance);
		break;
	default:
		break;
	}
}

void Mobile::moveTop(bool run, int distance)
{
	for (int i = 0; i < distance; i++) {
		if (move(run, -100, -100, 0, 0)) mov("[ ? ] : [ TOP ]  \t-\t[(" + to_string(get<0>(this->getPoint())) + ", " + to_string(get<1>(getPoint())) + ", " + to_string(get<2>(getPoint())) + ")]");
	}
}

void Mobile::moveTopRight(bool run, int distance)
{
	for (int i = 0; i < distance; i++) {
		if (move(run, 0, -100, 0, 1)) mov( "[ ? ] : [ TOPRIGHT ]\t-\t[(" + to_string(get<0>(this->getPoint())) + ", " + to_string(get<1>(getPoint())) + ", " + to_string(get<2>(getPoint())) + ")]");
	}
}

void Mobile::moveTopLeft(bool run, int distance)
{
	for (int i = 0; i < distance; i++) {
		if (move(run, -100, 0, 0, 7)) mov( "[ ? ] : [ TOPLEFT ]\t-\t[(" + to_string(get<0>(this->getPoint())) + ", " + to_string(get<1>(getPoint())) + ", " + to_string(get<2>(getPoint())) + ")]");
	}
}

void Mobile::moveRight(bool run, int distance)
{
	for (int i = 0; i < distance; i++) {
		if (move(run, 100, -100, 0, 2)) mov( "[ ? ] : [ RIGHT ]\t-\t[(" + to_string(get<0>(this->getPoint())) + ", " + to_string(get<1>(getPoint())) + ", " + to_string(get<2>(getPoint())) + ")]");
	}
}

void Mobile::moveLeft(bool run, int distance)
{
	for (int i = 0; i < distance; i++) {
		if (move(run, -100, 100, 0, 6)) mov( "[ ? ] : [ LEFT ]\t-\t[(" + to_string(get<0>(this->getPoint())) + ", " + to_string(get<1>(getPoint())) + ", " + to_string(get<2>(getPoint())) + ")]");
	}
}

void Mobile::moveDownRight(bool run, int distance)
{
	for (int i = 0; i < distance; i++) {
		if (move(run, 100, 0, 0, 3)) mov( "[ ? ] : [ DOWNRIGHT ]\t-\t[(" + to_string(get<0>(this->getPoint())) + ", " + to_string(get<1>(getPoint())) + ", " + to_string(get<2>(getPoint())) + ")]");
	}
}

void Mobile::moveDownLeft(bool run, int distance)
{
	for (int i = 0; i < distance; i++) {
		if (move(run, 0, 100, 0, 5)) mov( "[ ? ] : [ DOWNLEFT ]\t-\t[(" + to_string(get<0>(this->getPoint())) + ", " + to_string(get<1>(getPoint())) + ", " + to_string(get<2>(getPoint())) + ")]");
	}
}

void Mobile::moveDown(bool run, int distance)
{
	for (int i = 0; i < distance; i++) {
		if (move(run, 100, 100, 0, 4)) mov( "[ ? ] : [ DOWN ]\t-\t[(" + to_string(get<0>(this->getPoint())) + ", " + to_string(get<1>(getPoint())) + ", " + to_string(get<2>(getPoint())) + ")]");
	}
}

void Mobile::teleportHere(long iDDimension, tuple<long, long, long> point_finish)
{
	if (this->getIDDimension() != iDDimension)
	{
		this->getWorld()->getIsland()->getDimension(iDDimension)->addHero(this->getWorld()->getIsland()->getDimension(this->getIDDimension())->getHero(0), 0);
		this->getWorld()->getIsland()->getDimension(this->getIDDimension())->deleteHero(0);
	}
	this->setPoint(point_finish);
	this->setIDDimension(iDDimension);

	this->getWorld()->getIsland()->getDimension(this->getIDDimension())->loadElementsToView();
}

bool Mobile::middleMove(tuple<long, long, long> point_start, tuple<long, long, long> point_finish)
{
	return false;
}

bool Mobile::move(bool run, int x_move, int y_move, int z_move, int direction)
{
	if (this->isMovePossible(this->getIDDimension(), make_tuple(this->getX() + x_move, this->getY() + y_move, this->getZ() + z_move), 0))
	{
		moveUnsafe(run, x_move, y_move, z_move, true, true, direction, 0);
		return true;
	}
	else
	{
		if (moveLadder(run, x_move, y_move, z_move, direction)) return true;
		else return moveSlope(run, x_move, y_move, z_move, direction);
	}
}

void Mobile::moveUnsafe(bool run, int x_move, int y_move, int z_move, bool walkOn, bool walkOff, int direction, int iDMove)
{
	tuple<long, long, long> point_start = this->getPoint();
	int wait_time = this->speed_run / split;
	if (!run) wait_time = wait_time / 2;

	for (int i = 0; i < split; i++)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(wait_time));

		get<0>(this->point) = get<0>(this->point) + (x_move / split);
		get<1>(this->point) = get<1>(this->point) + (y_move / split);
		get<2>(this->point) = get<2>(this->point) + (z_move / split);

		//this->sprite = { i*128,((direction+1 + (iDMove * (7-((direction-1)/2))))  * 128), 128,128 };

		if (i == split / 2)
		{
			if(walkOff) this->getWorld()->getIsland()->getDimension(this->getIDDimension())->getElement(point_start)->walkOff(this);
			if (this->middleMove(point_start, make_tuple(get<0>(point_start) + x_move, get<1>(point_start) + y_move, get<2>(point_start) + z_move))) i = split;
		}
	}

	if (walkOn)this->getWorld()->getIsland()->getDimension(this->getIDDimension())->getElement(this->point)->walkOn(this);

	this->sprite = { 0, 0, 128,128 };

	this->getWorld()->getIsland()->getDimension(this->getIDDimension())->sortElementsToView();
}

bool Mobile::moveSlope(bool run, int x_move, int y_move, int z_move, int direction)
{
	MotionLess* element;

	if (this->getWorld()->getIsland()->getDimension(this->getIDDimension())->isElement(make_tuple(this->getX() + x_move, this->getY() + y_move, this->getZ() + z_move)))
	{
		element = this->getWorld()->getIsland()->getDimension(this->getIDDimension())->getElement(make_tuple(this->getX() + x_move, this->getY() + y_move, this->getZ() + z_move));
		if (element->getIDMotionLess() >= 4 && element->getIDMotionLess() <= 7)
		{
			if (element->getOrientation() == ((direction + 4) % 8))
			{
				moveUnsafe(run, x_move, y_move, z_move+50, false, true, direction, 1);
				return true;
			}
		}
	}
	else if (this->getWorld()->getIsland()->getDimension(this->getIDDimension())->isElement(make_tuple(this->getX() + x_move, this->getY() + y_move, this->getZ() + z_move + 50)))
	{
		element = this->getWorld()->getIsland()->getDimension(this->getIDDimension())->getElement(make_tuple(this->getX() + x_move, this->getY() + y_move, this->getZ() + z_move+50));
		if (element->getIDMotionLess() >= 4 && element->getIDMotionLess() <= 7)
		{
			if (element->getOrientation() == ((direction + 4) % 8))
			{
				moveUnsafe(run, x_move, y_move, z_move + 100, false, false, direction, 1);
				return true;
			}
		}
		else if (element->getPermeability())
		{
			moveUnsafe(run, x_move, y_move, z_move + 50, true, false, direction, 1);
			return true;
		}
	}
	else if (this->getWorld()->getIsland()->getDimension(this->getIDDimension())->isElement(make_tuple(this->getX() + x_move, this->getY() + y_move, this->getZ() + z_move-100)))
	{
		element = this->getWorld()->getIsland()->getDimension(this->getIDDimension())->getElement(make_tuple(this->getX() + x_move, this->getY() + y_move, this->getZ() + z_move-100));
		if (element->getIDMotionLess() >= 4 && element->getIDMotionLess() <= 7)
		{
			if (element->getOrientation() == direction)
			{
				moveUnsafe(run, x_move, y_move, z_move - 50, false, true, direction, 1);
				return true;
			}
		}
	}
	else if (this->getWorld()->getIsland()->getDimension(this->getIDDimension())->isElement(make_tuple(this->getX() + x_move, this->getY() + y_move, this->getZ() + z_move - 150)))
	{
		element = this->getWorld()->getIsland()->getDimension(this->getIDDimension())->getElement(make_tuple(this->getX() + x_move, this->getY() + y_move, this->getZ() + z_move - 150));
		if (element->getIDMotionLess() >= 4 && element->getIDMotionLess() <= 7)
		{
			if (element->getOrientation() == direction)
			{
				moveUnsafe(run, x_move, y_move, z_move - 100, false, false, direction, 1);
				return true;
			}
		}
		else if (this->getWorld()->getIsland()->getDimension(this->getIDDimension())->getElement(make_tuple(this->getX() + x_move, this->getY() + y_move, this->getZ() + z_move - 50))->getPermeability())
		{
			moveUnsafe(run, x_move, y_move, z_move - 50, true, false, direction, 1);
			return true;
		}
	}
	else if (this->getWorld()->getIsland()->getDimension(this->getIDDimension())->isElement(make_tuple(this->getX() + x_move, this->getY() + y_move, this->getZ() + z_move - 50)))
	{
		element = this->getWorld()->getIsland()->getDimension(this->getIDDimension())->getElement(make_tuple(this->getX() + x_move, this->getY() + y_move, this->getZ() + z_move - 50));
		if (element->getPermeability())
		{
			moveUnsafe(run, x_move, y_move, z_move - 50, true, false, direction, 1);
			return true;
		}
	}
	return false;
}

bool Mobile::moveLadder(bool run, int x_move, int y_move, int z_move, int direction)
{
	MotionLess* element;

	if (this->getWorld()->getIsland()->getDimension(this->getIDDimension())->isElement(make_tuple(this->getX() + x_move, this->getY() + y_move, this->getZ() + z_move)))
	{
		element = this->getWorld()->getIsland()->getDimension(this->getIDDimension())->getElement(make_tuple(this->getX() + x_move, this->getY() + y_move, this->getZ() + z_move));
		if (element->getIDMotionLess() >= 8 && element->getIDMotionLess() <= 11)
		{
			if (element->getOrientation() == ((direction + 4) % 8))
			{
				moveUnsafe(run, 0, 0, z_move + 50, false, true, direction, 2);
				return true;
			}
		}
	}
	else if (this->getWorld()->getIsland()->getDimension(this->getIDDimension())->isElement(make_tuple(this->getX() + x_move, this->getY() + y_move, this->getZ() + z_move + 50)))
	{
		element = this->getWorld()->getIsland()->getDimension(this->getIDDimension())->getElement(make_tuple(this->getX() + x_move, this->getY() + y_move, this->getZ() + z_move + 50));
		if (element->getIDMotionLess() >= 8 && element->getIDMotionLess() <= 11)
		{
			if (element->getOrientation() == ((direction + 4) % 8))
			{
				moveUnsafe(run, 0, 0, z_move + 100, false, false, direction, 2);
				return true;
			}
		}
		else if (element->getPermeability())
		{
			moveUnsafe(run, x_move, y_move, z_move + 50, true, false, direction, 2);
			return true;
		}
	}
	else if (this->getWorld()->getIsland()->getDimension(this->getIDDimension())->isElement(make_tuple(this->getX() + 0, this->getY() + 0, this->getZ() + z_move - 100)))
	{
		element = this->getWorld()->getIsland()->getDimension(this->getIDDimension())->getElement(make_tuple(this->getX() + 0, this->getY() + 0, this->getZ() + z_move - 100));
		if (element->getIDMotionLess() >= 8 && element->getIDMotionLess() <= 11)
		{
			if (element->getOrientation() == direction)
			{
				moveUnsafe(run, x_move, y_move, z_move - 50, false, true, direction, 2);
				return true;
			}
		}
	}
	else if (this->getWorld()->getIsland()->getDimension(this->getIDDimension())->isElement(make_tuple(this->getX() - x_move, this->getY() - y_move, this->getZ() + z_move - 150)))
	{
		element = this->getWorld()->getIsland()->getDimension(this->getIDDimension())->getElement(make_tuple(this->getX() - x_move, this->getY() - y_move, this->getZ() + z_move - 150));
		if (element->getIDMotionLess() >= 8 && element->getIDMotionLess() <= 11)
		{
			if (element->getOrientation() == direction)
			{
				moveUnsafe(run, 0, 0, z_move - 100, false, false, direction, 2);
				return true;
			}
		}
		else if (this->getWorld()->getIsland()->getDimension(this->getIDDimension())->getElement(make_tuple(this->getX() + 0, this->getY() + 0, this->getZ() + z_move - 50))->getPermeability())
		{
			moveUnsafe(run, 0, 0, z_move - 50, true, false, direction, 2);
			return true;
		}
	}
	else if (this->getWorld()->getIsland()->getDimension(this->getIDDimension())->isElement(make_tuple(this->getX() + 0, this->getY() + 0, this->getZ() + z_move - 50)))
	{
		element = this->getWorld()->getIsland()->getDimension(this->getIDDimension())->getElement(make_tuple(this->getX() + 0, this->getY() + 0, this->getZ() + z_move - 50));
		if (element->getPermeability())
		{
			moveUnsafe(run, 0, 0, z_move - 50, true, false, direction, 2);
			return true;
		}
	}
	return false;
}
