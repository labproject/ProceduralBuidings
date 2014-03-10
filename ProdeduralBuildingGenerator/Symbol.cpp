#include "mainHeader.h"

	//Standard Comstructor
	Symbol::Symbol(){}
	
	//constructor creating a Symbol with position, scale and name.
	Symbol::Symbol(vector<double> p,vector<double> s,string n)
	{
		position = p;
		scale = s;
		name = n;
	}

	/*
	================
	SCOPE Rules 
	================
	*/

	//translation
	void Symbol::T(double x, double y, double z)
	{
		//Your code here...
	}

	//Scale
	void Symbol::S(double x, double y, double z)
	{
		//Your code here...
	}

	//rotation around y Axis
	void Symbol::R(double r)
	{
		//Your code here...
	}
	
	/*
	================
	PRODUCTION Rules 
	================
	*/

	vector<Symbol>Symbol::subDiv(char dim, vector<double>&splits, vector<string> &symbols)
	{
		vector<Symbol> derivatives;
		//Your code here
		return derivatives;
	}

	vector<Symbol>Symbol::comp(string s)
	{
		vector<Symbol> derivatives;
		//Your code here...
		return derivatives;
	}
	
	vector<Symbol>Symbol::repeat(char dim, double size, string symbol)
	{
		vector<Symbol> derivatives;
		//Your code here...
		return derivatives;
	}


