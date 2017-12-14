#include "Ammo.h"



Ammo::Ammo()
{

}


Ammo::~Ammo()
{
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