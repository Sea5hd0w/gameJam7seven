#include "Island.h"

#include "LibraryCommunication.h"

Island::Island(World* world, long iDIsland) : world(world), iDIsland(iDIsland)
{
	gen("Island created");
}


Island::~Island()
{
}

bool Island::isDimension(long iDDimension)
{
	return this->dimensions.find(iDDimension) != this->dimensions.end();
}

void Island::addDimension(long iDDimension, Dimension * dimention)
{
	if (!this->isDimension(iDDimension))
	{
		this->dimensions[iDDimension] = dimention;
	}
	else
	{
		printf("[ERR] : Conflict iDDimension [%d] already exist in Island [%d]", iDDimension, iDIsland);
	}
}

void Island::deleteDimension(long iDDimension)
{
}

Dimension * Island::getDimension(long iDDimension)
{
	if (this->isDimension(iDDimension))
	{
		return this->dimensions[iDDimension];
	}
	else
	{
		err("Island : No Dimension[" + to_string(iDDimension) + "] found");
		return NULL;
	}
	
}
