#pragma once

#include "Monster.h"

class Nazi : public Monster
{
public:
	Nazi(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDMonster);
	~Nazi();
	string toString() override;
protected:
	void anim_sprite() override;
	void work() override;
};

