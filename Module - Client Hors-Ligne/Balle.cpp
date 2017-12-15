#include "Balle.h"
#include "World.h"
#include "LibraryCommunication.h"
#include "Dimension.h"
#include <string>

Balle::Balle(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDHero, int vitesse, int degat, bool shotHero)
	: Monster(world, iDIsland, iDDimension, point, permeability, sprite, orientation, iDHero)
{
	VX = vitesse;
	this->affectedByGravity = false;
	this->produceHitBox(world->getIsland()->getDimension(this->world->getMainHero()->getIDDimension()));
	this->shotHero = shotHero;
}


Balle::~Balle()
{
}


tuple<long, long, long> Balle::getPoint()
{
	return point;
}

void Balle::anim_sprite()
{
	if (VX > 0)
	{
		this->sprite = { 0, 0, 16, 16 };
	}
	else
	{
		this->sprite = { 0, 16, 16, 16 };
	}
}

void Balle::work()
{
	long x = this->world->getMainHero()->getX() - this->getX();
	long y = this->world->getMainHero()->getY() - this->getY();

	if (x > 700 || x < -700 || y > 700 || y < -700 || VX == 0)
	{
		this->world->getIsland()->getDimension(0)->deleteMonster(this->getIDMonster());
	}

	for (Hitbox* h : hits)
	{
		h->detect_collision();
	}
}

void Balle::underAttack(Mobile* e)
{
	this->loosePV(e->life);
}

string Balle::toString()
{
	return "balle";
}