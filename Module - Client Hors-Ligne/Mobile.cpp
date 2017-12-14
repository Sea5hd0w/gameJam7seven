#include "Mobile.h"

#include "World.h"
#include "Dimension.h"

#include "LibraryCommunication.h"
#include "variable_static.h"

Mobile::Mobile(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation)
	: Element(world, iDIsland, iDDimension, point, permeability, sprite, orientation, 1)
{
	this->speed_run = 200;
	this->split = 10;
	this->anim = 0;
	this->anim2 = 0;

	size_sprite_x = 16;
	size_sprite_y = 28;

	this->sizeX = 1;
	this->sizeY = 1;
	orient = true;
}


Mobile::~Mobile()
{
}

bool Mobile::isMovePossible(long iDDimension_parameter, tuple<long, long, long> element, int orientation)
{
	if (this->getWorld()->getIsland()->getDimension(iDDimension_parameter)->isElement(element))
	{
		return this->getWorld()->getIsland()->getDimension(iDDimension_parameter)->getElement(element)->getPermeability();
	}
	else
	{
		return false;
	}
}

void Mobile::teleportHere(long iDDimension, tuple<long, long, long> point_finish)
{
	if (this->getIDDimension() != iDDimension)
	{
		this->getWorld()->getIsland()->getDimension(iDDimension)->addHero(this->getWorld()->getIsland()->getDimension(this->getIDDimension())->getHero(0), 0);
		this->getWorld()->getIsland()->getDimension(this->getIDDimension())->deleteHero(0);
	}
	this->setPoint(point_finish);
	this->setIDDimension(iDDimension);

	this->getWorld()->getIsland()->getDimension(this->getIDDimension())->loadElementsToView();
}

void Mobile::move()
{
	debug(to_string(POSX) + " || " + to_string(POSY));
	anim_sprite();
	work();

	if(this->affectedByGravity) set_gravity_vecteurAcceleration();
	calc_vecteurVitesse();
	this->isMovePossible();
	calc_position();
}

bool Mobile::getOrient()
{
	return orient;
}

void Mobile::anim_sprite()
{
	if (VY > 0 && VX >= 0)
	{
		this->sprite = { size_sprite_x * 2, size_sprite_y, size_sprite_x, size_sprite_y };
		this->orient = true;
	}
	else if (VY < 0 && VX >= 0)
	{
		this->sprite = { size_sprite_x, size_sprite_y, size_sprite_x, size_sprite_y };
		this->orient = true;
	}
	else if (VY > 0 && VX < 0)
	{
		this->sprite = { size_sprite_x * 2, size_sprite_y * 4, size_sprite_x, size_sprite_y };
		this->orient = false;
	}
	else if (VY < 0 && VX < 0)
	{
		this->sprite = { size_sprite_x, size_sprite_y * 4, size_sprite_x, size_sprite_y };
		this->orient = false;
	}
	else if (VX > 0)
	{
		anim2 = (anim2 + 1) % 5;
		if (anim2 == 0) anim = (anim + 1) % 9;
		this->sprite = { size_sprite_x * anim, size_sprite_y * 2, size_sprite_x, size_sprite_y };
		this->orient = true;
	}
	else if (VX < 0)
	{
		anim2 = (anim2 + 1) % 5;
		if (anim2 == 0) anim = (anim + 1) % 9;
		this->sprite = { size_sprite_x * anim, size_sprite_y * 5, size_sprite_x, size_sprite_y };
		this->orient = false;
	}
	else
	{
		if (this->orient)
		{
			anim2 = (anim2 + 1) % 5;
			if (anim2 == 0) anim = (anim + 1) % 9;
			this->sprite = { size_sprite_x * anim, size_sprite_y * 0, size_sprite_x, size_sprite_y };
		}
		else
		{
			anim2 = (anim2 + 1) % 5;
			if (anim2 == 0) anim = (anim + 1) % 9;
			this->sprite = { size_sprite_x * anim, size_sprite_y * 3, size_sprite_x, size_sprite_y };
		}
	}
}

void Mobile::work()
{

}

void Mobile::set_gravity_vecteurAcceleration()
{
	clock_t time = clock();
	double accelerationGravitationnel = 9.81 * (clock() - this->t) / 1000.0;
	this->t = clock();

	AY = accelerationGravitationnel;
}

void Mobile::calc_vecteurVitesse()
{
	int vitMax = 32;
	VX += AX;
	VY += AY;
	VX = VX > 32 ? 32 : VX;
	VY = VY > 32 ? 32 : VY;
}

void Mobile::calc_position()
{
	POSX += VX;
	POSY += VY;

	//debug("x : " + to_string(POSX) + " || y : " + to_string(POSY));
}

void Mobile::moveTop(bool run, int distance)
{
	VY = (VY==0) ? -vitesseJump : VY;
}
void Mobile::moveTopRight(bool run, int distance)
{
	VX = vitesse;
	VY = (VY == 0) ? -vitesseJump : VY;
}
void Mobile::moveTopLeft(bool run, int distance)
{
	VX = -vitesse;
	VY = (VY == 0) ? -vitesseJump : VY;
}
void Mobile::moveRight(bool run, int distance)
{
	VX = vitesse;
}
void Mobile::moveLeft(bool run, int distance)
{
	VX = -vitesse;
}
void Mobile::moveDownRight(bool run, int distance)
{
	VX = vitesse;
	VY += vitesse;
}
void Mobile::moveDownLeft(bool run, int distance)
{
	VX = -vitesse;
	VY += vitesse;
}
void Mobile::moveDown(bool run, int distance)
{
	VY += vitesse;
}

bool Mobile::isMovePossible()
{
	long x, y;
	//position de toute les case du mobile
	list<tuple<long, long>> casePos;
	for (int i = 0; i < sizeY; i++)
	{
		for(int j = 0; j < sizeX; j++)
		{
			casePos.push_back(make_tuple(POSX / variable::SIZE_CASE_X + j, POSY / variable::SIZE_CASE_Y - i));
		}
	}
	
	Dimension* dim = this->getWorld()->getIsland()->getDimension(0);

	//sauter
	if (VY < 0)
	{
		for (tuple<long, long> pos : casePos)
		{
			x = get<0>(pos);
			y = get<1>(pos);
			//debug(to_string(y) + " || " + to_string(x) + " || " + to_string(POSY / variable::SIZE_CASE_Y) + " || " + to_string(POSX / variable::SIZE_CASE_X));
			for (tuple<long, long> other : casePos)
			{
				if (other != make_tuple(x, y - 1))
				{
					tuple<long, long> IDArea = dim->getIDArea(x, y);
					Area* area = dim->getArea(get<0>(IDArea), get<1>(IDArea));
					if (area->isElement(make_tuple(x*variable::SIZE_CASE_X, (y-1)*variable::SIZE_CASE_Y, 0)))
					{
						VY = 0;
						POSY = (y+1)*variable::SIZE_CASE_Y;
					}
				}
			}
		}
	}

	//tomber
	if (VY > 0)
	{
		for (tuple<long, long> pos : casePos)
		{
			x = get<0>(pos);
			y = get<1>(pos);
			//debug(to_string(y) + " || " + to_string(x) + " || " + to_string(POSY / variable::SIZE_CASE_Y) + " || " + to_string(POSX / variable::SIZE_CASE_X));
			for (tuple<long, long> other : casePos)
			{
				if (other != make_tuple(x, y + 1)) 
				{
					tuple<long, long> IDArea = dim->getIDArea(x, y);
					Area* area = dim->getArea(get<0>(IDArea), get<1>(IDArea));
					//debug(to_string(y) + " || " + to_string(x) + " || " + to_string(POSY / variable::SIZE_CASE_Y) + " || " + to_string(POSX / variable::SIZE_CASE_X));
					if (area->isElement(make_tuple((x+1)*variable::SIZE_CASE_X, (y+1)*variable::SIZE_CASE_Y, 0)) || area->isElement(make_tuple((x)*variable::SIZE_CASE_X, (y + 1)*variable::SIZE_CASE_Y, 0)))
					{
						VY = 0;
					}
				}
			}			
		}
	}

	//droite
	if (VX > 0)
	{
		for (tuple<long, long> pos : casePos)
		{
			x = get<0>(pos);
			y = get<1>(pos);
			//debug(to_string(y) + " || " + to_string(x) + " || " + to_string(POSY / variable::SIZE_CASE_Y) + " || " + to_string(POSX / variable::SIZE_CASE_X));
			for (tuple<long, long> other : casePos)
			{
				if (other != make_tuple(x + 1, y))
				{
					tuple<long, long> IDArea = dim->getIDArea(x, y);
					Area* area = dim->getArea(get<0>(IDArea), get<1>(IDArea));
					if (area->isElement(make_tuple((x+1)*variable::SIZE_CASE_X, y*variable::SIZE_CASE_Y, 0)))
					{
						VX = 0;
						POSX = (x)*variable::SIZE_CASE_X;
					}
				}
			}
		}
	}

	//gauche
	if (VX < 0)
	{
		for (tuple<long, long> pos : casePos)
		{
			x = get<0>(pos);
			y = get<1>(pos);
			//debug(to_string(y) + " || " + to_string(x) + " || " + to_string(POSY / variable::SIZE_CASE_Y) + " || " + to_string(POSX / variable::SIZE_CASE_X));
			for (tuple<long, long> other : casePos)
			{
				if (other != make_tuple(x, y))
				{
					tuple<long, long> IDArea = dim->getIDArea(x, y);
					Area* area = dim->getArea(get<0>(IDArea), get<1>(IDArea));
					if (area->isElement(make_tuple((x)*variable::SIZE_CASE_X, y*variable::SIZE_CASE_Y, 0)))
					{
						VX = 0;
						POSX = (x+1)*variable::SIZE_CASE_X;
					}
				}
			}
		}
	}
	
	return true;
}