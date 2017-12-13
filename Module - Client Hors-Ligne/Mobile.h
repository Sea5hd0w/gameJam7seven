#pragma once
#include <chrono>
#include <thread>

#include "Element.h"
#include "MotionLess.h"

class World;
class Dimension;
class Area;
class AStar;

class Mobile : public Element {

public:
	Mobile(World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation);
	~Mobile();

	bool isMovePossible(long iDDimension_parameter, tuple<long, long, long> element, int orientation);
	bool isMoveOutOfDimension(long iDDimension_parameter, tuple<long, long, long> element, int orientation);

	void moveAStar(long xDestination, long yDestination);

	void moveDirection(bool run, int distance, int direction);

	void moveTop(bool run, int distance);
	void moveTopRight(bool run, int distance);
	void moveTopLeft(bool run, int distance);
	void moveRight(bool run, int distance);
	void moveLeft(bool run, int distance);
	void moveDownRight(bool run, int distance);
	void moveDownLeft(bool run, int distance);
	void moveDown(bool run, int distance);

	void teleportHere(long iDDimension, tuple<long, long, long> point_finish);

protected:
	virtual bool middleMove(tuple<long, long, long> point_start, tuple<long, long, long> point_finish);

private:
	AStar* path;

	int speed_run;
	int split;
	bool run;

	bool move(bool run, int x_move, int y_move, int z_move, int direction);
	void moveUnsafe(bool run, int x_move, int y_move, int z_move, bool walkOn, bool walkOff, int direction, int iDMove);
	
	bool moveSlope(bool run, int x_move, int y_move, int z_move, int direction);
	bool moveLadder(bool run, int x_move, int y_move, int z_move, int direction);
};

