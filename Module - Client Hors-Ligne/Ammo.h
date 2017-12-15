#pragma once
#include "SDL.h"
#include <string>
#include "Element.h"
#include "audio.h"
using namespace std;
class Ammo : Element
{
public:
	Ammo();
	Ammo(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, int priority, int vitesse, int degat);
	~Ammo();
	
	void shoot(tuple<long, long, long> pointH);
	void printSprite(int xPosition, int yPosition);
	SDL_AudioDeviceID deviceId;
protected: 
	int degat;
	int vitesse;
private:
	void playSound();
	int idBullet;
	int ySize;
	int xSize;
	Audio *sounds;
	SDL_Texture* p_sprite;
	string pathSprite;
};