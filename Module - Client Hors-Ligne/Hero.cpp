#include "Hero.h"
#include "variable_static.h"


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
}


Hero::~Hero()
{
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