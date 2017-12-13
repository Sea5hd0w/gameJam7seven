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

#include "MotionLess.h"

using namespace std;

class Area
{
public:
	Area(World* world, long iDIsland, long iDDimension);
	~Area();

	map<tuple<long, long, long>, MotionLess*> getElements(); //Getter elements' list of Area

	bool isElement(tuple<long, long, long> point); // Test if element exist in Area's elements list
	void addElement(tuple<long, long, long> point, MotionLess* element); // Add element to list
	void deleteElement(tuple<long, long, long> point); //Remove element to list
	MotionLess* getElement(tuple<long, long, long> point); // Get element by position

private:
	World* world; //Pointer to access to world
	long iDIsland; //ID of the island
	long iDDimension; //ID of the Dimension

	map<tuple<long, long, long>, MotionLess*> mapArea; // List of elements' map

};

