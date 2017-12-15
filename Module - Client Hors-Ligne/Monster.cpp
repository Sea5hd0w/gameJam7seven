#include "Monster.h"

#include "LibraryCommunication.h"

Monster::Monster(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDMonster)
	: Mobile(world, iDIsland, iDDimension, point, permeability, sprite, orientation), iDMonster(iDMonster)
{
	this->sprite = { 0,0, 16, 28 };
	this->xSize = 64;
	this->ySize = 112;
}


Monster::~Monster()
{
}

long Monster::getIDMonster()
{
	return this->iDMonster;
}

void Monster::addX(double v)
{
	VX = v;
}

void Monster::addY(double v)
{
	VY = v;
}

void Monster::underAttack(Mobile* e)
{
	if (!e->shotHero)
		err("monster");
}