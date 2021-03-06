#pragma once

#include "Mobile.h"
class Hero : public Mobile {

public:
	Hero(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDHero);
	~Hero();
	//Ammo* Arme;
	long getIDHero();
	void setAmmo(Ammo* Arme);
	void shoot() override;
	void addX(double v);
	void addY(double v);
	void shoot(long y);
	void underAttack(Mobile* e) override;
	string toString() override;
private:
	long iDHero;

};

