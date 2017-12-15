#pragma once

#include <iostream>
#include <typeinfo>
#include <list>
#include <tuple>
#include <map>
#include <string>
#include <vector>
#include <time.h>

#include "SDL.h"
#include "Sprites.h"
#include "variable_static.h"
#include "HittBox.h"

#define POSX get<0>(point)
#define POSY get<1>(point)

using namespace std;

class World;

class Element
{
public:
	Element(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, int priority);
	~Element();
	
	const tuple<long, long, long> getPoint();
	const bool getPermeability();
	const int getOrientation();

	void printSprite(int xPosition, int yPosition);

	long getIDDimension();
	long getIDIsland();
	World* getWorld();

	const long getX();
	const long getY();
	const long getZ();

	pair<tuple<long*, long, long*, long*>, Element*> getElementToView();
	tuple<long*, long, long*, long*> getIDElementToView();

	virtual void move();


	
protected:
	void setPoint(tuple<long, long, long> new_point);
	void setPermeability(bool new_permeability);
	void setOrientation(int new_orientation);
	void setIDDimension(long new_IDDImension);

	tuple<long, long, long> point;
	
	SDL_Rect sprite;

	int xSize;
	int ySize;
	long iDDimension;
	long iDIsland;
	int priority;
	World* world;
	bool permeability;
	SDL_Texture* p_sprite;
	string pathSprite;
	int orientation;

	tuple<int,int> sizeX; //en unité de block
	tuple<int,int> sizeY; //en unité de block

	list<Hitbox*> hits;
private:

	
	

	
	
};

