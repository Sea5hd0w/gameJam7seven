#include "Area.h"

#include "LibraryCommunication.h"


Area::Area(World* world, long iDIsland, long iDDimension)
	: world(world), iDIsland(iDIsland), iDDimension(iDDimension)
{
	gen("Area created");
}


Area::~Area()
{
	debug("4");
	for (map<tuple<long, long, long>, MotionLess*>::iterator it = this->mapArea.begin(); it != this->mapArea.end(); it)
	{
		MotionLess* erase = it->second;
		it = this->mapArea.erase(it);
		delete(erase);
	}
}

map<tuple<long, long, long>, MotionLess*> Area::getElements()
{
	return this->mapArea;
}

bool Area::isElement(tuple<long, long, long> point)
{
	return this->mapArea.find(point) != this->mapArea.end();
}

void Area::addElement(tuple<long, long, long> point, MotionLess * element)
{
	if(!this->isElement(point))
	{
		this->mapArea.insert(std::pair<tuple<long, long, long>, MotionLess *>(point, element));
	}
	else
	{
		err("Conflict MotionLess [" + to_string(get<0>(point)) + ":" + to_string(get<1>(point)) + ":" + to_string(get<2>(point)) + "] already exist in Area Dimension [" + to_string(iDDimension) + "]");
	}
}

void Area::deleteElement(tuple<long, long, long> point)
{
	if (this->isElement(point))
	{
		delete(this->mapArea.find(point)->second);
		this->mapArea.erase(point);
	}
	else
	{
		err("Conflict MotionLess [" + to_string(get<0>(point)) + ":" + to_string(get<1>(point)) + ":" + to_string(get<2>(point)) + "] doesn't exist in Area Dimension [" + to_string(iDDimension) + "]");
	}
}

MotionLess * Area::getElement(tuple<long, long, long> point)
{
	return this->mapArea.find(point)->second;
}
