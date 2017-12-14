#pragma once
#include "Mobile.h"
class Balle :
	public Mobile
{
public:
	Balle(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDHero, int vitesse, int degat);
	~Balle();
	tuple<long, long, long> getPoint();
};

