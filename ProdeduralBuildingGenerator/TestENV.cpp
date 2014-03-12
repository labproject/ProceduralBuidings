#include "testENV.h"
#include "Symbol.h"
#include "GNode.h"
#include <map>
#include <iostream>
#include <vector>
#include <string>


void testENV()
{
	
	/*
	here are some teslines. 
	You can see how the Shapes 
	and Scopes can be created 
	and how rules can be applied
	*/
	
	vector<double> sVec;
	sVec.push_back(1);
	sVec.push_back(1);
	sVec.push_back(1);
	
	cout<<"-----------------------"<<endl<<"Start Test Sequence"<<endl<<"-----------------------"<<endl<<endl;
	//SYMBOL CREATION
	cout<<"SYMBOL CLASS TEST"<<endl;
	
	cout<<"Create:		Symbol a"<<endl;
	Symbol *a = new Symbol(sVec,sVec,"test");
	cout<<"Scale:		Symbol a"<<endl;
	a->S(1,1,3);
	cout<<"Translate:	Symbol a"<<endl;
	a->T(1,2,3);
	//a->subDiv(...)
	//a->repeat(...)
	//...

	/*
	CHECK RETURNING SYMBOL IN A VECTOR<SYMBOL> OUT OF A MEMBERFUNCTION OF SYMBOL
	*/

	

	
	a->T(2,3,0.4);
	vector<Symbol> testVec = a->test();
	string out =testVec.at(0).getName();
	cout<<out<<endl;
	cout<<endl;
	




	/*
	Here are some testlines 
	for the Grammar Objects
	*/
	vector<string>parameters;
	parameters.push_back("0.5");
	parameters.push_back("1r");
	parameters.push_back("0.2");
	
	cout<<endl<<"GRAMMAR CLASS TEST"<<endl;	
	//GRAMMAROBJECT CREATION
	cout<<"Create:		GNode g"<<endl;
	GNode *g = new GNode("a","b",3);
	cout<<"Set:		parameters of g"<<endl;
	g->parameters=parameters;

	cout<<endl;


	cout<<endl<<"MAP TEST"<<endl;	
	cout<<"Create:		map<string,GNode> m"<<endl;
	//map<string,GNode> m;
	//insert into m: map.insert("string",g).. to be checked again how it works.
	

	cout<<endl<<"GIT TEST"<<endl;	
	cout<<"hoffentlich klappt das"<<endl;	
	cout << "aenderung 1" << endl;


	GNode query;
	query.function = "subDiv";
	cout<<query.function<<endl;

	if(query.function == "subDiv"){
		//a->subDiv();
	}
	else if (query.function == "repeat"){
		//a->repeat();
	}

	cout<<endl<<endl<<"-----------------------"<<endl<<"End Test Sequence"<<endl<<"-----------------------"<<endl<<endl<<endl;	
};