#pragma once
#include <string>

using namespace std;

void writeLog(string file);

string GetIPAdress();

string GetLocalIPAddress();

void gen(string txt);
void des(string txt);
void err(string txt);
void sdl(string txt);
void mov(string txt);

void debug(string txt);
void debugMessage(string txt);

string askOrder();