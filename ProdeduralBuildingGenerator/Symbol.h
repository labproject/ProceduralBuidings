#ifndef __SYMBOL_H_INCLUDED__
#define __SYMBOL_H_INCLUDED__

#include <iostream>
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
	vector<double>			position;	// 3-dimensinal vector with value corresponding to x,y,z coordinate.
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
	Symbol(double,double,double,double,double,double,string);
	//new constructors can be created here!

	//SCOPERULES
	Symbol T(double,double,double,string);		//What is better, 3 single values or a vector of three values?
	Symbol S(double,double,double, string);		//What is better, 3 single values or a vector of three values?
	void R(double);

	//EXTRUDE
	Symbol extrude ( vector<double> v, string n);

	// RENAME
	vector<Symbol> rename ( string);

	//PRODUCTIONRULES
	vector<Symbol>		subDiv( int, vector<double>&, vector<string>&);
	vector<Symbol>		comp( vector<string> );
	vector<Symbol>		repeat( int, double, string);

	//GETTERS & SETTERS
	string				getName();
	vector<double>		getPosition();
	vector<double>		getScale();
	vector<double>		getRotation();

	//TEST FUNCTIONS
	vector<Symbol> test();
};



//please do not write below this comment, thanks
#endif