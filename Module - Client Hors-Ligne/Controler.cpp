#pragma comment(lib, "winmm.lib")
#include <windows.h>
#include <mmsystem.h>
#include "Controler.h"

#include <thread>
#include <chrono>

#include "LibraryCommunication.h"


Controler::Controler()
{
	thread thread_1 = thread(play_music);


	//Create empty world
	this->world = new World();

	//Create view and run the process in a different thread
	this->view = new View(this->world);
	std::thread runView(&View::runView, this->view);

	//Create GUIControler to treat intercation with the window (Click, key event,...) and run the process
	this->guiControler = new GUIControler(this->world, this->view);
	gen("Controler created");
	this->guiControler->runGUIControler();

	//If access to this code : stop process
	this->view->stopProcess();

	thread_1.join();
	//runSOCKControlerListenActions.join();
	runView.join();
}


Controler::~Controler()
{
}

void play_music()
{
	PlaySound(TEXT("ressources/sounds/JumperBoy.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	
}
