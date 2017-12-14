#include "Balle.h"



Balle::Balle(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDHero, )
	: Mobile(world, iDIsland, iDDimension, point, permeability, sprite, orientation)
{
	
}




Balle::~Balle()
{
}

void Balle::inTravel()
{

}
