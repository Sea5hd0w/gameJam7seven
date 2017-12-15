#pragma once
#include "Element.h"
#include "MotionLess.h"
#include "Mobile.h"

class Monster : public Mobile
{
public:
	Monster(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDHero);
	virtual ~Monster();

	long getIDMonster();
	void addX(double v);
	void addY(double v);
	void underAttack(Mobile* e) override;

	

private:
	long iDMonster;
};