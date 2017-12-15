#pragma once

#include "World.h"
#include "GUIControler.h"
#include "View.h"

class Controler
{
public:
	Controler();
	~Controler();

private:
	//Every object created by the controler are stored
	World* world; 
	GUIControler* guiControler;
	View* view;
};

void play_music();

