#pragma once
#include <chrono>
#include <thread>

#include "Element.h"
#include "MotionLess.h"

#define VX get<0>(vecteurVitesse)
#define VY get<1>(vecteurVitesse)
#define AX get<0>(vecteurAcceleration)
#define AY get<1>(vecteurAcceleration)

class World;
class Dimension;
class Area;
class AStar;

class Mobile : public Element {

public:
	Mobile(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation);
	~Mobile();

	bool isMovePossible(long iDDimension_parameter, tuple<long, long, long> element, int orientation);

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

	void move() override;

protected:
	tuple<double, double> vecteurVitesse;
	tuple<double, double> vecteurAcceleration;

	void anim_sprite();

	int size_sprite_x;
	int size_sprite_y;

private:
	AStar* path;
	clock_t t = 0;

	int speed_run;
	int split;
	bool run;

	bool move(bool run, int x_move, int y_move, int z_move, int direction);
	void moveUnsafe(bool run, int x_move, int y_move, int z_move, bool walkOn, bool walkOff, int direction, int iDMove);

	

	void set_gravity_vecteurAcceleration();
	void calc_vecteurVitesse();
	void calc_position();

	int vitesse = 3;
	int vitesseJump = 10;
	
	long anim;
	int anim2;
};

