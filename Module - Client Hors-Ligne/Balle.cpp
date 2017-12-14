#include "Balle.h"
#include "LibraryCommunication.h"
#include <string>
Balle::Balle(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDHero, int vitesse, int degat)
	: Mobile(world, iDIsland, iDDimension, point, permeability, sprite, orientation)
{
	VX = vitesse;
	this->moveRight(true, 50);
	this->world = world;
	while (true) {
		debug("Coordonnées de la balle : " + to_string(get<0>(point)) + " | " + to_string(get<1>(point)) + " | " + to_string(get<2>(point)));
	}
}




Balle::~Balle()
{
}

tuple<long, long, long> Balle::getPoint()
{
	return point;
}

