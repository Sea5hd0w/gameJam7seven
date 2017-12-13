#include "World.h"

#include "LibraryCommunication.h"


World::World()
{
	this->island = NULL;
	this->mainHero = NULL;
	loading = true;

	gen("World created");
}


World::~World()
{
}

Island * World::getIsland()
{
	return this->island;
}

void World::setIsland(Island * island)
{
	if (this->island != NULL)
	{
		delete this->island;
	}
	this->island = island;
}

Hero * World::getMainHero()
{
	return this->mainHero;
}

void World::setMainHero(Hero* hero)
{
	this->mainHero = hero;
}

bool World::isLoading()
{
	return this->loading;
}

void World::setLoading(bool loading)
{
	this->loading = loading;
}
