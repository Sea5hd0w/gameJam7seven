#pragma once

#include "Monster.h"
#include "audio.h"

class Boss2 : public Monster
{
public:
	Boss2(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDMonster);
	~Boss2();

protected:
	int ai1;
	int ai2;

	void anim_sprite() override;
	void work() override;
	void attack() override;

	Audio *soundsBoss2;

	bool started;

	void ai();
};

