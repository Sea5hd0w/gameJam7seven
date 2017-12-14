#include "Hero.h"
#include <tuple>


Hero::Hero(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDHero)
	: Mobile(world, iDIsland, iDDimension, point, permeability, sprite, orientation), iDHero(iDHero)
{
	this->sprite = { 0,0, 16, 28 };
	this->xSize = 64;
	this->ySize = 112;
}


Hero::~Hero()
{
}

void Hero::setAmmo(Ammo* Arme) {
	this->Arme = Arme;
}

void Hero::shoot() {
	
	this->Arme->shoot(std::get<1>(point));
}

long Hero::getIDHero()
{
	return this->iDHero;
}

void Hero::addX(double v)
{
	VX = v;
}

void Hero::addY(double v)
{
	VY = v;
}