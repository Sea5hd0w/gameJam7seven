#include "AStar.h"

#include "LibraryCommunication.h"

AStar::AStar(World* world, Mobile* mobile)
	: world(world), mobile(mobile)
{
}

AStar::~AStar()
{
}


void AStar::calculateShortWay(long xDestination, long yDestination)
{
	this->openList.clear();
	this->closedList.clear();
	this->path.clear();

	int x = this->mobile->getX() - this->mobile->getX() % 100;
	int y = this->mobile->getY() - this->mobile->getY() % 100;
	
	this->start = make_pair(x, y);
	this->destination = make_pair(xDestination, yDestination);

	node start_n{ make_pair(0,0),0,0,0 };

	pair<long, long> actual = this->start;

	this->openList.insert(make_pair(actual, start_n));
	this->addClosedList(actual);
	this->addAdjacentNode(actual);
	
	while (!(actual == this->destination) && !this->openList.empty())
	{		
		actual = this->getBestNode(this->openList);

		this->addClosedList(actual);
		this->addAdjacentNode(actual);
	}

	if (actual == this->destination) 
	{
		this->calculate_path();
	}
	else {
		err("A*");
	}
}

long AStar::heuristic(long x1, long y1, long x2, long y2)
{
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

bool AStar::nodeExist(pair<long, long> n, map< pair<long, long>, node> &p_map)
{
	if (p_map.find(n) != p_map.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void AStar::addAdjacentNode(pair<long, long>& n)
{
	for (int i = -1; i <= 1; i++)
	{
		for (int j =  -1; j <= 1; j++)
		{
			if ((i*100 + n.first != n.first) || (j * 100 + n.second != n.second))
			{
				if (this->world->getIsland()->getDimension(this->world->getMainHero()->getIDDimension())->getElement(make_tuple(n.first + i * 100, n.second + j * 100 ,0)) != NULL)
				{
					if (this->world->getIsland()->getDimension(this->world->getMainHero()->getIDDimension())->getElement(make_tuple(n.first + i * 100, n.second + j * 100, 0))->getPermeability())
					{
						this->addNode(make_pair(n.first + i * 100, n.second + j * 100), n);
					}
				}
			}
		}
	}
}

void AStar::addNode(pair<long, long> it, pair <long, long> n)
{
	long cout_g = 0, cout_h = 0, cout_f = 0;

	if (!nodeExist(it, this->closedList))
	{
		cout_g =  this->closedList.find(n)->second.cout_g + this->heuristic(it.first, it.second, n.first, n.second); 
		cout_h = this->heuristic(it.first, it.second, this->destination.first, this->destination.second);
		cout_f = cout_g + cout_h;

		if (nodeExist(it, this->openList))
		{
			if (cout_f < this->openList.find(it)->second.cout_f)
			{
				this->openList[it] = node{ n, cout_g, cout_h, cout_f };

			}
		}
		else
		{
			this->openList.insert(make_pair(it, node{ n, cout_g, cout_h, cout_f }));
		}
	}
}

pair<long, long> AStar::getBestNode(map<pair<long, long>, node>& p_map)
{
	long cout_f = p_map.begin()->second.cout_f;
	pair<long, long> point = p_map.begin()->first;

	for (map<pair<long, long>, node>::const_iterator i = p_map.begin(); i != p_map.end(); i++)
	{
		if (i->second.cout_f < cout_f) {
			cout_f = i->second.cout_f;
			point = i->first;
		}
	}
	return point;
}

void AStar::addClosedList(pair<long, long>& p_n)
{
	node& n = this->openList.find(p_n)->second;
	this->closedList.insert(make_pair(p_n, n));

	if (this->openList.erase(p_n) == 0) err("Node doens't exist : impossible to remove");
}

void AStar::calculate_path()
{
	node temp = this->closedList.find(this->destination)->second;

	pair<long, long> actual = this->destination;
	pair<long, long> prec = temp.parent;

	while (prec != this->start)
	{
		this->path.push_front(this->getDirection(actual, prec));
		actual = prec;
		prec = this->closedList.find(prec)->second.parent;
	}

	this->path.push_front(this->getDirection(actual, this->start));

	///////////////////!\\\\\\\\\\\\\\\\\\\
	//	A revoir pour couper la boucle	 \\
	//////////////////!\\\\\\\\\\\\\\\\\\\\
	
	this->move();
}

int AStar::getDirection(pair<long, long> p1, pair<long, long> p2)
{
	long n1 = p1.first - p2.first;
	long n2 = p1.second - p2.second;

	if (n1 == -100 && n2 == -100)
	{
		return 0;
	}
	else if (n1 == 0 && n2 == -100)
	{
		return 1;
	}
	else if (n1 == 100 && n2 == -100)
	{
		return 2;
	}
	else if (n1 == 100 && n2 == 0)
	{
		return 3;
	}
	else if (n1 == 100 && n2 == 100)
	{
		return 4;
	}
	else if (n1 == 0 && n2 == 100)
	{
		return 5;
	}
	else if (n1 == -100 && n2 == 100)
	{
		return 6;
	}
	else if (n1 == -100 && n2 == 0)
	{
		return 7;
	}
}

int AStar::invertDirection(int direction)
{
	return ((direction + 4) % 8);
}

void AStar::move()
{
	bool run = false;
	if (this->path.size() < 5) run = true;

	list<int> pathCopy =  this->path;


	while (!pathCopy.empty())
	{
		this->mobile->moveDirection(run, 1, pathCopy.front());
		pathCopy.pop_front();
	}
	/*
	for (int j : this->path)
	{
		if (this->i != i) break;
		this->mobile->moveDirection(run, 1, j);
	}
	*/
}