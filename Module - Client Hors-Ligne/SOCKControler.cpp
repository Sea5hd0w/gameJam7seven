#include "SOCKControler.h"
#include "LibraryCommunication.h"

#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

#include "LibraryCommunication.h"


SOCKControler::SOCKControler(/*SOCKET sock, */World* world, View* view)
{
	//this->sock = sock;
	this->world = world;
	this->view = view;

	this->run = true;

	this->testFirstMap();

	gen("SOCKControler created : starting Listen & Process instruction");
}


SOCKControler::~SOCKControler()
{
}


void SOCKControler::listenActions() //Loop to listen action of server
{
	char buffer[1024];  // Data buffer for incoming data.

	try
	{
		while (this->run)
		{
			memset(buffer, 0, sizeof buffer); // Reset buffer
			//recv(sock, buffer, sizeof(buffer), 0); // Recive messages

			this->rowDataActions.push_back(string(buffer)); //Add the buffer to the list of actions
			memset(buffer, 0, sizeof buffer); // Reset buffer
		}
	}
	catch (exception e)
	{
		this->endOfConnection(e);
	}
}

void SOCKControler::processActions() // Process the strings recive from the server
{
	//Stack the first string of dataAction
	string firstLine = "";

	//Case of a string is cut in the middle, the right side is stored
	string trunkedAction = "";

	vector<string> lines;

	while (run)
	{
		//Security : Any string to process
		if (!this->rowDataActions.empty())
		{
			//Select the first line
			firstLine = rowDataActions.front();

			if (!firstLine.empty())
			{
				lines = (this->split_1(firstLine, '<'));
				for (int i = 0; i < lines.size(); i++)
				{
					if (lines[i][lines[i].length() - 1] != '>')
					{
						trunkedAction = lines[i];
					}
					else if (trunkedAction.length() != 0) //Case the last string processed wasn't complete, we merge the last and the actual
					{
						// Action = trunkedAction + lines[i]
						executeActions(trunkedAction + lines[i]);
						trunkedAction = ""; // Delete the old piece of action
					}
					else
					{
						// Action = lines[i]
						executeActions(lines[i]);
					}
				}
			}
			this->rowDataActions.pop_front(); //Remove the processed line from the list
			firstLine = ""; //Reset first line
		}
	}
}

void SOCKControler::stopProcess()
{
	this->run = false;
}

void SOCKControler::executeActions(string action)
{
	string p_action = action.substr(0, action.size() - 1);

	//Loading or not
	switch (p_action[0])
	{
	case '1':
		this->loading(p_action);
		break;
	case '2':
		this->action(p_action);
		break;
	case '3':
		this->information(p_action);
		break;
	}
}

void SOCKControler::sendAction(string action) //Send action to server
{
	debugMessage(action);
	/*try
	{
		string actionToSend = "<" + action + ">";
		send(sock, actionToSend.c_str(), actionToSend.size(), 0);
	}
	catch (exception e)
	{
		this->endOfConnection(e);
	}*/
}

void SOCKControler::endOfConnection(exception e) // Close the connection & Disconect the player of the game
{
}


vector<string> SOCKControler::split_1(const string& str, const char& ch) {
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

vector<string> SOCKControler::split_2(string str, string sep) {
	char* cstr = const_cast<char*>(str.c_str());
	char* current;
	std::vector<std::string> arr;
	current = strtok_s(cstr, sep.c_str(), NULL);
	while (current != NULL) {
		arr.push_back(current);
		current = strtok_s(NULL, sep.c_str(), NULL);
	}
	return arr;
}

void SOCKControler::testSendOrders(string data)
{
	this->rowDataActions.push_back(data);
}


void SOCKControler::testFirstMap()
{
	string dataHero = "<1:1:0:0:0:0:0:0:ressources/graphics/motionless/Hero_Debug_Type2.bmp:0>";
	this->rowDataActions.push_back(dataHero);

	string dataMotionLess = "<1:0:0:0:";


	/*TEST SLOPE*/
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			if (x == 2 && y == 4 ||
				x == 4 && y == 1 ||
				x == 5 && y == 1 ||
				x == 6 && y == 1 ||
				x == 7 && y == 7 ||
				x == 7 && y == 8 ||
				x == 8 && y == 8 
				)
			{
				this->rowDataActions.push_back(dataMotionLess + to_string(x * 100) + ":" + to_string(y * 100) + ":0:3:ressources/graphics/motionless/Bloc_Debug_Type1.bmp>");
				this->rowDataActions.push_back(dataMotionLess + to_string(x * 100) + ":" + to_string(y * 100) + ":100:2:ressources/graphics/motionless/Floor_Debug_Type2.bmp>");
			}
			else if (x == 3 && y == 4 ||
					x == 7 && y == 1 ||
					x == 9 && y == 9
				)
			{
				this->rowDataActions.push_back(dataMotionLess + to_string(x * 100) + ":" + to_string(y * 100) + ":0:6:ressources/graphics/motionless/Slope3_Debug_Type1.bmp>");
			}
			else if (x == 2 && y == 3)
			{
				this->rowDataActions.push_back(dataMotionLess + to_string(x * 100) + ":" + to_string(y * 100) + ":0:4:ressources/graphics/motionless/Slope1_Debug_Type1.bmp>");
			}
			else if (x == 1 && y == 4)
			{
				this->rowDataActions.push_back(dataMotionLess + to_string(x * 100) + ":" + to_string(y * 100) + ":0:5:ressources/graphics/motionless/Slope7_Debug_Type1.bmp>");
			}
			else if (x == 2 && y == 5)
			{
				this->rowDataActions.push_back(dataMotionLess + to_string(x * 100) + ":" + to_string(y * 100) + ":0:7:ressources/graphics/motionless/Slope5_Debug_Type1.bmp>");
			}
			else if (x == 8 && y == 7)
			{
				this->rowDataActions.push_back(dataMotionLess + "800:700:0:10:ressources/graphics/motionless/Ladder3_Debug_Type1.bmp>");
			}
			else if (x == 3 && y == 7)
			{
				this->rowDataActions.push_back(dataMotionLess + to_string(x * 100) + ":" + to_string(y * 100) + ":0:3:ressources/graphics/motionless/Bloc_Debug_Type2.bmp>");
			}
			else
			{
				this->rowDataActions.push_back(dataMotionLess + to_string(x * 100) + ":" + to_string(y * 100) + ":0:2:ressources/graphics/motionless/Floor_Debug_Type1.bmp>");
			}
		}
	}

	for (int z = 1; z < 5; z++)
	{
		this->rowDataActions.push_back(dataMotionLess + "700:700:" + to_string(z*100) + ":3:ressources/graphics/motionless/Bloc_Debug_Type1.bmp>");
		this->rowDataActions.push_back(dataMotionLess + "700:800:" + to_string(z * 100) + ":3:ressources/graphics/motionless/Bloc_Debug_Type1.bmp>");
		this->rowDataActions.push_back(dataMotionLess + "800:700:" + to_string(z * 100) + ":10:ressources/graphics/motionless/Ladder3_Debug_Type1.bmp>");
		this->rowDataActions.push_back(dataMotionLess + "800:800:" + to_string(z * 100) + ":3:ressources/graphics/motionless/Bloc_Debug_Type1.bmp>");

		this->rowDataActions.push_back(dataMotionLess + "1400:1500:" + to_string(z * 100) + ":9:ressources/graphics/motionless/Ladder7_Debug_Type1.bmp>");
		this->rowDataActions.push_back(dataMotionLess + "1500:1400:" + to_string(z * 100) + ":8:ressources/graphics/motionless/Ladder1_Debug_Type1.bmp>");
		this->rowDataActions.push_back(dataMotionLess + "1600:1500:" + to_string(z * 100) + ":10:ressources/graphics/motionless/Ladder3_Debug_Type1.bmp>");
		this->rowDataActions.push_back(dataMotionLess + "1500:1600:" + to_string(z * 100) + ":11:ressources/graphics/motionless/Ladder5_Debug_Type1.bmp>");
		this->rowDataActions.push_back(dataMotionLess + "1500:1500:" + to_string(z * 100) + ":3:ressources/graphics/motionless/Bloc_Debug_Type1.bmp>");
	}
	this->rowDataActions.push_back(dataMotionLess + "700:700:500:2:ressources/graphics/motionless/Floor_Debug_Type2.bmp>");
	this->rowDataActions.push_back(dataMotionLess + "700:800:500:2:ressources/graphics/motionless/Floor_Debug_Type2.bmp>");
	this->rowDataActions.push_back(dataMotionLess + "800:700:500:2:ressources/graphics/motionless/Floor_Debug_Type2.bmp>");
	this->rowDataActions.push_back(dataMotionLess + "800:800:500:2:ressources/graphics/motionless/Floor_Debug_Type2.bmp>");

	this->rowDataActions.push_back(dataMotionLess + "1500:1500:500:2:ressources/graphics/motionless/Floor_Debug_Type2.bmp>");
	this->rowDataActions.push_back(dataMotionLess + "1400:1500:500:2:ressources/graphics/motionless/Floor_Debug_Type2.bmp>");
	this->rowDataActions.push_back(dataMotionLess + "1500:1400:500:2:ressources/graphics/motionless/Floor_Debug_Type2.bmp>");
	this->rowDataActions.push_back(dataMotionLess + "1600:1500:500:2:ressources/graphics/motionless/Floor_Debug_Type2.bmp>");
	this->rowDataActions.push_back(dataMotionLess + "1500:1600:500:2:ressources/graphics/motionless/Floor_Debug_Type2.bmp>");

	this->rowDataActions.push_back(dataMotionLess + "800:900:100:6:ressources/graphics/motionless/Slope3_Debug_Type1.bmp>");
	this->rowDataActions.push_back(dataMotionLess + "700:900:200:6:ressources/graphics/motionless/Slope3_Debug_Type1.bmp>");
	this->rowDataActions.push_back(dataMotionLess + "600:900:200:3:ressources/graphics/motionless/Bloc_Debug_Type1.bmp>");
	this->rowDataActions.push_back(dataMotionLess + "600:900:300:2:ressources/graphics/motionless/Floor_Debug_Type2.bmp>");

	this->rowDataActions.push_back(dataMotionLess + "600:800:300:7:ressources/graphics/motionless/Slope5_Debug_Type1.bmp>");
	this->rowDataActions.push_back(dataMotionLess + "600:700:400:7:ressources/graphics/motionless/Slope5_Debug_Type1.bmp>");
	this->rowDataActions.push_back(dataMotionLess + "600:600:400:3:ressources/graphics/motionless/Bloc_Debug_Type1.bmp>");
	this->rowDataActions.push_back(dataMotionLess + "600:600:500:2:ressources/graphics/motionless/Floor_Debug_Type2.bmp>");

	this->rowDataActions.push_back(dataMotionLess + "700:600:400:3:ressources/graphics/motionless/Bloc_Debug_Type1.bmp>");
	this->rowDataActions.push_back(dataMotionLess + "700:600:500:2:ressources/graphics/motionless/Floor_Debug_Type2.bmp>");

	this->rowDataActions.push_back(dataMotionLess + "800:600:400:3:ressources/graphics/motionless/Bloc_Debug_Type1.bmp>");
	this->rowDataActions.push_back(dataMotionLess + "800:600:500:2:ressources/graphics/motionless/Floor_Debug_Type2.bmp>");





	/*TEST DOORS*/
	for (int x = 10; x < 20; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			if (x == 16 && y == 4)
			{
				this->rowDataActions.push_back(dataMotionLess + to_string(x * 100) + ":" + to_string(y * 100) + ":0:15:ressources/graphics/motionless/GateDimension_Debug_Type1.bmp:1:0:1:400:500:0>");
			}
			else
			{
				this->rowDataActions.push_back(dataMotionLess + to_string(x * 100) + ":" + to_string(y * 100) + ":0:2:ressources/graphics/motionless/Floor_Debug_Type3.bmp>");
			}
		}
	}


	/*TEST CONNETABLE*/
	for (int x = 0; x < 10; x++)
	{
		for (int y = 10; y < 20; y++)
		{
			if (x  == 5 && y == 15)
			{
				this->rowDataActions.push_back(dataMotionLess + to_string(x * 100) + ":" + to_string(y * 100) + ":0:12:ressources/graphics/motionless/Sensor_Debug_Type1.bmp:0>");
			}
			else if (x == 7 && y == 18)
			{
				this->rowDataActions.push_back(dataMotionLess + to_string(x * 100) + ":" + to_string(y * 100) + ":0:13:ressources/graphics/motionless/Sensor_Debug_Type2.bmp:0>");
			}
			else if (x == 3 && y == 14)
			{
				this->rowDataActions.push_back(dataMotionLess + to_string(x * 100) + ":" + to_string(y * 100) + ":0:14:ressources/graphics/motionless/Actuator_Debug_Type1.bmp:0>");
			}
			else
			{
				this->rowDataActions.push_back(dataMotionLess + to_string(x * 100) + ":" + to_string(y * 100) + ":0:2:ressources/graphics/motionless/Floor_Debug_Type3.bmp>");
			}
		}
	}

	/*TEST LADDER*/
	for (int x = 10; x < 30; x++)
	{
		for (int y = 10; y < 30; y++)
		{
			if (x == 14 && y == 15)
			{
				this->rowDataActions.push_back(dataMotionLess + to_string(x * 100) + ":" + to_string(y * 100) + ":0:9:ressources/graphics/motionless/Ladder7_Debug_Type1.bmp>");
			}
			else if (x == 15 && y == 14)
			{
				this->rowDataActions.push_back(dataMotionLess + to_string(x * 100) + ":" + to_string(y * 100) + ":0:8:ressources/graphics/motionless/Ladder1_Debug_Type1.bmp>");
			}
			else if (x == 16 && y == 15)
			{
				this->rowDataActions.push_back(dataMotionLess + to_string(x * 100) + ":" + to_string(y * 100) + ":0:10:ressources/graphics/motionless/Ladder3_Debug_Type1.bmp>");
			}
			else if (x == 15 && y == 16)
			{
				this->rowDataActions.push_back(dataMotionLess + to_string(x * 100) + ":" + to_string(y * 100) + ":0:11:ressources/graphics/motionless/Ladder5_Debug_Type1.bmp>");
			}
			else if (x == 15 && y == 15)
			{
				this->rowDataActions.push_back(dataMotionLess + to_string(x * 100) + ":" + to_string(y * 100) + ":0:3:ressources/graphics/motionless/Bloc_Debug_Type1.bmp>");
			}
			else
			{ 
				this->rowDataActions.push_back(dataMotionLess + to_string(x * 100) + ":" + to_string(y * 100) + ":0:2:ressources/graphics/motionless/Floor_Debug_Type1.bmp>");
			}
		}
	}




	this->rowDataActions.push_back("<3:MainLoadEnd:0:0>");

	dataMotionLess = "<1:0:0:1:";
	for (int x = 0; x <10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			if (x == 7 && y == 7)
			{
				this->rowDataActions.push_back(dataMotionLess + to_string(x * 100) + ":" + to_string(y * 100) + ":0:15:ressources/graphics/motionless/GateDimension_Debug_Type1.bmp:1:0:0:1500:500:0>");
			}
			else
			{
				this->rowDataActions.push_back(dataMotionLess + to_string(x*100) + ":" + to_string(y*100) + ":0:2:ressources/graphics/motionless/Floor_Debug_Type3.bmp>");
			}
		}
	}

	//this->rowDataActions.push_back("<3:MainLoadEnd:0:1>");

}
