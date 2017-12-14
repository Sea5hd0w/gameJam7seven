#pragma once
#include "Monster.h"

class HellWolf : public Monster
{
public:
	HellWolf(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDMonster);
	~HellWolf();

protected:
	void anim_sprite() override;
	void work() override;

};

