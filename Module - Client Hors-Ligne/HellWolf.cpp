#include "HellWolf.h"

#include "World.h"
#include "LibraryCommunication.h"
#include "Dimension.h"
#include "balle.h"
HellWolf::HellWolf(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDMonster)
	: Monster(world, iDIsland, iDDimension, point, permeability, sprite, orientation, iDMonster)
{
	this->sprite = { 0,0, 48, 48 };
	this->xSize = 64;
	this->ySize = 112;

	size_sprite_x = 48;
	size_sprite_y = 48;
	VX = 0;
	this->produceHitBox(world->getIsland()->getDimension(this->world->getMainHero()->getIDDimension()));
	started = false;

	SDL_Init(SDL_INIT_AUDIO);
	initAudio();
	// load WAV file

	this->soundsHellWolf = createAudio("ressources/sounds/hellwolf.wav", 0, SDL_MIX_MAXVOLUME / 2);
	

	this->life = 1;
}


HellWolf::~HellWolf()
{
}

void HellWolf::anim_sprite()
{
	if (VY > 0 && VX >= 0)
	{
		this->sprite = { size_sprite_x * 2, size_sprite_y * 2, size_sprite_x, size_sprite_y };
		this->orient = true;
	}
	else if (VY < 0 && VX >= 0)
	{
		this->sprite = { size_sprite_x, size_sprite_y * 2, size_sprite_x, size_sprite_y };
		this->orient = true;
	}
	else if (VY > 0 && VX < 0)
	{
		this->sprite = { size_sprite_x * 2, size_sprite_y * 0, size_sprite_x, size_sprite_y };
		this->orient = false;
	}
	else if (VY < 0 && VX < 0)
	{
		this->sprite = { size_sprite_x, size_sprite_y * 0, size_sprite_x, size_sprite_y };
		this->orient = false;
	}
	else if (VX > 0)
	{
		anim2 = (anim2 + 1) % 5;
		if (anim2 == 0) anim = (anim + 1) % 4;
		this->sprite = { size_sprite_x * anim, size_sprite_y * 3, size_sprite_x, size_sprite_y };
		this->orient = true;
	}
	else if (VX < 0)
	{
		anim2 = (anim2 + 1) % 5;
		if (anim2 == 0) anim = (anim + 1) % 4;
		this->sprite = { size_sprite_x * anim, size_sprite_y * 1, size_sprite_x, size_sprite_y };
		this->orient = false;
	}
	else
	{
		this->sprite = { 0, 0, size_sprite_x, size_sprite_y };
	}
}

void HellWolf::work()
{
	if (startAI)
	{
		VX = -0;
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
	else if(x < 1400 || x > -1400 || y < 1400 || y > -1400)
	{
		startAI = true;
		if (!started)
		{
			playSoundFromMemory(this->soundsHellWolf, SDL_MIX_MAXVOLUME);
			started = true;
		}
	}
}

string HellWolf::toString()
{
	return "hellFire";
}