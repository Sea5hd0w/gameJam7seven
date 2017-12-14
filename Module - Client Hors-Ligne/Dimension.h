#pragma once

#include <iostream>
#include <typeinfo>
#include <list>
#include <tuple>
#include <map>
#include <string>
#include <vector>

#include "Hero.h"
#include "Monster.h"

using namespace std;

class World;
#include "Area.h"

class Dimension
{
public:
	Dimension(World* world, long iDIsland, long iDDimension);
	~Dimension();

	void addElementsToView(Element* element);
	void loadElementsToView(); //Load all the element of map (MotionLess & Mobiles) in list for the view
	void sortElementsToView(); //Sort element for the view : by position & type (Mobile, MotionLess)
	list<pair<tuple<long*, long, long*, long*>, Element*>> getElementsToView(); // Getter

	bool isArea(long x, long y); //Test if Area exist by ID
	void addArea(long x, long y, Area* area); //Add Area by ID
	void deleteArea(long x, long y); //Delete Area by ID
	Area* getArea(long x, long y); //Get Area by ID
	map<tuple<long, long>, Area*> &getAreas(); //Get Area's list

	MotionLess* getElement(tuple<long, long, long> point); // Get Element in dimension
	bool isElement(tuple<long, long, long> point); // Test if element exist in Dimension

	void addHero(Hero* hero, long iDHero); // Add Hero in Dimension
	void deleteHero(long iDHero); // Delete Hero in Dimension
	Hero* getHero(long iDHero); // Get Hero by ID
	map<long, Hero*> &getHeroes(); // Get Hero's list

	
	void addMonster(Monster* monster, long iDMonster); // Add Monster in Dimension
	void deleteMonster(long iDMonster); // Delete Monster in Dimension
	Monster* getMonster(long iDMonster); // Get Monster by ID
	map<long, Monster*> &getMonsters(); // Get Monster's list


	/*
	void addNPC(NPC* npc, long iDNPC); // Add NPC in Dimension
	void deleteNPC(long iDNPC); // Delete NPC in Dimension
	NPC* getNPC(long iDNPC); // Get NPC by ID
	map<long, NPC*> &getNPCs(); // Get NPC's list
	*/

	SDL_Texture* getBackground();
	void addBackground(string background);
	tuple<long, long> getIDArea(long x, long y); // Calculate ID area by coordinate of an Element
private:
	World* world; //Pointer to access to world
	long iDIsland; //ID of the island
	long iDDimension; //ID of the Dimension

	long areaSize = 25; // Number of element per side

	map<long, Hero*> heroes; // Hero's List of the Dimension
	map<long, Monster*> monsters; // Monster's List of the Dimension
	//map<long, NPC*> npcs; // NPC's List of the Dimension


	map<tuple<long, long>, Area*> area; // Area's of the Dimension

	

	list<pair<tuple<long*, long, long*, long*>, Element*>> elementsToView; // List of all element to view (MotionLess, Mobiles)

	SDL_Texture* background;
};

