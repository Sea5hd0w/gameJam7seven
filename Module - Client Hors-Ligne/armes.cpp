#include "armes.h"



armes::armes(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDMotionLess)  
	: MotionLess(world, iDIsland, iDDimension, point, permeability, sprite, 0, 3)
{

}

void armes::walkOn(Hero* hero) {
	hero->setAmmo(this->getAmmo());
	this

}

Ammo* armes::getAmmo()
{
	return this->Arme;
}


armes::~armes()
{
}
