#pragma once

#include "Monster.h"
#include "audio.h"
#include <chrono>

class Boss2 : public Monster
{
public:
	Boss2(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDMonster);
	~Boss2();
	string toString() override;
	void shoot();
	clock_t t;
	void loosePV(int pv) override;
protected:
	void anim_sprite() override;
	void work() override;
	void attack() override;

	Audio *soundsBoss2;

	bool started;

};

