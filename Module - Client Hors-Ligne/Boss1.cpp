#include "Boss1.h"

#include "World.h"
#include "LibraryCommunication.h"
#include "Dimension.h"

Boss1::Boss1(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDMonster)
	: Monster(world, iDIsland, iDDimension, point, permeability, sprite, orientation, iDMonster)
{
	this->sprite = { 0,0, 100, 100 };
	this->xSize = 300;
	this->ySize = 300;


	size_sprite_x = 100;
	size_sprite_y = 100;

	this->sizeX = make_tuple(0,1);
	this->sizeY = make_tuple(0,2);

	VX = 0;
	attack_b = true;
}


Boss1::~Boss1()
{
}


void Boss1::anim_sprite()
{
	if (attack_b)
	{
		if (this->orient)
		{
			anim2 = (anim2 + 1) % 5;
			if (anim2 == 0) anim = (anim + 1) % 15;
			if(anim2 == 0 && anim == 9) this->attack();
			if(anim2 == 4 && anim == 14) this->attack_b = false;
			this->sprite = { size_sprite_x * anim, size_sprite_y * 0, size_sprite_x, size_sprite_y };
		}
		else
		{
			anim2 = (anim2 + 1) % 5;
			if (anim2 == 0) anim = (anim + 1) % 15;
			if (anim2 == 0 && anim == 9) this->attack();
			if (anim2 == 4 && anim == 14) this->attack_b = false;
			this->sprite = { size_sprite_x * anim, size_sprite_y * 1, size_sprite_x, size_sprite_y };
		}
	}
	else if (VY > 0 && VX >= 0)
	{
		this->sprite = { 0, size_sprite_y * 0, size_sprite_x, size_sprite_y };
		this->orient = true;
	}
	else if (VY < 0 && VX >= 0)
	{
		this->sprite = { 0, size_sprite_y * 0, size_sprite_x, size_sprite_y };
		this->orient = true;
	}
	else if (VY > 0 && VX < 0)
	{
		this->sprite = { 0, size_sprite_y * 1, size_sprite_x, size_sprite_y };
		this->orient = false;
	}
	else if (VY < 0 && VX < 0)
	{
		this->sprite = { 0, size_sprite_y * 1, size_sprite_x, size_sprite_y };
		this->orient = false;
	}
	else if (VX > 0)
	{
		anim2 = (anim2 + 1) % 7;
		if (anim2 == 0) anim = (anim + 1) % 1;
		this->sprite = { size_sprite_x * anim, size_sprite_y * 0, size_sprite_x, size_sprite_y };
		this->orient = true;
	}
	else if (VX < 0)
	{
		anim2 = (anim2 + 1) % 7;
		if (anim2 == 0) anim = (anim + 1) % 1;
		this->sprite = { size_sprite_x * anim, size_sprite_y * 1, size_sprite_x, size_sprite_y };
		this->orient = false;
	}
	else
	{
		if (this->orient)
		{
			anim2 = (anim2 + 1) % 7;
			if (anim2 == 0) anim = (anim + 1) % 1;
			this->sprite = { size_sprite_x * anim, size_sprite_y * 0, size_sprite_x, size_sprite_y };
		}
		else
		{
			anim2 = (anim2 + 1) % 7;
			if (anim2 == 0) anim = (anim + 1) % 1;
			this->sprite = { size_sprite_x * anim, size_sprite_y * 1, size_sprite_x, size_sprite_y };
		}
	}
}

void Boss1::work()
{
	long x = this->world->getMainHero()->getX() - this->getX();
	long y = this->world->getMainHero()->getY() - this->getY();


	if (x > 1400 || x < -1400 || y > 1400 || y < -1400)
	{
		this->world->getIsland()->getDimension(0)->deleteMonster(this->getIDMonster());
	}
}

void Boss1::attack()
{
}

string Boss1::toString()
{
	return "boss1";
}