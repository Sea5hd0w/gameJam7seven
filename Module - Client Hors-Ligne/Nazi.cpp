#include "Nazi.h"

#include "World.h"
#include "LibraryCommunication.h"
#include "Dimension.h"

Nazi::Nazi(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDMonster)
	: Monster(world, iDIsland, iDDimension, point, permeability, sprite, orientation, iDMonster)
{
	this->sprite = { 0,0, 32, 32 };
	this->xSize = 96;
	this->ySize = 96;


	size_sprite_x = 32;
	size_sprite_y = 32;

	this->sizeX = make_tuple(0,1);
	this->sizeY = make_tuple(0,2);

	VX = -1;
}


Nazi::~Nazi()
{
}


void Nazi::anim_sprite()
{
	if (VY > 0 && VX >= 0)
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
		if (anim2 == 0) anim = (anim + 1) % 4;
		this->sprite = { size_sprite_x * anim, size_sprite_y * 0, size_sprite_x, size_sprite_y };
		this->orient = true;
	}
	else if (VX < 0)
	{
		anim2 = (anim2 + 1) % 7;
		if (anim2 == 0) anim = (anim + 1) % 4;
		this->sprite = { size_sprite_x * anim, size_sprite_y * 1, size_sprite_x, size_sprite_y };
		this->orient = false;
	}
	else
	{
		if (this->orient)
		{
			anim2 = (anim2 + 1) % 7;
			if (anim2 == 0) anim = (anim + 1) % 4;
			this->sprite = { size_sprite_x * anim, size_sprite_y * 0, size_sprite_x, size_sprite_y };
		}
		else
		{
			anim2 = (anim2 + 1) % 7;
			if (anim2 == 0) anim = (anim + 1) % 4;
			this->sprite = { size_sprite_x * anim, size_sprite_y * 1, size_sprite_x, size_sprite_y };
		}
	}
}

void Nazi::work()
{
	long x = this->world->getMainHero()->getX() - this->getX();
	long y = this->world->getMainHero()->getY() - this->getY();


	if (x > 1400 || x < -1400 || y > 1400 || y < -1400)
	{
		this->world->getIsland()->getDimension(0)->deleteMonster(this->getIDMonster());
	}
}

string Nazi::toString()
{
	return "nazi";
}