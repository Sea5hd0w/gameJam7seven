#include "Mobile.h"

#include "World.h"
#include "Dimension.h"

#include "LibraryCommunication.h"

Mobile::Mobile(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation)
	: Element(world, iDIsland, iDDimension, point, permeability, sprite, orientation, 1)
{
	this->speed_run = 200;
	this->split = 10;
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

void Mobile::moveDirection(bool run, int distance, int direction)
{
	int vitesseRun = 10;
	int vitesseJump = 32*2;
	switch (direction)
	{
	case 0:
		//this->moveTop(run, distance);
		VY -= vitesseJump;
		break;
	case 1:
		//this->moveTopRight(run, distance);
		VY -= vitesseJump;
		VX += vitesseRun;
		break;
	case 2:
		//this->moveRight(run, distance);
		VX += vitesseRun;
		break;
	case 3:
		//this->moveDownRight(run, distance);
		//VY += vitesseJump;
		VX += vitesseRun;
		break;
	case 4:
		//this->moveDown(run, distance);
		//VY -= vitesseJump;
		break;
	case 5:
		VX -= vitesseRun;
		//this->moveDownLeft(run, distance);
		break;
	case 6:
		VX -= vitesseRun;
		//this->moveLeft(run, distance);
		break;
	case 7:
		VX -= vitesseRun;
		VY -= vitesseJump;
		//this->moveTopLeft(run, distance);
		break;
	default:
		break;
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

bool Mobile::move(bool run, int x_move, int y_move, int z_move, int direction)
{
	if (this->isMovePossible(this->getIDDimension(), make_tuple(this->getX() + x_move, this->getY() + y_move, this->getZ() + z_move), 0))
	{
		moveUnsafe(run, x_move, y_move, z_move, true, true, direction, 0);
		return true;
	}
	else
	{
	}
}

void Mobile::moveUnsafe(bool run, int x_move, int y_move, int z_move, bool walkOn, bool walkOff, int direction, int iDMove)
{
	tuple<long, long, long> point_start = this->getPoint();
	int wait_time = this->speed_run / split;
	if (!run) wait_time = wait_time / 2;

	for (int i = 0; i < split; i++)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(wait_time));

		get<0>(this->point) = get<0>(this->point) + (x_move / split);
		get<1>(this->point) = get<1>(this->point) + (y_move / split);
		get<2>(this->point) = get<2>(this->point) + (z_move / split);

		//this->sprite = { i*128,((direction+1 + (iDMove * (7-((direction-1)/2))))  * 128), 128,128 };

		if (i == split / 2)
		{
			if(walkOff) this->getWorld()->getIsland()->getDimension(this->getIDDimension())->getElement(point_start)->walkOff(this);
		}
	}

	if (walkOn)this->getWorld()->getIsland()->getDimension(this->getIDDimension())->getElement(this->point)->walkOn(this);

	this->sprite = { 0, 0, 128,128 };

	this->getWorld()->getIsland()->getDimension(this->getIDDimension())->sortElementsToView();
}

void Mobile::move()
{
	set_gravity_vecteurAcceleration();
	calc_vecteurVitesse();
	calc_position();
}

void Mobile::set_gravity_vecteurAcceleration()
{
	clock_t time = clock();
	double accelerationGravitationnel = 9.0 * (clock() - this->t) / 1000.0;

	AY = accelerationGravitationnel;
}

void Mobile::calc_vecteurVitesse()
{
	int vitMax = 32;
	VX += AX;
	VY += AY;
	VX = VX > 32 ? 32 : VX;
	VY = VY > 32 ? 32 : VY;

	if (POSY >= 600)
	{
		VY = 0;
	}
}

void Mobile::calc_position()
{
	POSX += VX;
	POSY += VY;
}