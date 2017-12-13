#pragma once

#include "Mobile.h"

class Hero : public Mobile {

public:
	Hero(World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDHero);
	~Hero();

	long getIDHero();

private:
	long iDHero;

};

