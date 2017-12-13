#pragma once

#include "World.h"
#include "SOCKControler.h"
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
	SOCKControler* sockControler;
	GUIControler* guiControler;
	View* view;
};

