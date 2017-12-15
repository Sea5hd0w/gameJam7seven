#pragma once

#include "Monster.h"

class Boss1 : public Monster
{
public:
	Boss1(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDMonster);
	~Boss1();

protected:
	void anim_sprite() override;
	void work() override;
	void attack() override;
};

