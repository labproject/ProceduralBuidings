#ifndef __GNODE_H_INCLUDED__
#define __GNODE_H_INCLUDED__

#include <string>
#include <vector>

using namespace std;



/*
===========
CLASS GRAMMAROBJECT
============
*/

class GNode
{
public:

	string					function;			//string: name of function to use. for example subDiv, repeat or comp.
	vector<string>			parameters;			//the Parameters for the function stored as strings
	vector<string>			symbolNames;		//The Names of the Symbols we derive from our previous symbol
	GNode();
	GNode(string,string,int);
};


#endif