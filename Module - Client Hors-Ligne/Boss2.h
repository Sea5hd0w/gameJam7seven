#pragma once

#include "Monster.h"

class Boss2 : public Monster
{
public:
	Boss2(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDMonster);
	~Boss2();

protected:
	void anim_sprite() override;
	void work() override;
	void attack() override;
};

