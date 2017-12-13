#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>

#include <string>
#include <list>
#include <vector>

#include "World.h"
#include "Island.h"
#include "Dimension.h"
#include "Area.h"
#include "View.h"
#include "Connector.h"
#include "Gate.h"

using namespace std;

class SOCKControler
{
public:
	SOCKControler(/*SOCKET sock, */World* world, View* view);
	~SOCKControler();

	//Function executed in two thread
	void listenActions();
	void processActions();
	
	//Stop all the process
	void stopProcess();

	//Send message to the server
	void sendAction(string action);

	//Debug function : Simulate an order coming from server
	void testSendOrders(string data);

private:
	//SOCKET sock; //Sock object for communication width server
	World* world; // Object world to acccess to elements and interact
	View* view; // Object view

	list<string> rowDataActions; //List of all string recive from the server
	bool run; //Bool control the SOCK loops (while(run))

	void executeActions(string action); //Split action into category : info, action, loading for treatment

	void information(string rowData); //Treat information from server

	void action(string rowData); //Treat action from server

	void loading(string rowData); //Treat loading information from server : split into : MotionLess, Hero, Monster, NPC
	void loadingMotionLess(string rowData); //Create MotionLess from server string
	void loadingHero(string rowData); //Create Hero from server string
	void loadingMonster(string rowData); //Create Monster from server string
	void loadingNPC(string rowData); //Create NPC from server string


	void endOfConnection(exception e = std::exception(NULL)); //Default value : null

	//Split a string by separator
	vector<string> split_1(const string& str, const char& ch);
	vector<string> split_2(string str, string sep);

	//Debug function : simulate lodaing iformation from server
	void testFirstMap();
};

