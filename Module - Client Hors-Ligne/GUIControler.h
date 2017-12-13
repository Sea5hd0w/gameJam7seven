#pragma once

#include <stdio.h>
#include <SDL.h>

#include "World.h"
#include "SOCKControler.h"
#include "View.h"
#include "AStar.h"

using namespace std;

class GUIControler
{
public:
	GUIControler(World* world, SOCKControler* controler, View* view);
	~GUIControler();

	void runGUIControler(); //Main loop of GUI

private:
	World* world; // Object world to acccess to elements and interact
	SOCKControler* controler; // Object sockControler to send message to the server
	View* view; // Object view to acccess to mainWindow dimension
	bool run; //Bool control the GUI loop (while(run))

	long convertX(long x, long y); //Convert orthogonal coordinate in isometric
	long convertY(long x, long y); //Convert orthogonal coordinate in isometric

	void keyCodeInMove(int i, int j, int t);

	int heightCase = 40; //Size of height classic case
	int wighthCase = 80; //Size of width classic case
	int positionCaseHeight1 = 68; //Distance from image's top and case's top
	int positionCaseHeight2 = 20; //Distance from image's bottom and case's bottom
	int positionCasesSide = 24; //Distance from image's side and case's side
};

