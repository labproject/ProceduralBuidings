#ifndef __SYMBOL_H_INCLUDED__
#define __SYMBOL_H_INCLUDED__

#include <vector>
#include <string>

using namespace std;

/*
===========
CLASS SYMBOL
============
*/


class Symbol
{
public:
	//CLASS VARIABLES
	vector<double>			position;
	vector<double>			scale;
	vector<double>			rotation;	//4-dimensional Vector ([0] = angle, [1-3] = rotationvector
	vector<double>			color;		//contains RGB values from 0 to 1
	string					name;
	int						occ;	//occupancy 0 = not occupied, 1 = partialy Occupied 2= fully Occupied
	bool					terminal;
	bool					drawable;
	bool					active;
	
	//CONSTRUCTORS
	Symbol();
	Symbol(vector<double>,vector<double>,string);
	//new constructors can be created here!

	//SCOPERULES
	void T(double,double,double);		//What is better, 3 single values or a vector of three values?
	void S(double,double,double);		//What is better, 3 single values or a vector of three values?
	void R(double);

	//PRODUCTIONRULES
	vector<Symbol>		subDiv(char, vector<double>&, vector<string>&);
	vector<Symbol>		comp(string);
	vector<Symbol>		repeat(char, double, string);

	//GETTERS & SETTERS
	string				getName();
	vector<double>		getPosition();
	vector<double>		getScale();
	vector<double>		getRotation();

	//TEST FUNCTIONS
	vector<Symbol> test();
};


#endif