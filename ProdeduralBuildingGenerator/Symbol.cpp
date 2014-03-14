#include "Symbol.h"

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
		// 14.03.14_by Ruotong Li
		// when do the translating, we only need to move the position of symbol to the new place, other parameters don't change
		p[0] += x;
		p[1] += y;
		p[2] += z;
	}

	//Scale
	void Symbol::S(double x, double y, double z)
	{
		// 14.03.14_by Ruotong Li
		// when do the scaling, nothing but the scale of the symbol has changed.
		s[0] *= x;
		s[1] *= y;
		s[2] *= z;
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
	/*
	================
	GETTERS AND SETTERS 
	================
	*/
	string Symbol::getName()
	{
		return name;
	}


	/*
	================
	TEST Rules 
	================
	*/
	vector<Symbol> Symbol::test()
	{
		vector<Symbol>res;
		Symbol a;
		Symbol b;

		a.name="Box";
		b.name="Facade";

		res.push_back(a);
		res.push_back(b);


	return res;
	}
