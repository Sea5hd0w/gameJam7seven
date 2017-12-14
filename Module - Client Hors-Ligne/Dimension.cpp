#include "Dimension.h"

#include "LibraryCommunication.h"


Dimension::Dimension(World* world, long iDIsland, long iDDimension)
	: world(world), iDIsland(iDIsland), iDDimension(iDDimension)
{
	this->background = NULL;
	gen("Dimension created");
}


Dimension::~Dimension()
{
	for (map<tuple<long, long>, Area*>::const_iterator area = this->getAreas().begin(); area != this->getAreas().end(); area++)
	{
		for (auto& element : area->second->getElements())
		{
			this->elementsToView.remove(element.second->getElementToView());
		}
	}

	for (map<tuple<long, long>, Area*>::iterator it = this->area.begin(); it != this->area.end(); ++it)
	{
		delete(it->second);
		this->area.erase(it);
	}
}

void Dimension::addElementsToView(Element* element)
{
	this->elementsToView.push_front(element->getElementToView());
	this->sortElementsToView();
}

void Dimension::loadElementsToView()
{
	for (map<tuple<long, long>, Area*>::const_iterator area = this->getAreas().begin(); area != this->getAreas().end(); area++)
	{
		for (const auto& element : area->second->getElements())
		{
			this->elementsToView.push_front(element.second->getElementToView());
		}
	}

	for (map<long, Hero*>::const_iterator elementsList = this->heroes.begin(); elementsList != this->heroes.end(); elementsList++)
	{
		this->elementsToView.push_front(elementsList->second->getElementToView());
	}

	for (map<long, Monster*>::const_iterator elementsList = this->monsters.begin(); elementsList != this->monsters.end(); elementsList++)
	{
		this->elementsToView.push_front(elementsList->second->getElementToView());
	}
	
	this->sortElementsToView();
}

void Dimension::sortElementsToView()
{
	this->elementsToView.sort([](pair<tuple<long*, long, long*, long*>, Element*> & a, pair<tuple<long*, long, long*, long*>, Element*> & b) {
		return *get<2>(a.first) < *get<2>(b.first) || 
			*get<2>(a.first) == *get<2>(b.first) && (*get<3>(a.first) < *get<3>(b.first) || 
			*get<3>(a.first) == *get<3>(b.first) && (*get<0>(a.first) < *get<0>(b.first) || 
			*get<0>(a.first) == *get<0>(b.first) && get<1>(a.first) < get<1>(b.first)
		)); });
}

list<pair<tuple<long*, long, long*, long*>, Element*>> Dimension::getElementsToView()
{
	return this->elementsToView;
}

bool Dimension::isArea(long x, long y)
{
	return this->area.find(getIDArea(x, y)) != this->area.end();
}

void Dimension::addArea(long x, long y, Area * area)
{
	if (!isArea(x, y))
	{
		this->area.insert(std::pair<tuple<long, long>, Area*>(this->getIDArea(x, y), area));
	}
	else
	{
		err("Conflict Area [" + to_string(x) + ":" + to_string(y) + "] already exist in Dimension [" + to_string(iDDimension) + "]");
	}
}

void Dimension::deleteArea(long x, long y)
{
	for (auto& element : this->getArea(x, y)->getElements())
	{
		this->elementsToView.remove(element.second->getElementToView());
	}
	Area* erase = this->area.find(this->getIDArea(x, y))->second;
	this->area.erase(this->getIDArea(x, y));
	delete(erase);
}

Area * Dimension::getArea(long x, long y)
{
	if (isArea(x, y))
	{
		return this->area[this->getIDArea(x, y)];
	}
	else
	{
		err("Dimension : No Area[" + to_string(get<0>(getIDArea(x, y))) + ":" + to_string(get<1>(getIDArea(x, y))) +"] found");
		return NULL;
	}
}

map<tuple<long, long>, Area*> &Dimension::getAreas()
{
	return this->area;
}

MotionLess * Dimension::getElement(tuple<long, long, long> point)
{
	if (this->isArea(get<0>(point), get<1>(point)))
	{
		if (this->getArea(get<0>(point), get<1>(point))->isElement(point))
		{
			return this->getArea(get<0>(point), get<1>(point))->getElement(point);
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		return NULL;
	}
}

bool Dimension::isElement(tuple<long, long, long> point)
{
	if (this->isArea(get<0>(point), get<1>(point)))
	{
		return this->getArea(get<0>(point), get<1>(point))->isElement(point);
	}
	return false;
}

void Dimension::addHero(Hero* hero, long iDHero)
{
	if (this->heroes.find(iDHero) == this->heroes.end())
	{
		this->heroes.insert(std::pair<long, Hero*>(iDHero, hero));
	}
	else
	{
		err("Conflict Hero [" + to_string(iDHero) + "] already exist in Dimension [" + to_string(iDDimension) + "]");
	}
}

void Dimension::deleteHero(long iDHero)
{
	if (this->heroes.find(iDHero) != this->heroes.end())
	{
		//delete this->heroes.find(iDHero)->second;
		this->heroes.erase(iDHero);
	}
}

Hero * Dimension::getHero(long iDHero)
{
	if (this->heroes.find(iDHero) != this->heroes.end())
	{
		return this->heroes.find(iDHero)->second;
	}
	else
	{
		err("Dimension : No Hero[" + to_string(iDHero) + "] found");
		return NULL;
	}
}

map<long, Hero*>& Dimension::getHeroes()
{
	return this->heroes;
}

void Dimension::addMonster(Monster* monster, long iDMonster)
{
	if (this->monsters.find(iDMonster) == this->monsters.end())
	{
		this->monsters.insert(std::pair<long, Monster*>(iDMonster, monster));
	}
	else
	{
		err("Conflict Hero [" + to_string(iDMonster) + "] already exist in Dimension [" + to_string(iDDimension) + "]");
	}
}

void Dimension::deleteMonster(long iDMonster)
{
	if (this->monsters.find(iDMonster) != this->monsters.end())
	{
		//delete this->heroes.find(iDHero)->second;
		this->monsters.erase(iDMonster);
	}
}

Monster * Dimension::getMonster(long iDMonster)
{
	if (this->monsters.find(iDMonster) != this->monsters.end())
	{
		return this->monsters.find(iDMonster)->second;
	}
	else
	{
		err("Dimension : No Monster[" + to_string(iDMonster) + "] found");
		return NULL;
	}
}

map<long, Monster*>& Dimension::getMonsters()
{
	return this->monsters;
}


SDL_Texture* Dimension::getBackground()
{
	return this->background;
}

void Dimension::addBackground(string background)
{
	this->background = Sprites::addSprite(background);
}

tuple<long, long> Dimension::getIDArea(long x, long y)
{
	long x_id = x/100 - (x/100 % this->areaSize);
	long y_id = y/100 - (y/100 % this->areaSize);

	return make_tuple(x_id, y_id);
}
