#include "HittBox.h"
#include <math.h>
#include "Element.h"
#include "Dimension.h"
#include "LibraryCommunication.h"

Hitbox::Hitbox(Mobile* mob, long dephaseX, long dephaseY, Dimension* d, long* mobX, long* mobY)
{
	this->mob = mob;
	this->dephaseX = dephaseX;
	this->dephaseY = dephaseY;
	this->mobX = mobX;
	this->mobY = mobY;
	dim = d;
	
	this->dim->addHitbox(this);
	this->updatePos();
	//gen("hit : " + to_string(this->posX) + " || " + to_string(this->posY));
	
}

bool Hitbox::detect_collision()
{
	for (Hitbox* hit : dim->getHitboxs())
	{
		if (this->mob != hit->mob)
		{
			long a = hit->getPosX();
			long b = hit->getPosY();

			long c = posX;
			long d = posY;
			if (abs(this->posX - hit->getPosX()) < variable::SIZE_CASE_X)
			{
				if (abs(this->posY - hit->getPosY()) < variable::SIZE_CASE_Y)
				{
					hit->mob->underAttack(this->mob);
					return true;
				}
			}
		}
	}
	return false;
}

long Hitbox::getPosX()
{
	return this->posX;
}

long Hitbox::getPosY()
{
	return this->posY;
}

void Hitbox::updatePos()
{
	this->posX = *mobX + this->dephaseX;
	this->posY = *mobY +this->dephaseY;
	//gen("hit : " + to_string(this->posX) + " || " + to_string(this->posY));
}