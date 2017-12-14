#pragma once
#include "MotionLess.h"
#include "Ammo.h"
#include "Hero.h"
class armes :
	public MotionLess
{
public:
	armes();
	armes(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDMotionLess);
	~armes();
	Ammo* Arme;
	void walkOn(Hero* hero); //Interac with MotionLess
	Ammo* getAmmo();
protected:
	

private:


};

