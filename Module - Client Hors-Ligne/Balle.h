#pragma once
#include "Monster.h"
class Balle :
	public Monster
{
public:
	Balle(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDHero, int vitesse, int degat);
	~Balle();

	tuple<long, long, long> getPoint();

protected:
	void anim_sprite() override;
};

