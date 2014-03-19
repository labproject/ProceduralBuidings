
#include "Modeling.h"

// 16.03.14_by Ruotong Li
	/*--------------- Algorithms 1 -----------------*/
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
/*--------------- Algorithms 2 -----------------*/
/*
1) start from the first Symbol S, 
2) take the ID of Sybmol S and find the corresponding vector<GNode> in the map
3) create a random number and then choose the GNode apply function corresponding to the value of random number
4) appy the function to get a vector<Symbol> new_created.
5) put the new created symbols into nTree.
5) go throught the new_created Sybmols and apply the algorithms recursivly. => go to 2)
*/

// Apply the rules on the parent Symbol node and get a vector of new created Symbols
vector<Symbol> apply_rule ( Symbol &node_parent, GNode *rule )
{
	// new a vector of new Symbols
	vector<Symbol> node_child;

	// 
	// the following "names" are from Naurin's code
	if( rule -> function == "Subdiv")
	{

	}

	else if( rule -> function == "Repeat")
	{
				processRepeatParams(parameters, gnode);	
			}
	else if( rule -> function == "Rotate"){
				processRotateParams(parameters, gnode);	
			}
	else if( rule -> function == "Component_split"){
				processComponentSplitParams(parameters, gnode);	
			}
	else if( rule -> function == "S"){
				processSParams(parameters, gnode);	
			}
	else if( rule -> function == "Scale"){
				processScaleParams(parameters, gnode);	
			}
	else{
				cout << "INVALID FUNCTION " << endl;
			}
}

stlplus::ntree<Symbol> modeling ( Symbol &S, map< string symbol_ID, vector<Gnode> rule_set > grammar )
	// Symbol S is the first symbol we start our modelling.
	//  map< string symbol_ID, vector<Gnode> rule_set > is the datastructure got from Parsing
{
	cout<<"-----------------------"<<endl<<"MODELING"<<endl<<"-----------------------"<<endl<<endl<<endl;

	// 1) get the element from the vector
	for ( map< string, vector<Gnode> >::iterator it = grammar.begin() , it != grammar.end(); it ++ )
	{
		// 2) get the symbol_ID from the vectorelement;
		//	( by checking if there's the same Symbol_ID shown in the map->first);

	}
	
	// 3) go through the tree and mark all the element into a new vector;
		( by doing this implement a function: vector<Symbol> check_element( Vector<Symbol> newcreated_vector ))
	// 4) apply rules on all the Symbols in this new vector. 
		( by checking if there's the same Symbol_ID shown in the map->first);
	// 3) apply rules on such a Symbol and get a vector of new element as result;
		a) create a random number corresponding to the probaility of rule function
		b) apply the function with such a probability.
		( by doing this implement a function: vector<Symbol> apply_rule ( Symbol node_parent, Gnode rule );
	// 4) put the new Symbols we get into the result_vector and nTree.
	// 5) goto 1)

	
	stlplus::ntree<Symbol> derivTree;
	return derivTree;
}

/*
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

// the following is to test the symbol.cpp
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