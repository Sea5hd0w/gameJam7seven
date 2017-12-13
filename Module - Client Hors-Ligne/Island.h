#pragma once

#include <iostream>
#include <typeinfo>
#include <list>
#include <tuple>
#include <map>
#include <string>
#include <vector>

class World;
class Dimension;

using namespace std;

class Island
{
public:
	Island(World* world, long iDIsland);
	~Island();

	bool isDimension(long iDDimension); //Test if dimension exist by ID
	void addDimension(long iDDimension, Dimension* dimension); //Add dimension by ID
	void deleteDimension(long iDDimension); //Delete dimension by ID
	Dimension* getDimension(long iDDimension); //Get dimension by ID

private:
	World* world; //Pointer to access to world
	long iDIsland; //ID of the island

	map<long, Dimension*> dimensions; //Map of all dimensions
};

