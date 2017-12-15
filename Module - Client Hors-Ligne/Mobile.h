#pragma once
#include <chrono>
#include <thread>

#include "Element.h"
#include "MotionLess.h"
#include "HittBox.h"

#define VX get<0>(vecteurVitesse)
#define VY get<1>(vecteurVitesse)
#define AX get<0>(vecteurAcceleration)
#define AY get<1>(vecteurAcceleration)

class World;
class Dimension;
class Area;
class AStar;
class Ammo;
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

	bool getOrient();


	long anim;
	int anim2;
	bool orient;

	virtual void underAttack(Mobile* e);
	void produceHitBox(Dimension* dim);

	bool shotHero = true;
	
	int life = 1;
	Ammo* Arme;
	virtual void shoot() = 0;
	virtual string toString() = 0;
protected:
	tuple<double, double> vecteurVitesse;
	tuple<double, double> vecteurAcceleration;

	virtual void anim_sprite();
	virtual void work();
	virtual void attack();

	int size_sprite_x;
	int size_sprite_y;

	int vitesse;
	int vitesseJump;
	
	virtual bool isMovePossible();

	bool affectedByGravity = true;

	bool attack_b;

	//void loosePV(int pv);

private:
	AStar* path;
	clock_t t = 0;

	int speed_run;
	int split;
	bool run;
	
	void set_gravity_vecteurAcceleration();
	void calc_vecteurVitesse();
	void calc_position();
	void updateHitbox();

	
};

