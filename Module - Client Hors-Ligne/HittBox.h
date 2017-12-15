#pragma once


class Dimension;
class Element;
class Mobile;
class Hitbox
{
public:
	Hitbox(Mobile* mob, long dephaseX, long dephaseY, Dimension* d, long* mobX, long* mobY);
	bool detect_collision();

	long getPosX();
	long getPosY();

	void updatePos();
	Mobile* mob;
private:
	long* mobX;
	long* mobY;
	long posX, posY, dephaseX, dephaseY;
	Dimension* dim;

};