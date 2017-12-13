#include "GUIControler.h"

#include "LibraryCommunication.h"


GUIControler::GUIControler(World* world, SOCKControler* controler, View* view)
	: world(world), controler(controler), view(view), run(true)
{
	gen("GUIControler created : starting Listen & Process instruction");
}


GUIControler::~GUIControler()
{
}


void GUIControler::runGUIControler()
{
	long x = -1;
	long y = -1;

	while (run)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			//Treatment of SDL event
			switch (event.type)
			{
			case SDL_KEYDOWN:
				/*	fprintf(stdout, "Key Down :\n");
				fprintf(stdout, "\trepetition ? : %d\n", event.key.repeat);
				fprintf(stdout, "\tscancode : %d\n", event.key.keysym.scancode);
				fprintf(stdout, "\tkey : %d\n", event.key.keysym.sym);*/
				break;
			case SDL_KEYUP:
				/*fprintf(stdout, "Key Up :\n");
				fprintf(stdout, "\trepetition ? : %d\n", event.key.repeat);
				fprintf(stdout, "\tscancode : %d\n", event.key.keysym.scancode);
				fprintf(stdout, "\tkey : %d\n", event.key.keysym.sym);*/

				switch (event.key.keysym.scancode)
				{
					case 89:
						sdl(to_string(event.key.keysym.scancode) + " : Move DownLeft");
						this->world->getMainHero()->moveDownLeft(false, 1);

						break;
					case 90:
						sdl(to_string(event.key.keysym.scancode) + " : Move Down");
						this->world->getMainHero()->moveDown(false, 1);

						break;
					case 91:
						sdl(to_string(event.key.keysym.scancode) + " : Move DownRight");
						this->world->getMainHero()->moveDownRight(false, 1);

						break;
					case 92:
						sdl(to_string(event.key.keysym.scancode) + " : Move Left");
						this->world->getMainHero()->moveLeft(false, 1);

						break;
					case 93:
						this->controler->testSendOrders(askOrder());
						break;
					case 94:
						sdl(to_string(event.key.keysym.scancode) + " : Move Right");
						this->world->getMainHero()->moveRight(false, 1);

						break;
					case 95:
						sdl(to_string(event.key.keysym.scancode) + " : Move TopLeft");
						this->world->getMainHero()->moveTopLeft(false, 1);

						break;
					case 96:
						sdl(to_string(event.key.keysym.scancode) + " : Move Top");
						this->world->getMainHero()->moveTop(false, 1);

						break;
					case 97:
						sdl(to_string(event.key.keysym.scancode) + " : Move TopRight");
						this->world->getMainHero()->moveTopRight(false, 1);
						break;
				}
				break;
				/*
				case SDL_MOUSEMOTION:
					fprintf(stdout, "Mouse move :\n");
					fprintf(stdout, "\twindow : %d\n", event.motion.windowID);
					fprintf(stdout, "\tmouse : %d\n", event.motion.which);
					fprintf(stdout, "\tposition : %d;%d\n", event.motion.x, event.motion.y);
					fprintf(stdout, "\tdelta : %d;%d\n", event.motion.xrel, event.motion.yrel);
				break;*/
				case SDL_MOUSEBUTTONUP:
					//sdl("KeyUp [" + to_string(event.button.x) + ":" + to_string(event.button.y) + "]");
					/*fprintf(stdout, "Mouse button up :\n");
					fprintf(stdout, "\twindow : %d\n", event.button.windowID);
					fprintf(stdout, "\tmouse : %d\n", event.button.which);
					fprintf(stdout, "\tbutton : %d\n", event.button.button);
					#if SDL_VERSION_ATLEAST(2,0,2)
					fprintf(stdout, "\tclics : %d\n", event.button.clicks);
					#endif
					fprintf(stdout, "\tposition : %d;%d\n", event.button.x, event.button.y);*/
				break;
				case SDL_MOUSEBUTTONDOWN:
					x = convertX(event.button.x, event.button.y);
					y = convertY(event.button.x, event.button.y);
					if (x >= 0 && y >= 0)
					{
						sdl("KeyDown [" + to_string(event.button.x) + ":" + to_string(event.button.y) + "] - [" + to_string(x - (x%100)) + ":" + to_string(y - (y % 100)) + "]");
						this->world->getMainHero()->moveAStar(x - (x % 100), y - (y % 100));
					}
					/*fprintf(stdout, "Mouse button down\n");
					fprintf(stdout, "\twindow : %d\n", event.button.windowID);
					fprintf(stdout, "\tmouse : %d\n", event.button.which);
					fprintf(stdout, "\tbutton : %d\n", event.button.button);
					#if SDL_VERSION_ATLEAST(2,0,2)
					fprintf(stdout, "\tclics : %d\n", event.button.clicks);
					#endif
					fprintf(stdout, "\tposition : %d;%d\n", event.button.x, event.button.y);*/
				break;/*
				case SDL_MOUSEWHEEL:
					fprintf(stdout, "Wheel of mouse :\n");
					fprintf(stdout, "\twindow : %d\n", event.wheel.windowID);
					fprintf(stdout, "\tmouse : %d\n", event.wheel.which);
					fprintf(stdout, "\tposition : %d;%d\n", event.wheel.x, event.wheel.y);
				break;

				case SDL_JOYDEVICEADDED:
					fprintf(stdout, "Joystick added :\n");
					fprintf(stdout, "\tjoystick : %d\n", event.jdevice.which);
				break;
				case SDL_JOYDEVICEREMOVED:
					fprintf(stdout, "Joystick removed :\n");
					fprintf(stdout, "\tjoystick : %d\n", event.jdevice.which);

				break;
				case SDL_JOYAXISMOTION:
					fprintf(stdout, "Movement joystick :\n");
					fprintf(stdout, "\tjoystick : %d\n", event.jaxis.which);
					fprintf(stdout, "\taxis : %d\n", event.jaxis.axis);
					fprintf(stdout, "\value : %d\n", event.jaxis.value);
				break;
				case SDL_JOYBUTTONDOWN:
					fprintf(stdout, "Joystick buttom down:\n");
					fprintf(stdout, "\tjoystick : %d\n", event.jbutton.which);
					fprintf(stdout, "\tbutton : %d\n", event.jbutton.button);
					fprintf(stdout, "\tstate : %d\n", event.jbutton.state);
				break;
				case SDL_JOYBUTTONUP:
					fprintf(stdout, "Joystick button up:\n");
					fprintf(stdout, "\tjoystick : %d\n", event.jbutton.which);
					fprintf(stdout, "\tbutton : %d\n", event.jbutton.button);
					fprintf(stdout, "\tstate : %d\n", event.jbutton.state);
				break;
				case SDL_JOYBALLMOTION:
					fprintf(stdout, "Trackball movement :\n");
					fprintf(stdout, "\tjoystick : %d\n", event.jball.which);
					fprintf(stdout, "\ttrackball : %d\n", event.jball.ball);
					fprintf(stdout, "\tmovement : %d;%d\n", event.jball.xrel, event.jball.yrel);
				break;
				case SDL_JOYHATMOTION:
					fprintf(stdout, "Joystick hat movement :\n");
					fprintf(stdout, "\tjoystick : %d\n", event.jhat.which);
					fprintf(stdout, "\tbutton : %d\n", event.jhat.hat);
					fprintf(stdout, "\tvalue : %d\n", event.jhat.value);
				break;
				case SDL_WINDOWEVENT:
				fprintf(stdout, "Window event on window: %d\n", event.window.windowID);
				break;*/
				case SDL_QUIT:
					this->run = false;
				break;
				default:
					//sdl("Event : " + to_string(event.type));
				break;
			}
		}
	}
}

long GUIControler::convertX(long x, long y)
{
	//Initialize
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;

	//Get current window size
	int xW = this->view->getWindowSize().first;
	int yW = this->view->getWindowSize().second;

	//Get hero postion (Can be the curent position or an other to fix camera)
	int xH = this->world->getMainHero()->getX();
	int yH = this->world->getMainHero()->getY();
	int zH = this->world->getMainHero()->getZ();

	//Calculate coordinate of the start of the hero case sprite in X
	x1 = xW / 2 - (128 / 2 - positionCasesSide);
	//Calculate coordinate of the end of the hero case sprite in X
	x2 = x1 + wighthCase;

	//Calculate coordinate of the start of the hero case sprite in Y
	y1 = yW / 2;
	//Calculate coordinate of the end of the hero case sprite in Y
	y2 = y1 + heightCase;


	int b = (x1 + (wighthCase / 2)) / 2 + y1;

	//Try to frame coordinate between the isometric lines : function f(x) = ax + b
	for (int i = -25; i <= 25; i++)
	{
		if (((((b - (x / 2))) + (i*heightCase)) < y) && (((b - (x / 2)) + heightCase + (i*heightCase)) > y))
		{
			return xH + i * 100;
		}
	}
	return -1;
}

long GUIControler::convertY(long x, long y)
{
	//Initialize
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;

	//Get current window size
	int xW = this->view->getWindowSize().first;
	int yW = this->view->getWindowSize().second;

	//Get hero postion (Can be the curent position or an other to fix camera)
	int xH = this->world->getMainHero()->getX();
	int yH = this->world->getMainHero()->getY();
	int zH = this->world->getMainHero()->getZ();

	//Calculate coordinate of the start of the hero case sprite in X
	x1 = xW / 2 - (128 / 2 - positionCasesSide);
	//Calculate coordinate of the end of the hero case sprite in X
	x2 = x1 + wighthCase;

	//Calculate coordinate of the start of the hero case sprite in Y
	y1 = yW / 2;
	//Calculate coordinate of the end of the hero case sprite in Y
	y2 = y1 + heightCase;


	int b = b = y1 - ((x1 + (wighthCase / 2)) / 2);

	//Try to frame coordinate between the isometric lines : function f(x) = ax + b
	for (int i = -25; i <= 25; i++)
	{
		if (((((b + (x / 2))) + (i*heightCase)) < y) && ((((b + (x / 2)) + heightCase) + (i*heightCase)) > y))
		{ 
			return yH + i*100;
		}
	}
	return -1;
}