#pragma once

#include "Monster.h"

class Nazi : public Monster
{
public:
	Nazi(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDMonster);
	~Nazi();

protected:
	void anim_sprite() override;
	void work() override;
};

