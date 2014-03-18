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
//	vector<string>			parameters;			//the Parameters for the function stored as strings
	vector<pair< float, float>> parameters;		// stored as pair is better than string
	/*
	eg:	subdiv ( "Z", scope.sz * rand(0.3,0.5), 2r, 3*window_width, 0.8 ) {...}
	parameters = < < 3, 4 >, < 3, result_of_rand_fuction>, < -1, 2>, < window_width, 3>, < 0, 0.8 > >
	1) in the pair, the two float value represent one parameter.
	2) first pair shows the dimention axis: 1 = X, 2 = Y, 3 = Z, ane divided into "4" part. 
	3) other pairs followed by the first one shows the subdivided length.
	4) when there's random function appears in the parameter, calculate the result first and then store it.
	5) when there's relative values eg.1r, set the first parameter in the pair -1 and second as the parameter of r
	6) when there's a value which is happen to be a variable, then set the first parameter in the pair as the variable, and second as the number multiplied by the variable.
	7) when there's a absolute value, then set the fist number in the pair"0" and second as the absolute value.
	on gerneral, the first pair shows the axis and the number of results(here we subdivided the symbole long z-axis into 4 prats).
	and the following pairs hows a "keyword" represented by number and a number. the "keywords"
	
	eg. scale ( 1r, building_height, 0.9*r)			//also the function of rotate and translate are the same.
	parameter = < < -1, 1>, < building_height, 1>, < -1, 0.9> >
	1) almost the same as the "subdiv", 
	2) the only thing different is we don't need to store the "axis" and numbers of divided parts.

	eg. repeat ("X", 2 )
	parameter = < <1,0> , < 0, 2>>
	1) first pair shows the axis
	2) the second pair shows the value, obey the same rule as "subdiv" parameters

	eg. component-split ( "sidefaces" )
	1) parameter will be an empty vector, since once the symbol is given, there's only one way to split.
	2) please give result with symbolNames vector in such order ( buttomside, topside, sideface1, sideface2, ... sidefaceN)
	3) namethe sidefaces in a anti-clockwise start with plane-XY goes throught the coordination origin.

	*/
	
	vector<string>			symbolNames;		//The Names of the Symbols we derive from our previous symbol
	/*
	when the rule is component-split:
	1) please give result with symbolNames vector in such order ( buttomside, topside, sideface1, sideface2, ... sidefaceN)
	2) namethe sidefaces in a anti-clockwise start with plane-XY goes throught the coordination origin.
	*/
	float					prob;				//The probablity of taking such fucntion
	GNode();
	GNode(string,string,int);
};

//please do not write below this comment, thanks
#endif