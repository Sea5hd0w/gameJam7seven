#include "Boss2.h"

#include "World.h"
#include "LibraryCommunication.h"
#include "Dimension.h"
#include "Ammo.h"

Boss2::Boss2(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDMonster)
	: Monster(world, iDIsland, iDDimension, point, permeability, sprite, orientation, iDMonster)
{
	ai1 = 0;
	ai2 = 0;

	this->sprite = { 0,0, 80, 80 };
	this->xSize = 300;
	this->ySize = 300;


	size_sprite_x = 80;
	size_sprite_y = 80;

	this->sizeX = make_tuple(2,3);
	this->sizeY = make_tuple(-2, 0);

	VX =0;
	attack_b =	true;

	started = false;

	SDL_Init(SDL_INIT_AUDIO);
	initAudio();
	// load WAV file

	this->soundsBoss2 = createAudio("ressources/sounds/ghost.wav", 0, SDL_MIX_MAXVOLUME / 2);
	this->affectedByGravity = false;
	this->life =15;
	t = clock();
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
		this->ai();
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

	//this->shoot();
}

void Boss2::attack()
{
	this->shoot();
}

string Boss2::toString()
{
	return "boss2";
}

void Boss2::shoot()
{
	if (clock() - t > 100)
	{
		this->Arme->shoot(make_tuple(POSX, POSY - 64, 0), -10);
		t = clock();
	}
}
void Boss2::ai()
{
	ai1 = (ai1 + 1) % 200;
	if (ai1 == 0) ai2 = (ai2 + 1) % 2;

	if (ai2 == 0) VX = -3;
	else VX = 3;

	if ((ai1 > 0 && ai1 < 25) || (ai1 > 50 && ai1 < 75) || (ai1 > 100 && ai1 < 125) || (ai1 > 150 && ai1 < 175)) VY = -2;
	else VY = 2;

	if (ai1 % 70 == 0) attack_b = true;
}



