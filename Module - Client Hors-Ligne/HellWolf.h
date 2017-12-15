#pragma once
#include "Monster.h"
#include "audio.h"

class HellWolf : public Monster
{
public:
	HellWolf(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDMonster);
	~HellWolf();

	string toString() override;
protected:
	void anim_sprite() override;
	void work() override;
	
	Audio *soundsHellWolf;

	bool started;

};

