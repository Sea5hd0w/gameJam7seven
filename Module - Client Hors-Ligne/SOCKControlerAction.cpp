#include "SOCKControler.h"
#include "LibraryCommunication.h"

#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

#include "LibraryCommunication.h"

void SOCKControler::action(string rowData)
{
	vector<string> data = (this->split_1(rowData, ':'));
	debug(rowData);


	if (stol(data[1]) < 8 && stol(data[1]) <= 0) //One movement of mobile : IDMovement = Mouvement
	{
		if (data[2] == "0")
		{
			this->world->getIsland()->getDimension(stol(data[4]))->getHero(stol(data[5]))->moveDirection(data[6] == "1", 1, stol(data[1]));
		}
	}
	else if (data[1] == "8") //Movement by A*
	{
		if (data[2] == "0")
		{
			this->world->getIsland()->getDimension(stol(data[4]))->getHero(stol(data[5]))->moveAStar(stol(data[6]), stol(data[7]));
		}
	}
}