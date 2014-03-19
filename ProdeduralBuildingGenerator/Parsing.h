#ifndef __PARSING_H_INCLUDED__
#define __PARSING_H_INCLUDED__

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "GNode.h"
#include "Global.h"
#include <vector>
#include <map>

using namespace std;

//map<string,float>config;

map<string,vector<GNode>> parsing();
void readConfig(string);
void split(string);
void writeGNode(string,vector<string>,vector<string>,vector<string>,vector<string>);


float proceedPROB(string);
float interpret(string);

string proceedFNCT(string);
vector<pair<float,float>> proceedPARAM(string);
vector<string>proceedSYMBID(string);


//please do not write below this comment, thanks
#endif