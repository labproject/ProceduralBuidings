#include "Modeling.h"

using namespace std;

float random (float a, float b)
{
    float result;
    float low = min(a,b);
    float diff = abs(a-b);
    float tmp;

    srand(time(NULL));
    tmp = rand()%10;
    tmp = (tmp/10);
    result = low+tmp*diff;
    return result;
}

// 16.03.14_by Ruotong Li
	/*--------------- Algorithms 1 -----------------*/ // turns out not right!! _by Li,Ruotong@19.03.2014
	/* 
	1) get the element from the vector
	2) get the symbol_ID from the vectorelement;
		( by checking if there's the same Symbol_ID shown in the map->first);
	3) go through the tree and mark all the element into a new vector;
		( by doing this implement a function: vector<Symbol> check_element( Vector<Symbol> newcreated_vector ))
	4) apply rules on all the Symbols in this new vector. 
		( by checking if there's the same Symbol_ID shown in the map->first);
	3) apply rules on such a Symbol and get a vector of new element as result;
		a) create a random number corresponding to the probaility of rule function
		b) apply the function with such a probability.
		( by doing this implement a function: vector<Symbol> apply_rule ( Symbol node_parent, Gnode rule );
	4) put the new Symbols we get into the result_vector and nTree.
	5) goto 1)
	*/

// 17.03.2014_by Li,Ruotong
/*--------------- Algorithms 2 -----------------*/ // turns out not right!! _by Li,Ruotong@19.03.2014
/*
1) start from the first Symbol S, 
2) take the ID of Sybmol S and find the corresponding vector<GNode> in the map
3) create a random number and then choose the GNode apply function corresponding to the value of random number
4) appy the function to get a vector<Symbol> new_created.
5) put the new created symbols into nTree.
5) go throught the new_created Sybmols and apply the algorithms recursivly. => go to 2)
*/

// 19.03.2014_ by Li, Ruotong
// ----------------- Algorithms 3 -------------------- // correct version
/*
	!!! now We modified the datastructure as : vector< piar< string Symbol_ID, vecor<GNode> rules >>
	1) take the pair one by one to apply rules on the symbol 
	2) go through the nTree and mark all the symbols with the symbol_ID same as the Symbol, 
		put them into vector<Symbol> temp_Symbol
	3) create a random number and decided which rule to take from the vector<GNode> rules.
	4) apply rule on the symbol by implement the following function
		vector< Symbol > apply_rule ( Symbol temp_Symbol, GNode rule );
	5) put the new created Symbol into the nTree, if there's no new Symbol( apply S, T, rename..) then keep the tree same.
	6) next pair -> 2)

****!!! problems left:
	1) when to check the occlusion
	2) set the boolen variable "visbale" and "active"
*/

// Apply the rules on the parent Symbol node and get a vector of new created Symbols
/*
	1) create a new vector<Symbol> node_child as the return value;
	2) compare the rule -> function with the function name and decide the function we will apply
		"Scale" => void Symbol::S(double x, double y, double z);
		"Trans" => void Symbol::T(double x, double y, double z);
		"Rotate" => not valid at the moment
		"Rename" => 
		"Subdiv" => vector<Symbol>Symbol::subDiv( int d, vector<double>&splits, vector<string> &symbols);	// 0-x, 1-y, 2-z; splits are absolute value
		"Component_split" => vector<Symbol>Symbol::comp( vector<string> symbols);	// s gives us the name of the new Symbol
		"Repeat" => vector<Symbol>Symbol::repeat( int dim, double size, string symbol);	// 0-x, 1-y, 2-z;
		"Occlusion" => 
	3) take the data from GNode and pass the corresponding parameter to the fucnton;
	4) return the new created vector< Symbol > node_child;
*/

vector<Symbol> apply_rule ( Symbol &node_parent, GNode *rule )
{
	// 1) create a new vector<Symbol> node_child as the return value;
	vector<Symbol> node_child;

	// 2) compare the rule -> function with the function name and decide the function we will apply

	// "Scale" => void Symbol::S(double x, double y, double z);

	if ( rule -> function == "scale" )
	{
		vector< double > p;
		for ( vector< pair< float, float > > :: iterator it = rule -> parameters.begin(); it != rule -> parameters.end(); it ++ )
		{
			if ( it -> first == -1 )			// convert the dimention keyword from {-1,-2,-3} to {0,1,2}
				p.push_back ( node_parent.scale[0] * ( it -> second ) );
			else if ( it -> first == -2 )
				p.push_back ( node_parent.scale[1] * ( it -> second ) );
			else if ( it -> first == -3 )
				p.push_back ( node_parent.scale[2] * ( it -> second ) );
			else
				p.push_back ( ( it -> first ) * ( it -> second ) );
		}
		node_parent.S ( p[0], p[1], p[2]);
	} // no return value

	// "Trans" => void Symbol::T(double x, double y, double z);
	else if ( rule -> function == "trans" )
	{
		vector< double > p;
		for ( vector< pair< float, float > > :: iterator it = rule -> parameters.begin(); it != rule -> parameters.end(); it ++ )
		{
			if ( it -> first == -1 )			// convert the dimention keyword from {-1,-2,-3} to {0,1,2}
				p.push_back ( node_parent.scale[0] * ( it -> second ) );
			else if ( it -> first == -2 )
				p.push_back ( node_parent.scale[1] * ( it -> second ) );
			else if ( it -> first == -3 )
				p.push_back ( node_parent.scale[2] * ( it -> second ) );
			else
				p.push_back ( ( it -> first ) * ( it -> second ) );
		}
		node_parent.T ( p[0], p[1], p[2]);
	}	// no return value

	//	"Rotate" => not valid at the moment

	//	"Rename" => rename ( string symbolName ); // if name = "epsilon", then active = 0; else change the name
	else if ( rule -> function == "rename" )
	{
		node_parent.rename ( rule -> symbolNames[0] );
	}

	//	"Subdiv" => vector<Symbol>Symbol::subDiv( int d, vector<double>&splits, vector<string> &symbols);	// 0-x, 1-y, 2-z; splits are absolute value
	else if ( rule -> function == "subDiv" )
	{
		vector< pair< float, float > > :: iterator it = rule -> parameters.begin();
		int d;					// parameter shows the cordinate we Subdiv along
		d = ( it -> first ) * ( -1 ) - 1; // convert the dimention keyword from {-1,-2,-3} to {0,1,2}
		
		vector<double> splits;	// absolute value of the splits part.
		int r_count =0;			// count of the relative value
		int i = 0;				// index of the relative value
		vector<int> idx;		// list of index for the relative values
		double sum_absolute = 0;
		
		it ++;
		while ( it != rule -> parameters.end() )
		{
			if ( it -> first == -1 )		
			{
				splits.push_back ( node_parent.scale[0] * ( it -> second ) );
				sum_absolute += *splits.end();
			}
			else if ( it -> first == -2 )
			{
				splits.push_back ( node_parent.scale[1] * ( it -> second ) );
				sum_absolute += *splits.end();
			}
			else if ( it -> first == -3 )
			{
				splits.push_back ( node_parent.scale[2] * ( it -> second ) );
				sum_absolute += *splits.end();
			}
			else if ( it -> first == -4 )
			{
				splits.push_back ( it -> second );
				r_count += it -> second;
				idx.push_back ( i );
			}
			else
			{
				splits.push_back ( ( it -> first ) * ( it -> second ) );
				sum_absolute += *splits.end();
			}
			i ++;
		}
		double r = ( node_parent.scale[d] - sum_absolute ) / r_count;
		for ( int it = 0; it < idx.size(); it ++)
			splits [ idx[i] ] *= r;

		node_child = node_parent.subDiv ( d, splits, rule -> symbolNames );
	}

	//	"Component_split" => vector<Symbol>Symbol::comp( vector<string> symbols);	// s gives us the name of the new Symbol
	else if ( rule -> function == "comp" )
	{
		node_child = node_parent.comp ( rule -> symbolNames );
	}
	
	//	"Repeat" => vector<Symbol>Symbol::repeat( int dim, double size, string symbol);	// 0-x, 1-y, 2-z;
	else if ( rule -> function == "repeat" )
	{
		// take the parameters and symbol_IDs of the result
		vector< pair< float, float > > :: iterator it = rule -> parameters.begin();
		int d = ( it -> first ) * ( -1 ) - 1; // convert the dimention keyword from {-1,-2,-3} to {0,1,2}
		
		double size;
		if ( it -> first == -1 )			// convert the dimention keyword from {-1,-2,-3} to {0,1,2}
			size = node_parent.scale[0] * ( it -> second );
		else if ( it -> first == -2 )
			size = node_parent.scale[1] * ( it -> second );
		else if ( it -> first == -3 )
			size = ( node_parent.scale[2] * ( it -> second ));
		else
			size = ( it -> first ) * ( it -> second );
		
		string name = rule -> symbolNames [0];	// convert symbol name

		// pass parameter to the Symbol functions
		node_child = node_parent.repeat ( d, size, name );
	}

	//	"Occlusion" => 

	return node_child;
}

tree <Symbol> modeling ( vector< pair < string, vector<GNode>> > grammar )
	// Symbol S is the first symbol we start our modelling.
	//  map< string symbol_ID, vector<Gnode> rule_set > is the datastructure got from Parsing =======> is no longer used! _by Li,Ruotong @ 19.03.2014
	// !!!@19.03.2014 New datastructure: vector< pair < string symbol_ID, vector<Gnode> rule_set> >
{
	cout<<"-----------------------"<<endl<<"MODELING"<<endl<<"-----------------------"<<endl<<endl<<endl;

	/*
	!!! now We modified the datastructure as : vector< piar< string Symbol_ID, vecor<GNode> rules >>
	*/
	//stlplus::ntree<Symbol> derivTree;----------- we use tree instead of ntree

	tree<Symbol> derivTree;			// create the tree
	tree<Symbol>::iterator top;		// the root iterator

	// initialize the start symbol S
	double start_para[6] = {0.0, 0.0, 0.0, 1.0, 1.0, 1.0};  
	vector< double > start_p( start_para, start_para + 3);
	vector< double > start_s( start_para+4, start_para + 6);
	Symbol S( start_p, start_s, "start");		// initialize the start symbol 

	derivTree.insert(top, S);		// push S into the tree as initialize

	// 1) take the pair one by one to apply rules on the symbol 
	for ( vector< pair < string, vector<GNode>> > :: iterator g_it = grammar.begin(); g_it != grammar.end(); g_it ++ )
	{
		vector<Symbol> child_Symbol;

		// 2) go through the nTree and mark all the symbols with the symbol_ID same as the Symbol, put them into vector<Symbol> temp_Symbol
		vector< tree<Symbol> :: iterator > temp_Symbol;		
		for ( tree<Symbol> :: iterator it = derivTree.begin(); it != derivTree.end(); it ++)
		{
			if ( it -> name == g_it -> first )
				temp_Symbol.push_back( it );
			else
				continue;
		}
		
		//3) for each Symbol in the temp_Symbol, create a random number and decided which rule to take from the vector<GNode> rules.
		vector<GNode>::iterator temp_GNode = g_it -> second.begin();
		for ( vector< tree<Symbol> :: iterator > :: iterator it = temp_Symbol.begin(); it != temp_Symbol.end(); it++) 
			// "it" is the iterator of the temp_Symbol which is a vector of the Symbols we need to apply rules.
		{
			float rand = random( 0.0, 1.0 );
			double probability = 0.0;

			while ( rand <= probability ) 
			{
				probability += temp_GNode -> prob;
				temp_GNode ++;
			}
			//4) apply rule on the symbol by implement the function: vector< Symbol > apply_rule ( Symbol temp_Symbol, GNode rule );
			GNode G = *temp_GNode;					// G denote the temp rule we want apply on the Symbol S
			tree< Symbol >::iterator p_it = *it;	// S_p_it denote the loation of the tree parent
			//Symbol temp_parent = *p_it;			
			
			child_Symbol = apply_rule ( *p_it, &G );	// child_Symbol is the result for each parent node.
	
			//5) put the new created Symbol into the nTree, if there's no new Symbol( apply S, T, rename..) then keep the tree same.
			for ( vector<Symbol> :: iterator c_it = child_Symbol.begin(); c_it != child_Symbol.end(); c_it ++)
			{
				derivTree.append_child ( p_it, *c_it );
			}

		}		
	}

	return derivTree;
}

/* ================= code names from Naurin:
if(funcName == "Subdiv"){
				processSubdivParams(parameters, gnode);			
			}else if(funcName == "Repeat"){
				processRepeatParams(parameters, gnode);	
			}else if(funcName == "Rotate"){
				processRotateParams(parameters, gnode);	
			}else if(funcName == "Component_split"){
				processComponentSplitParams(parameters, gnode);	
			}else if(funcName == "S"){
				processSParams(parameters, gnode);	
			}else if(funcName == "Scale"){
				processScaleParams(parameters, gnode);	
			}else{
				cout << "INVALID FUNCTION " << endl;
			}
*/

// ========== the following is to test the symbol.cpp
/*
void test_symbol()
{
	vector<double> p(3, 0);
	vecotr<double> s(3, 1);
	Symbol lyc( p, s, "Test_symbol LI");

	lyc.S ( 2.0, 2.0, 0.5);	// test scale function
	lyc.T ( 1.0, 2.0, 4.0);	// test translation function

	vector<strings> s;
	s.push_back( "Buttom" );
	s.push_back( "Top" );
	s.push_back( "Side 1");
	s.push_back( "Side 2");
	s.push_back( "Side 3");
	s.push_back( "Side 4");
	vector<Symbol> lyc_compResult;
	lyc_compResult = lyc.comp( s); // test component split

	vector< double > sub_test;
	sub_test.push_back(0.8);
	sub_test.push_back(1.2);
	vector< double > sub_test2;
	sub_test2.push_back( "F1");
	sub_test2.push_back("F2");
	vector<Symbol> lyc_subDivResult;
	lyc_subDivResult = lyc_compResult[3].subDiv(0, sub_test, sub_test2 ); // test subdiv

	vector<Symbol> lyc_repeatResult;
	lyc_repeatResult[0].repeat( 2, 0.5, "P");
}
*/