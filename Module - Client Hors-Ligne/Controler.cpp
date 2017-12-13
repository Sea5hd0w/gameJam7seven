#include "Controler.h"

#include <thread>
#include <chrono>

#include "LibraryCommunication.h"


Controler::Controler()
{
	//Create empty world
	this->world = new World();

	//Create view and run the process in a different thread
	this->view = new View(this->world);
	std::thread runView(&View::runView, this->view);

	//Create sockControler to interact with the server. One thread to listen, the other to treat data
	this->sockControler = new SOCKControler(this->world, this->view);
	//std::thread runSOCKControlerListenActions(&SOCKControler::listenActions, this);
	std::thread runSOCKControlerProcessActions(&SOCKControler::processActions, this->sockControler);

	//Create GUIControler to treat intercation with the window (Click, key event,...) and run the process
	this->guiControler = new GUIControler(this->world, this->sockControler, this->view);
	gen("Controler created");
	this->guiControler->runGUIControler();

	//If access to this code : stop process
	this->sockControler->stopProcess();
	this->view->stopProcess();

	//runSOCKControlerListenActions.join();
	runSOCKControlerProcessActions.join();
	runView.join();
}


Controler::~Controler()
{
}
