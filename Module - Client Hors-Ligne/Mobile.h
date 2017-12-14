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


	int size_sprite_x;
	int size_sprite_y;

	int vitesse;
	int vitesseJump;
	int sizeX; //en unité de block
	int sizeY; //en unité de block

	virtual bool isMovePossible();

private:
	AStar* path;
	clock_t t = 0;

	int speed_run;
	int split;
	bool run;
	
	void set_gravity_vecteurAcceleration();
	void calc_vecteurVitesse();
	void calc_position();
	
	long anim;
	int anim2;
};

