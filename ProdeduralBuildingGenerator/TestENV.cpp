#include "mainHeader.h"
#include <map>


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
	
	cout<<"-----------------------"<<endl<<"Start Test Sequence"<<endl<<"-----------------------"<<endl<<endl<<endl;
	//SYMBOL CREATION
	cout<<"Create:		Symbol a"<<endl;
	Symbol *a = new Symbol(sVec,sVec,"test");
	cout<<"Scale:		Symbol a"<<endl;
	a->S(1,1,3);
	cout<<"Translate:	Symbol a"<<endl;
	a->T(1,2,3);
	//a->subDiv(...)
	//a->repeat(...)
	//...


	cout<<endl;
	
	/*
	Here are some testlines 
	for the Grammar Objects
	*/
	vector<string>parameters;
	parameters.push_back("0.5");
	parameters.push_back("1r");
	parameters.push_back("0.2");
	
	//GRAMMAROBJECT CREATION
	cout<<"Create:		GNode g"<<endl;
	GNode *g = new GNode("a","b",3);
	cout<<"Set:		parameters of g"<<endl;
	g->parameters=parameters;

	cout<<endl;

	cout<<"Create:		map<string,GNode> m"<<endl;
	//map<string,GNode> m;
	//insert into m: map.insert("string",g).. to be checked again how it works.
	cout<<"GIT_TEST"<<endl;
	cout<<endl<<endl<<"-----------------------"<<endl<<"End Test Sequence"<<endl<<"-----------------------"<<endl;	

	cout<<"hoffentlich klappt das"<<endl;	
	cout << "aenderung 1" << endl;

	
};