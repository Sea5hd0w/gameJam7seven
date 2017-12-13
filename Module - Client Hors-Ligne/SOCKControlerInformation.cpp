#include "SOCKControler.h"
#include "LibraryCommunication.h"

#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

#include "LibraryCommunication.h"

void SOCKControler::information(string rowData)
{
	vector<string> data = (this->split_1(rowData, ':'));


	if (data[1] == "MainLoadEnd") //End of the main load : Heros, Stuff, Map of the dimension of the MainHero
	{
		this->world->getIsland()->getDimension(stol(data[3]))->loadElementsToView();
		this->world->setLoading(false);
	}
	else if (data[1] == "EnableDisable") //Activate or desactivate a connectable
	{

		if (data[7] == "1")	this->world->getIsland()->getDimension(stol(data[3]))->getElement(make_tuple(stol(data[4]), stol(data[5]), stol(data[6])))->enable();
		else this->world->getIsland()->getDimension(stol(data[3]))->getElement(make_tuple(stol(data[4]), stol(data[5]), stol(data[6])))->disable();
	}
	else if (data[1] == "Delete") //Delete all an area
	{
		debug("1");
		this->world->getIsland()->getDimension(stol(data[3]))->deleteArea(stol(data[4]), stol(data[5]));
	}
}