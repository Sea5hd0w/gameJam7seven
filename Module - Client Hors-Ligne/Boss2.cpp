#include "Boss2.h"

#include "World.h"
#include "LibraryCommunication.h"
#include "Dimension.h"

Boss2::Boss2(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDMonster)
	: Monster(world, iDIsland, iDDimension, point, permeability, sprite, orientation, iDMonster)
{
	this->sprite = { 0,0, 80, 80 };
	this->xSize = 300;
	this->ySize = 300;


	size_sprite_x = 80;
	size_sprite_y = 80;

	this->sizeX = 1;
	this->sizeY = 2;

	VX =0;
	attack_b =	false;

	started = false;

	SDL_Init(SDL_INIT_AUDIO);
	initAudio();
	// load WAV file

	this->soundsBoss2 = createAudio("ressources/sounds/ghost.wav", 0, SDL_MIX_MAXVOLUME / 2);
}


Boss2::~Boss2()
{
}


void Boss2::anim_sprite()
{
	if (attack_b)
	{
		if (this->orient)
		{
			anim2 = (anim2 + 1) % 5;
			if (anim2 == 0) anim = (anim + 1) % 16;
			if (anim2 == 0 && anim == 9) this->attack();
			if (anim2 == 4 && anim == 14) this->attack_b = false;
			this->sprite = { size_sprite_x * anim, size_sprite_y * 1, size_sprite_x, size_sprite_y };
		}
		else
		{
			anim2 = (anim2 + 1) % 5;
			if (anim2 == 0) anim = (anim + 1) % 16;
			if (anim2 == 0 && anim == 9) this->attack();
			if (anim2 == 4 && anim == 14) this->attack_b = false;
			this->sprite = { size_sprite_x * anim, size_sprite_y * 0, size_sprite_x, size_sprite_y };
		}
	}
	else if (VY > 0 && VX >= 0)
	{
		this->sprite = { size_sprite_x * 4, size_sprite_y * 3, size_sprite_x, size_sprite_y };
		this->orient = true;
	}
	else if (VY < 0 && VX >= 0)
	{
		this->sprite = { size_sprite_x * 4, size_sprite_y * 3, size_sprite_x, size_sprite_y };
		this->orient = true;
	}
	else if (VY > 0 && VX < 0)
	{
		this->sprite = { size_sprite_x * 4, size_sprite_y * 2, size_sprite_x, size_sprite_y };
		this->orient = false;
	}
	else if (VY < 0 && VX < 0)
	{
		this->sprite = { size_sprite_x * 4, size_sprite_y * 2, size_sprite_x, size_sprite_y };
		this->orient = false;
	}
	else if (VX > 0)
	{
		this->sprite = { size_sprite_x * 4, size_sprite_y * 3, size_sprite_x, size_sprite_y };
		this->orient = true;
	}
	else if (VX < 0)
	{
		this->sprite = { size_sprite_x * 4, size_sprite_y * 2, size_sprite_x, size_sprite_y };
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

void Boss2::work()
{
	if (startAI)
	{
		VX = -5;
	}

	long x = this->world->getMainHero()->getX() - this->getX();
	long y = this->world->getMainHero()->getY() - this->getY();


	if (x > 1400 || x < -1400 || y > 1400 || y < -1400)
	{
		if (startAI)
		{
			this->world->getIsland()->getDimension(0)->deleteMonster(this->getIDMonster());
		}
	}
	else if (x < 1400 || x > -1400 || y < 1400 || y > -1400)
	{
		startAI = true;
		if (!started)
		{
			playSoundFromMemory(this->soundsBoss2, SDL_MIX_MAXVOLUME);
			started = true;
		}
	}
}

void Boss2::attack()
{
}

