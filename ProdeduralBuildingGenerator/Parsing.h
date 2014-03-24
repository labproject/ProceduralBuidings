#ifndef __PARSING_H_INCLUDED__
#define __PARSING_H_INCLUDED__

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "GNode.h"
#include <vector>


/*
Please do all your #include operations here in this file like the inclusions above
*/


using namespace std;

/*
Please DECLARE all your functions here in the main (just like the parsing() below;
*/
vector<pair<string,vector<GNode>>> parsing();
bool is_number(string );
void processSubdivParams(string, GNode* );
void processComponentSplitParams(string , GNode* );
void processScaleParams(string , GNode* );
void processRotateParams(string , GNode* );
void processRepeatParams(string , GNode* );
void processSParams(string , GNode* );
void processParameters(string , string , GNode* );

// main processing functions.....
GNode createGNode(string );
void fillDataStructure(string);

//please do not write below this comment, thanks
#endif