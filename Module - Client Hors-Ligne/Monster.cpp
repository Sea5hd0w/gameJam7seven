#include "Monster.h"

#include "LibraryCommunication.h"
#include "Dimension.h"
#include "World.h"
#include "Ammo.h"

Monster::Monster(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDMonster)
	: Mobile(world, iDIsland, iDDimension, point, permeability, sprite, orientation), iDMonster(iDMonster)
{
	this->sprite = { 0,0, 16, 28 };
	this->xSize = 64;
	this->ySize = 112;

	startAI = false;
	this->Arme = new Ammo(world, iDIsland, iDDimension, point, permeability, "ressources/graphics/motionless/Bullet_Debug_Type1.bmp", orientation, 0, 10, 50);
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

void Monster::shoot()
{
	this->Arme->shoot(make_tuple(POSX,POSY-64,0), -10, this);
}