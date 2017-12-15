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

	VX = 0;
	attack_b = false;

	started = false;

	SDL_Init(SDL_INIT_AUDIO);
	initAudio();
	// load WAV file

	this->soundsBoss2 = createAudio("ressources/sounds/ghost.wav", 0, SDL_MIX_MAXVOLUME / 2);
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
	if (startAI)
	{
		this->ai();
	}
	long x = this->world->getMainHero()->getX() - this->getX();
	long y = this->world->getMainHero()->getY() - this->getY();


	if (x > 1400 || x < -1400 || y > 1400 || y < -1400)
	{
		this->world->getIsland()->getDimension(0)->deleteMonster(this->getIDMonster());
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

void Nazi::ai()
{
	ai1 = (ai1 + 1) % 70;
	if (ai1 == 0) ai2 = (ai2 + 1) % 2;

	if (ai2 == 0) VX = -2;
	else VX = 2;
}



string Nazi::toString()
{
	return "nazi";
}