#pragma once

#include <map>
#include <tuple>
#include <chrono>
#include <thread>
#include <time.h>
#include <iostream>
#include <List>
#include <math.h>

#include "World.h"
#include "Island.h"
#include "Dimension.h"
#include "MotionLess.h"

#include <thread>

using namespace std;

class AStar
{
public:
	AStar(World* world, Mobile* mobile);
	~AStar();

	void calculateShortWay(long xDestination, long yDestination); //Main function : loop throught the step of A* and lunch the movement

private:
	World* world;
	Mobile* mobile;

	struct node {
		pair<long, long> parent;
		long cout_g, cout_h, cout_f;
	};

	pair<long, long> start;
	pair<long, long> destination;

	map< pair<long, long>, node> openList;
	map< pair<long, long>, node> closedList;

	list<int> path;

	long heuristic(long x1, long y1, long x2, long y2);
	bool nodeExist(pair<long, long> n, map< pair<long, long>, node> &p_map);

	void addAdjacentNode(pair <long, long>& n);
	void addNode(pair <long, long> it, pair <long, long> n);

	pair<long, long> getBestNode(map< pair<long, long>, node> &p_map);

	void addClosedList(pair<long, long>& p_n);

	void calculate_path();
	int getDirection(pair<long, long> p1, pair<long, long> p2);
	int invertDirection(int direction);

	void move();
};

