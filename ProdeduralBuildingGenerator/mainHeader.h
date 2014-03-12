#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
===========
CLASS SYMBOL
============
*/
void testENV();

class Symbol
{
public:
	//class Variables

	vector<double>			position;
	vector<double>			scale;
	vector<double>			rotation;
	vector<double>			color; //contains RGB values from 0 to 1
	
	string					name;
	int						occ;	//occupancy 0 = not occupied, 1 = partialy Occupied 2= fully Occupied

	bool					terminal;
	bool					drawable;
	bool					active;
	
	//CONSTRUCTORS
	Symbol();
	Symbol(vector<double>,vector<double>,string);


	//SCOPERULES
	void T(double,double,double);
	void S(double,double,double);
	void R(double);

	//PRODUCTIONRULES
	vector<Symbol>subDiv(char, vector<double>&, vector<string>&);
	vector<Symbol>comp(string);
	vector<Symbol>repeat(char, double, string);

	//GETTERS & SETTERS
	string getName();

	//TEST FUNCTIONS
	vector<Symbol> test();
};


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

