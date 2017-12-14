#include "Ammo.h"
#include "View.h"


Ammo::Ammo(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, int priority, int vitesse, int degat)
	: Element(world, iDIsland,  iDDimension,  point,  permeability,  sprite,orientation,priority)
{
	this->degat = degat;
	this->vitesse = vitesse;
}


Ammo::~Ammo()
{

}

void Ammo::shoot(long yHero) {
	
}

void Ammo::printSprite(int xPosition, int yPosition)
{
	int y = yPosition;
	if (this->ySize > 64) y = y - (this->ySize - 64);

	SDL_Rect dest = { xPosition,  y, this->xSize, this->ySize };
	try {
		SDL_RenderCopy(View::renderer, this->p_sprite, &this->sprite, &dest);
	}
	catch (exception)
	{
	}
}