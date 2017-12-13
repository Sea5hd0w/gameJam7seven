#pragma once


#include "Hero.h"
#include "Island.h"


class World
{
public:
	World();
	~World();

	Island* getIsland(); //Getter
	void setIsland(Island* island); //Setter

	Hero* getMainHero(); //Getter
	void setMainHero(Hero* hero); //Setter

	bool isLoading(); //Access to bool loading
	void setLoading(bool loading); //Set bool loading

private:
	Hero* mainHero; //Main Hero of the game : The character controled by the User
	Island* island; //Island of the MainHero

	bool loading; //Boollean indicating if the Dimension and the areas of the MainHero is load


};

