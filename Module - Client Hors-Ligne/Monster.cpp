#include "Monster.h"

#include "LibraryCommunication.h"
#include "Dimension.h"
#include "World.h"

Monster::Monster(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDMonster)
	: Mobile(world, iDIsland, iDDimension, point, permeability, sprite, orientation), iDMonster(iDMonster)
{
	this->sprite = { 0,0, 16, 28 };
	this->xSize = 64;
	this->ySize = 112;

	startAI = false;
}


Monster::~Monster()
{
	this->hits.clear();
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
	if (e->shotHero != this->shotHero)
	{
		int pv = this->life > e->life ? e->life : this->life;
		
		e->underAttack(this);
		this->loosePV(pv);
		
		//this->world->getIsland()->getDimension(0)->getElementsToView().remove(make_pair(e->getIDElementToView(), e));
		err(this->toString() + " || " + e->toString());
	}
		
}

void Monster::loosePV(int pv)
{
	this->life -= pv;
	debug(to_string(this->life) + " || " + to_string(pv));
	if (life <= 0)
	{
		for (Hitbox* h : hits)
		{
			this->world->getIsland()->getDimension(0)->deleteHitbox(h);
		}
		this->world->getIsland()->getDimension(0)->deleteMonster(this->getIDMonster());
	}
}