#pragma once

#include "Mobile.h"
#include "Ammo.h"
class Hero : public Mobile {

public:
	Hero(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDHero);
	~Hero();
	Ammo* Arme;
	long getIDHero();
	void setAmmo(Ammo* Arme);
private:
	long iDHero;

};

