#include "Symbol.h"

/*
-Rename function
-epsilon -> makes inactive
	rename node to "epsilon" make this.node inactive!
	apply rule-> if name of new Symbol is epsilon -> make this.child inactive
	apply rule-> after a rule is applied make this.node inactive
-Occlusion
	
*/

	//Standard Comstructor
	Symbol::Symbol()
	{
		terminal=false;
		drawable=true;
		active=true;
	}
	
	//constructor creating a Symbol with position, scale and name.
	Symbol::Symbol(vector<double> p,vector<double> s,string n)
	{
		position = p;
		scale = s;
		name = n;

		terminal=false;
		drawable=true;
		active=true;
	}
	Symbol::Symbol(double posX,double posY,double posZ,double scaleX,double scaleY,double scaleZ,string n){
		name = n;

		position.push_back(posX);
		position.push_back(posY);
		position.push_back(posZ);
		scale.push_back(scaleX);
		scale.push_back(scaleY);
		scale.push_back(scaleZ);

		terminal=false;
		drawable=true;
		active=true;
	}

	/*
	================
	SCOPE Rules 
	================
	*/

	//translation
	Symbol Symbol::T(double x, double y, double z, string n)
	{ 
		// 14.03.14_by Ruotong Li
		// when do the translating, we only need to move the position of symbol to the new place, other parameters don't change
		
		Symbol *deriv_Element = new Symbol( position, scale, n);
		
		deriv_Element -> position[0] = position[0] + x;
		deriv_Element -> position[1] = position[1] + y;
		deriv_Element -> position[2] = position[2] + z;

		return *deriv_Element;
	}
	
	//Scale
	Symbol Symbol::S(double x, double y, double z, string n)
	{
		// 14.03.14_by Ruotong Li
		// when do the scaling, nothing but the scale of the symbol has changed.
		Symbol *deriv_Element = new Symbol( position, scale, n);

		deriv_Element -> scale[0] = scale[0] * x;
		deriv_Element -> scale[1] = scale[1] * y;
		deriv_Element -> scale[2] = scale[2] * z;

		return *deriv_Element;
	}

	//rotation around y Axis
	void Symbol::R(double r)
	{
		//Your code here...
	}

	// 10.04.2014 by Li,Ruotong ++add new function
	Symbol Symbol::extrude ( vector<double> v, string n)
	{
		// 10.04.14_by Ruotong Li
		// when do the extrude, check the "0" scale value and replace it.
		Symbol *deriv_Element = new Symbol( position, scale, n);
		vector<double> :: iterator it_v = v.begin();

		// check the scale vector, and when find the value equals 0, replace it by the double value of v
		for ( int i = 0; i < 3; i ++)
		{
			if ( deriv_Element -> scale[i] == 0 )
			{
				deriv_Element -> scale[i] = *it_v;
				it_v ++;
			}
			else
				continue;
		}

		return *deriv_Element;
	}


	// rename the Symbol with a new name
	vector<Symbol> Symbol:: rename ( string symbolName )
	{
		Symbol deriv_Element( position, scale, symbolName);

		if ( symbolName == "epsilon" )
			deriv_Element.active = false;
		else
			deriv_Element.name = symbolName;

		vector<Symbol> deriv;
		deriv.push_back( deriv_Element );
		return deriv;
	}
	
	/*
	================
	PRODUCTION Rules 
	================
	*/

	vector<Symbol>Symbol::subDiv( int d, vector<double>&splits, vector<string> &symbols) // 0-x, 1-y, 2-z; splits are absolute value
	{
		vector<Symbol> derivatives;
		double p_of_newSymbol = position[d];
		// 14.03.14_by Ruotong Li
		/*--------------- Algorithms -----------------*/
		/* 
		the way to impliment this rule:
		1) creat a new symbol with the same position and scale as the parent symbol
		2) scale it into the right size.
		3) translation it to the right position.
		4) push the new symbol into a vector "derivatives"
		*/
		for ( unsigned int i = 0; i < splits.size(); i++)
		{
			// create new symbol
			// Symbol *deriv_Element = new Symbol( position, scale, symbols[i]);
			position[d] = p_of_newSymbol;
			Symbol deriv_Element( position, scale, symbols[i]);	

			// scale
			vector<double> scale_p (3, 1.0);				// create a vector to store the scale parameter
			scale_p[d] = splits[i] / scale[d];			// calculate the scale parameter
			deriv_Element = deriv_Element.S ( scale_p[0], scale_p[1], scale_p[2], symbols[i]);	// call the S function do calculation
			
			p_of_newSymbol += splits[i];
			// translation
			/*
			vector<double> trans_p (3, 0.0);				// create a vector to store the translation parameter
			if ( i == 0 );
			else 
				trans_p [d] += splits[i];					// calculate the position of the new symbol
			deriv_Element = deriv_Element.T (trans_p[0], trans_p[1], trans_p[2], symbols[i]);	// Translate the new symbol
			*/

			// push_back
			derivatives.push_back ( deriv_Element);
		}

		return derivatives;
	}

	vector<Symbol>Symbol::comp( vector<string> symbols)	// s gives us the name of the new Symbol
	{
		vector<Symbol> derivatives;
		
		// 15.03.14_by Ruotong Li
		/*--------------- Algorithms -----------------*/
		/* 
		in the vector of string stores the name of:
		{ buttom, top, sideface1, sideface2... sideface4 }; sidefaces anti-clockwise start with plane-XY.
		for each plane:
		1) create symbol same as parent node
		2) remove one dimention and make sure it's at the right position
		**) don't consider the rotation and ONLY onsider the situation of BOX with 6 faces.!!
		*/
		
		int i = 0;	// use as the index of the namelist
		// 1) splict bottom
		Symbol deriv_Element_01( position, scale, symbols[i]);	// create new symbol
		deriv_Element_01 = deriv_Element_01.S ( 1.0, 0.0, 1.0, symbols[i]);										// remove the Y dimention
		derivatives.push_back (deriv_Element_01);							// push_back
		i ++;

		// 2) splict top
		Symbol deriv_Element_02( position, scale, symbols[i]);	// create new symbol
		deriv_Element_02 = deriv_Element_02.S ( 1.0, 0.0, 1.0, symbols[i]);										// remove the Y dimention
		deriv_Element_02 = deriv_Element_02.T ( 0.0, scale[1], 0.0, symbols[i]);							// tanslate it to the right position
		derivatives.push_back (deriv_Element_02);							// push_back
		i++;

		// 3) splict side_face_1 XY at front
		Symbol deriv_Element_03( position, scale, symbols[i]);	// create new symbol
		deriv_Element_03 = deriv_Element_03.S ( 1.0, 1.0, 0.0, symbols[i]);										// remove the Y dimention
		derivatives.push_back (deriv_Element_03);							// push_back
		i++;

		// 4) splict side_face_1 YZ at right
		Symbol deriv_Element_04( position, scale, symbols[i]);	// create new symbol
		deriv_Element_04 = deriv_Element_04.S ( 0.0, 1.0, 1.0, symbols[i]);										// remove the Y dimention
		deriv_Element_04 = deriv_Element_04.T ( scale[0], 0.0, 0.0, symbols[i]);							// tanslate it to the right position
		derivatives.push_back (deriv_Element_04);							// push_back
		i++;

		// 5) splict side_face_3 XY at back
		Symbol deriv_Element_05( position, scale, symbols[i]);	// create new symbol
		deriv_Element_05 = deriv_Element_05.S ( 1.0, 1.0, 0.0, symbols[i]);										// remove the Y dimention
		deriv_Element_05 = deriv_Element_05.T ( 0.0, 0.0, scale[2], symbols[i]);							// tanslate it to the right position
		derivatives.push_back (deriv_Element_05);							// push_back
		i++;

		// 6) splict side_face_1 YZ at left
		Symbol deriv_Element_06( position, scale, symbols[i]);	// create new symbol
		deriv_Element_06 = deriv_Element_06.S ( 0.0, 1.0, 1.0, symbols[i]);										// remove the Y dimention
		derivatives.push_back (deriv_Element_06);							// push_back
		i++;

		return derivatives;
	}
	
	vector<Symbol>Symbol::repeat( int dim, double size, string symbol)	// 0-x, 1-y, 2-z;
	{
		vector<Symbol> derivatives;

		//10.04.2014 by Jonas Abert
		int number = (int)(scale[dim]/size);
		double total = number*size;
		double rest = scale[dim]-(number*size);
		double add = rest/number;
		
		size= size+add;
	
		

		
		// 15.03.14_by Ruotong Li
		/*--------------- Algorithms -----------------*/
		/*
		1) create the first symbol of repeat element
		2) clone the first sybol and then move it to the right place by call the translation function
		3) reapt step 2)
		*/
		
		int i = 1;							// use as count the number of new crated symbols
		vector<double> scale_p( scale );		// creat a parameter shows the new symbols scale vector
		scale_p[dim] = size;

		while ( size * i <= scale[dim] )
		{
			// 1) create new symbol ( repeat element )
			Symbol deriv_Element( position, scale_p, symbol);	
			
			// 2) tanslaton to the right place
			vector<double> trans_p ( 3, 0 );
			trans_p[dim] = size * ( i - 1 );
			deriv_Element = deriv_Element.T ( trans_p[0], trans_p[1], trans_p[2], symbol );

			// 3) push_back and repeat
			derivatives.push_back (deriv_Element);
			i++;
		}

		// consider about the remaining part
		
		if ( size * i > scale[dim] )
		{
			i --;
			scale_p[dim] = scale[dim]- i * size;
			Symbol deriv_Element( position, scale_p, "remaind");
			vector<double> trans_p ( 3, 0 );
			trans_p[dim] = size * ( i );
			deriv_Element = deriv_Element.T ( trans_p[0], trans_p[1], trans_p[2], deriv_Element.name );
			derivatives.push_back (deriv_Element);
		}

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
