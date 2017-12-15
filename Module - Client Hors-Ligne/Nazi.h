#pragma once

#include "Monster.h"
#include "audio.h"

class Nazi : public Monster
{
public:
	Nazi(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDMonster);
	~Nazi();
	string toString() override;
protected:
	int ai1;
	int ai2;
	void anim_sprite() override;
	void work() override;

	Audio *soundsBoss2;

	bool started;

	void ai();
};

