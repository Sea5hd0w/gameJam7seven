#include "GUIControler.h"

#include "LibraryCommunication.h"

#include <iostream>
#include <fstream>

#include "HellWolf.h"

#include "variable_static.h"

GUIControler::GUIControler(World* world, View* view)
	: world(world), view(view), run(true)
{
	this->loadTXT("ressources/levels/map.txt");

	gen("GUIControler created : starting Listen & Process instruction");
}


GUIControler::~GUIControler()
{
}


void GUIControler::runGUIControler()
{
	long x = -1;
	long y = -1;
	double v = 3;
	while (run)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			//Treatment of SDL event
			switch (event.type)
			{
			case SDL_KEYUP:
				/*	fprintf(stdout, "Key Down :\n");
				fprintf(stdout, "\trepetition ? : %d\n", event.key.repeat);
				fprintf(stdout, "\tscancode : %d\n", event.key.keysym.scancode);
				fprintf(stdout, "\tkey : %d\n", event.key.keysym.sym);*/
				switch (event.key.keysym.scancode)
				{
				case 89:
					//sdl(to_string(event.key.keysym.scancode) + " : stop DownLeft");
					this->world->getMainHero()->addX(0);
					this->world->getMainHero()->addY(0);
					//this->world->getMainHero()->moveDownLeft(false, 1);
					break;
				case 90:
					//sdl(to_string(event.key.keysym.scancode) + " : stop Down");
					this->world->getMainHero()->addY(0);
					//this->world->getMainHero()->moveDown(false, 1);
					break;
				case 91:
					//sdl(to_string(event.key.keysym.scancode) + " : stop DownRight");
					this->world->getMainHero()->addX(0);
					this->world->getMainHero()->addY(0);
					//this->world->getMainHero()->moveDownRight(false, 1);
					break;
				case 92:
					//sdl(to_string(event.key.keysym.scancode) + " : stop Left");
					this->world->getMainHero()->addX(0);
					//this->world->getMainHero()->moveLeft(false, 1);
					break;
				case 93:
					break;
				case 94:
					//sdl(to_string(event.key.keysym.scancode) + " : stop Right");
					this->world->getMainHero()->addX(0);
					//this->world->getMainHero()->moveRight(false, 1);
					break;
				case 95:
					//sdl(to_string(event.key.keysym.scancode) + " : stop TopLeft");
					this->world->getMainHero()->addX(0);
					this->world->getMainHero()->addY(0);
					//this->world->getMainHero()->moveTopLeft(false, 1);
					break;
				case 96:
					//sdl(to_string(event.key.keysym.scancode) + " : stop Top");
					this->world->getMainHero()->addY(0);
					//this->world->getMainHero()->moveTop(false, 1);
					break;
				case 97:
					//sdl(to_string(event.key.keysym.scancode) + " : stop TopRight");
					this->world->getMainHero()->addX(0);
					this->world->getMainHero()->addY(0);
					//this->world->getMainHero()->moveTopRight(false, 1);
					break;
				}
				break;
			case SDL_KEYDOWN:
				/*fprintf(stdout, "Key Up :\n");
				fprintf(stdout, "\trepetition ? : %d\n", event.key.repeat);
				fprintf(stdout, "\tscancode : %d\n", event.key.keysym.scancode);
				fprintf(stdout, "\tkey : %d\n", event.key.keysym.sym);*/
				
				switch (event.key.keysym.scancode)
				{
					case 89:
						//sdl(to_string(event.key.keysym.scancode) + " : Move DownLeft");
						this->world->getMainHero()->moveDownLeft(false, 1);
						break;
					case 90:
						//sdl(to_string(event.key.keysym.scancode) + " : Move Down");
						//this->world->getMainHero()->addY(v);
						this->world->getMainHero()->moveDown(false, 1);
						break;
					case 91:
						//sdl(to_string(event.key.keysym.scancode) + " : Move DownRight");
						this->world->getMainHero()->moveDownRight(false, 1);
						break;
					case 92:
						//sdl(to_string(event.key.keysym.scancode) + " : Move Left");
						this->world->getMainHero()->moveLeft(false, 1);
						break;
					case 93:
						break;
					case 94:
						//sdl(to_string(event.key.keysym.scancode) + " : Move Right");
						this->world->getMainHero()->moveRight(false, 1);
						break;
					case 95:
						//sdl(to_string(event.key.keysym.scancode) + " : Move TopLeft");
						this->world->getMainHero()->moveTopLeft(false, 1);
						break;
					case 96:
						//sdl(to_string(event.key.keysym.scancode) + " : Move Top");
						this->world->getMainHero()->moveTop(false, 1);
						break;
					case 97:
						//sdl(to_string(event.key.keysym.scancode) + " : Move TopRight");
						
						//this->world->getMainHero()->moveTopRight(false, 1);
						break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				this->world->getMainHero()->shoot();
				break;

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


void GUIControler::loadTXT(string path)
{
	std::ifstream file(path);
	std::string str;
	string back;
	int i = 0;
	while (std::getline(file, str))
	{
		if (i == 0) back = str;
		else this->executeActions(str);
		i++;
	}
	this->world->getIsland()->getDimension(0)->addBackground(back);
}

void GUIControler::executeActions(string action)
{
	string p_action = action.substr(0, action.size() - 1);

	//Loading or not
	switch (p_action[0])
	{
	case '1':
		this->loading(p_action);
		break;
	case '3':
		this->information(p_action);
		break;
	}
}
void GUIControler::information(string rowData)
{
	vector<string> data = (this->split_1(rowData, ':'));

	if (data[1] == "MainLoadEnd") //End of the main load : Heros, Stuff, Map of the dimension of the MainHero
	{
		this->world->setLoading(false);
		this->world->getIsland()->getDimension(stol(data[3]))->loadElementsToView();
	}
}

void GUIControler::loading(string rowData)
{
	switch (rowData[2]) //Check what object is loading
	{
	case '0':
		this->loadingMotionLess(rowData);
		break;
	case '1':
		this->loadingHero(rowData);
		break;
	case '2':
		this->loadingMonster(rowData);
		break;
	case '3':
		this->loadingNPC(rowData);
		break;
	}
}

void GUIControler::loadingMotionLess(string rowData)
{
	Area* areaBuffer = NULL;

	vector<string> data = (this->split_1(rowData, ':'));

	//Check if Island exist : else create it
	if (this->world->getIsland() == NULL /* || Recive data of an other island*/)
	{
		this->world->setIsland(new Island(this->world, stol(data[2])));
	}

	//Check if Dimension exist : else create it
	if (!this->world->getIsland()->isDimension(stol(data[3])))
	{
		this->world->getIsland()->addDimension(stol(data[3]), new Dimension(this->world, stol(data[2]), stol(data[3])));
	}

	//Check if Area exist : else create it
	if (!this->world->getIsland()->getDimension(stol(data[3]))->isArea(stol(data[4]), stol(data[5])))
	{
		areaBuffer = new Area(this->world, stol(data[2]), stol(data[3]));
		this->world->getIsland()->getDimension(stol(data[3]))->addArea(stol(data[4]), stol(data[5]), areaBuffer);
	}
	else
	{
		areaBuffer = this->world->getIsland()->getDimension(stol(data[3]))->getArea(stol(data[4]), stol(data[5]));
	}

	//Create element : ID 0 to 12 : basic, 13 & 14 Connector, 15 : Gate
	if ((stol(data[7])) < 12) //If motionLess is a basic
	{
		long x = stol(data[4])*variable::SIZE_CASE_X;
		long y = stol(data[5])*variable::SIZE_CASE_Y;
		areaBuffer->addElement(make_tuple(x, y, 0), MotionLess::getMotionLess(stol(data[7]), this->world, stol(data[2]), stol(data[3]), make_tuple(x, y, 0), data[8]));
	}
	else if ((stol(data[7])) < 15)
	{
		//areaBuffer->addElement(make_tuple(stol(data[4]), stol(data[5]), stol(data[6])), Connector::getConnector(stol(data[7]), this->world, stol(data[2]), stol(data[3]), make_tuple(stol(data[4]), stol(data[5]), stol(data[6])), data[8], data[9].at(0) == '1'));
	}
	else
	{
		//areaBuffer->addElement(make_tuple(stol(data[4]), stol(data[5]), stol(data[6])), Gate::getGate(stol(data[7]), this->world, stol(data[2]), stol(data[3]), make_tuple(stol(data[4]), stol(data[5]), stol(data[6])), data[8], (data[9].at(0) == '1'), stol(data[10]), stol(data[11]), make_tuple(stol(data[12]), stol(data[13]), stol(data[14]))));
	}
}

void GUIControler::loadingHero(string rowData)
{
	Area* areaBuffer = NULL;

	vector<string> data = (this->split_1(rowData, ':'));

	if (this->world->getMainHero()) debug("Loading hero");
	Hero* hero = new Hero(this->world, stol(data[2]), stol(data[3]), make_tuple(stol(data[4])*variable::SIZE_CASE_X, stol(data[5])*variable::SIZE_CASE_Y, stol(data[6])), false, data[8], stoi(data[7]), stol(data[9]));

	//Check if MainHero exist : else create it
	if (this->world->getMainHero() == NULL)
	{
		this->world->setMainHero(hero);
	}

	//Check if Island exist : else create it
	if (this->world->getIsland() == NULL /* || Recive data of an other island*/)
	{
		this->world->setIsland(new Island(this->world, stol(data[2])));
	}

	//Check if Dimension exist : else create it
	if (!this->world->getIsland()->isDimension(stol(data[3])))
	{
		this->world->getIsland()->addDimension(stol(data[3]), new Dimension(this->world, stol(data[2]), stol(data[3])));
	}

	//Add Hero to the dimension
	this->world->getIsland()->getDimension(stol(data[3]))->addHero(hero, stol(data[9]));
	debug("AddHEro");
}

void GUIControler::loadingMonster(string rowData)
{
	Area* areaBuffer = NULL;

	vector<string> data = (this->split_1(rowData, ':'));

	Monster* monster = NULL;

	if (stol(data[10]) == 1)
	{
		monster = new HellWolf(this->world, stol(data[2]), stol(data[3]), make_tuple(stol(data[4])*variable::SIZE_CASE_X, stol(data[5])*variable::SIZE_CASE_Y, stol(data[6])), false, "ressources/graphics/motionless/Enemi_Debug_Type1.bmp", stoi(data[7]), stol(data[9]));
	}
	else if (stol(data[10]) == 2)
	{
		monster = new Monster(this->world, stol(data[2]), stol(data[3]), make_tuple(stol(data[4])*variable::SIZE_CASE_X, stol(data[5])*variable::SIZE_CASE_Y, stol(data[6])), false, data[8], stoi(data[7]), stol(data[9]));
	}



	//Check if Island exist : else create it
	if (this->world->getIsland() == NULL /* || Recive data of an other island*/)
	{
		this->world->setIsland(new Island(this->world, stol(data[2])));
	}

	//Check if Dimension exist : else create it
	if (!this->world->getIsland()->isDimension(stol(data[3])))
	{
		this->world->getIsland()->addDimension(stol(data[3]), new Dimension(this->world, stol(data[2]), stol(data[3])));
	}

	//Add Hero to the dimension
	this->world->getIsland()->getDimension(stol(data[3]))->addMonster(monster, stol(data[9]));
	debug("AddMonster");
}

void GUIControler::loadingNPC(string rowData)
{

}

vector<string> GUIControler::split_1(const string& str, const char& ch) {
	string next;
	vector<string> result;

	// For each character in the string
	for (string::const_iterator it = str.begin(); it != str.end(); it++) {
		// If we've hit the terminal character
		if (*it == ch) {
			// If we have some characters accumulated
			if (!next.empty()) {
				// Add them to the result vector
				result.push_back(next);
				next.clear();
			}
		}
		else {
			// Accumulate the next character into the sequence
			next += *it;
		}
	}
	if (!next.empty())
		result.push_back(next);
	return result;
}