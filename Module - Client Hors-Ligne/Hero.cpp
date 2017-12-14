#include "Hero.h"
#include "variable_static.h"
#include <tuple>
#include "LibraryCommunication.h"


Hero::Hero(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDHero)
	: Mobile(world, iDIsland, iDDimension, point, permeability, sprite, orientation), iDHero(iDHero)
{
	this->sprite = { 0,0, 16, 28 };
	this->xSize = 64;
	this->ySize = 112;

	this->vitesse = variable::VITESSE_HERO_X;
	this->vitesseJump = variable::VITESSE_HERO_JUMP;

	this->sizeX = 1;
	this->sizeY = 2;
	this->Arme = new Ammo(world, iDIsland, iDDimension, point, permeability, "ressources/graphics/motionless/Bullet_Debug_Type1.bmp", orientation, iDHero, 10, 50);
	
}


Hero::~Hero()
{
}

void Hero::setAmmo(Ammo* Arme) {
	this->Arme = Arme;
}

void Hero::shoot() {
	debug("ddd");
	this->Arme->shoot(point);
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