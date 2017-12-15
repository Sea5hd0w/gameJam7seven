#pragma once

#include <stdio.h>
#include <SDL.h>

#include "World.h"
#include "View.h"

using namespace std;

class GUIControler
{
public:
	GUIControler(World* world, View* view);
	~GUIControler();

	void runGUIControler(); //Main loop of GUI

private:
	World* world; // Object world to acccess to elements and interact
	View* view; // Object view to acccess to mainWindow dimension
	bool run; //Bool control the GUI loop (while(run))

	void loadTXT(string path);

	void executeActions(string action);
	
	void information(string rowData);

	void loading(string rowData); //Treat loading information from server : split into : MotionLess, Hero, Monster, NPC
	void loadingMotionLess(string rowData); //Create MotionLess from server string
	void loadingHero(string rowData); //Create Hero from server string
	void loadingMonster(string rowData); //Create Monster from server string
	void loadingNPC(string rowData); //Create NPC from server string

	vector<string> split_1(const string& str, const char& ch);


	int heightCase = 40; //Size of height classic case
	int wighthCase = 80; //Size of width classic case
	int positionCaseHeight1 = 68; //Distance from image's top and case's top
	int positionCaseHeight2 = 20; //Distance from image's bottom and case's bottom
	int positionCasesSide = 24; //Distance from image's side and case's side

	bool load;
};

