#include "SOCKControler.h"
#include "LibraryCommunication.h"

#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

#include "LibraryCommunication.h"


void SOCKControler::loading(string rowData)
{
	switch (rowData[2]) //Check what object is loading
	{
	case '0':
		this->loadingMotionLess(rowData);
		break;
	case '1':
		this->loadingHero(rowData);
		break;
	case '2':
		this->loadingMonster(rowData);
		break;
	case '3':
		this->loadingNPC(rowData);
		break;
	}
}

void SOCKControler::loadingMotionLess(string rowData)
{
	Area* areaBuffer = NULL;

	vector<string> data = (this->split_1(rowData, ':'));

	//Check if Island exist : else create it
	if (this->world->getIsland() == NULL /* || Recive data of an other island*/)
	{
		this->world->setIsland(new Island(this->world, stol(data[2])));
	}

	//Check if Dimension exist : else create it
	if (!this->world->getIsland()->isDimension(stol(data[3])))
	{
		this->world->getIsland()->addDimension(stol(data[3]), new Dimension(this->world, stol(data[2]), stol(data[3])));
	}

	//Check if Area exist : else create it
	if (!this->world->getIsland()->getDimension(stol(data[3]))->isArea(stol(data[4]), stol(data[5])))
	{
		areaBuffer = new Area(this->world, stol(data[2]), stol(data[3]));
		this->world->getIsland()->getDimension(stol(data[3]))->addArea(stol(data[4]), stol(data[5]), areaBuffer);
	}
	else
	{
		areaBuffer = this->world->getIsland()->getDimension(stol(data[3]))->getArea(stol(data[4]), stol(data[5]));
	}

	//Create element : ID 0 to 12 : basic, 13 & 14 Connector, 15 : Gate
	if ((stol(data[7])) < 12) //If motionLess is a basic
	{
		areaBuffer->addElement(make_tuple(stol(data[4]), stol(data[5]), stol(data[6])), MotionLess::getMotionLess(stol(data[7]), this->world, this, stol(data[2]), stol(data[3]), make_tuple(stol(data[4]), stol(data[5]), stol(data[6])), data[8]));
	}
	else if((stol(data[7])) < 15)
	{
		areaBuffer->addElement(make_tuple(stol(data[4]), stol(data[5]), stol(data[6])), Connector::getConnector(stol(data[7]), this->world, this, stol(data[2]), stol(data[3]), make_tuple(stol(data[4]), stol(data[5]), stol(data[6])), data[8], data[9].at(0) == '1'));
	}
	else
	{
		areaBuffer->addElement(make_tuple(stol(data[4]), stol(data[5]), stol(data[6])), Gate::getGate(stol(data[7]), this->world, this, stol(data[2]), stol(data[3]), make_tuple(stol(data[4]), stol(data[5]), stol(data[6])), data[8], (data[9].at(0) == '1'), stol(data[10]), stol(data[11]), make_tuple(stol(data[12]), stol(data[13]), stol(data[14]))));
	}
}

void SOCKControler::loadingHero(string rowData)
{
	Area* areaBuffer = NULL;
	
	vector<string> data = (this->split_1(rowData, ':'));

	if(this->world->getMainHero()) debug("Loading hero");
	Hero* hero = new Hero(this->world, this, stol(data[2]), stol(data[3]), make_tuple(stol(data[4]), stol(data[5]), stol(data[6])), false, data[8], stoi(data[7]), stol(data[9]));

	//Check if MainHero exist : else create it
	if (this->world->getMainHero() == NULL)
	{
		this->world->setMainHero(hero);
	}

	//Check if Island exist : else create it
	if (this->world->getIsland() == NULL /* || Recive data of an other island*/)
	{
		this->world->setIsland(new Island(this->world, stol(data[2])));
	}

	//Check if Dimension exist : else create it
	if (!this->world->getIsland()->isDimension(stol(data[3])))
	{
		this->world->getIsland()->addDimension(stol(data[3]), new Dimension(this->world, stol(data[2]), stol(data[3])));
	}
	
	//Add Hero to the dimension
	this->world->getIsland()->getDimension(stol(data[3]))->addHero(hero, stol(data[9]));
	debug("AddHEro");
}

void SOCKControler::loadingMonster(string rowData)
{

}

void SOCKControler::loadingNPC(string rowData)
{

}