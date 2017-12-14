#pragma once
class Ammo
{
public:
	Ammo();
	~Ammo();
	void shoot();
	void printSprite(int xPosition, int yPosition);
private:
	const int degat;
	const int vitesse;
	const int ySize;
};

