#include "Parsing.h"
#include <map>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <fstream>
#include "GNode.h"

using namespace std;
string delimiter = "->";		// delimiter for separating multiple rules of a symbol

//vector<map<string, vector<GNode> > >data;        //.. This is our Global DATASTRUCTURE (vector of map elements)
vector<pair<string,vector<GNode> > > ruleSet;		// New data structure, using vector instead of map as per new requirements


bool is_number(string s){
  return !s.empty() && ( s.find_first_not_of("+-0123456789") == string::npos);
}

/*
eg:	subdiv ( "Z", scope.sz * rand(0.3,0.5), 2r, 3*window_width, 0.8 ) {...}
parameters = < < 3, 4 >, < 3, result_of_rand_fuction>, < -1, 2>, < window_width, 3>, < 0, 0.8 > >
1) in the pair, the two float value represent one parameter.
2) first pair shows the dimention axis: 1 = X, 2 = Y, 3 = Z, ane divided into "4" part. 
3) other pairs followed by the first one shows the subdivided length.
4) when there's random function appears in the parameter, calculate the result first and then store it.
5) when there's relative values eg.1r, set the first parameter in the pair -1 and second as the parameter of r
6) when there's a value which is happen to be a variable, then set the first parameter 
   in the pair as the variable, and second as the number multiplied by the variable.
7) when there's a absolute value, then set the fist number in the pair"0" and second as the absolute value.
   on gerneral, the first pair shows the axis and the number of results(here we subdivided the symbole 
   long z-axis into 4 prats). and the following pairs hows a "keyword" represented by number and a number. the "keywords" 
*/
void processSubdivParams(string parameters, GNode* gnode){
	

}

/*
eg. component-split ( "sidefaces" )
1) parameter will be an empty vector, since once the symbol is given, there's only one way to split.
2) please give result with symbolNames vector in such order ( buttomside, topside, sideface1, sideface2, ... sidefaceN)
3) namethe sidefaces in a anti-clockwise start with plane-XY goes throught the coordination origin.
*/
void processComponentSplitParams(string parameters, GNode* gnode){
	vector<pair< float , float> > params;
	gnode->parameters = params;
	
}


/*
eg. scale ( 1r, building_height, 0.9*r)	//also the function of rotate and translate are the same.
parameter = < < -1, 1>, < building_height, 1>, < -1, 0.9> >
1) almost the same as the "subdiv", 
2) the only thing different is we don't need to store the "axis" and numbers of divided parts.
*/
void processScaleParams(string parameters, GNode* gnode){
	
}
void processRotateParams(string parameters, GNode* gnode){
	
}


/*
	eg. repeat ("X", 2 )
	parameter = < <1,0> , < 0, 2>>
	1) first pair shows the axis
	2) the second pair shows the value, obey the same rule as "subdiv" parameters
*/
void processRepeatParams(string parameters, GNode* gnode){
	size_t pos = parameters.find(",");
	pair<float, float> firstPair ;
	pair<float, float> secondPair ;				
	// axis param
	string param = parameters.substr(0, pos);
	parameters.erase(0, pos + 1);
	if(param=="X")
		firstPair = make_pair(1,0);
	else if(param=="Y")
		firstPair = make_pair(2,0); 
	else
		firstPair = make_pair(3,0);

	// value param
	if(is_number(parameters)) { //starts with a number, so not a variable
		if((pos = parameters.find("r"))>=parameters.length()) { // relative position
			secondPair = make_pair(-1, atof(parameters.substr(0,pos).c_str()));
		}else{
			secondPair = make_pair(0, atof(parameters.c_str()));
		}
	}else{ // variable name
		
	}
	
	gnode->parameters.insert(gnode->parameters.end(), firstPair);
	gnode->parameters.insert(gnode->parameters.end(), secondPair);
		
}




void processSParams(string parameters, GNode* gnode){

}

void processParameters(string parameters, string funcName, GNode* gnode){
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
			
}

GNode createGNode(string rule){

	//create GNode for this rule and add it to the gnodes list for this symbol
	GNode gnode  ;
	size_t pos = 0;
	size_t pos2 = 0;

	//extract function name
	pos = rule.find("(");			
	string funcName = rule.substr(0, pos);
	cout << "Function Name: ";
	cout << funcName << endl;
	rule.erase(0, pos + 1);
	gnode.function = funcName;


	//extract function parameter list
	string parameters;
	if(rule.find("{") > rule.length() ) {// no symbol list {}
		pos = rule.find_last_of(")");
		parameters = rule.substr(0, pos);
		rule.erase(0, pos + 1);
	}else{
		pos = rule.find("{");  
		parameters = rule.substr(0, pos-1);
		rule.erase(0, pos); 
	}			
	cout << "Parameters: ";
	cout << parameters << endl;

	//extract symbolNames list 
	pos = rule.find("{");
	pos2 = rule.find_last_of("}");		
	string symbolNames = rule.substr(pos+1, pos2-1);
	cout << "Symbol Names: ";
	cout << symbolNames << endl;
	//rule.erase(0, pos + 1);
	//gnode.function = funcName;
	
	//process parameters
	processParameters(parameters, funcName, &gnode);

	return gnode;				
}

void fillDataStructure(string str)    //call this function to fill the DataStructure one by one with each rule that is read..
{
	string symbolName; // this will be the map key, for each symbol there could be multiple rules, each rule is separated by '->' string 
	size_t pos = 0;
	string rule;

	//extract symbolName
	pos = str.find(delimiter);
	symbolName = str.substr(0, pos);
	str.erase(0, pos + delimiter.length());			
		
	//insert rules corresponding to this symbol in the datastructure
	cout << "\n========Symbol: ";
	cout << symbolName ;
	cout << "=============" << endl;
	vector<GNode> gnodes;
	while ((pos = str.find(delimiter)) != string::npos) {
		rule = str.substr(0, pos);
		cout << "\nRULE: ";
		cout << rule << endl;
		str.erase(0, pos + delimiter.length());
		
		GNode gnode = createGNode(rule);		
		
		gnodes.insert(gnodes.end(), gnode);
	}
	//process last token
	cout << "\nRULE: ";
	cout << str << endl;
	GNode gnode = createGNode(str);				
	gnodes.insert(gnodes.end(), gnode);

	//create an Entry in datastructure of this symbolName
	//map<string, vector<GNode> >  symbolRules;	//removing old data structure	
	pair<string, vector<GNode> > symbolRules;	//using new data structure, pair instead of map
	//symbolRules[symbolName] = gnodes;	
	symbolRules = make_pair(symbolName, gnodes);       
	//data.insert(data.end(), symbolRules);     //removing old data structure
	ruleSet.insert(ruleSet.end(), symbolRules); //using new data structure

}

void doParsing(){
	// read Rules_new.txt
	string STRING;
	ifstream infile;
	infile.open("Rules_new.txt");         //place in the working directory
	
	while(!infile.eof())             // To get you all the lines.
	{
		 while(getline(infile,STRING)) //saves lines in STRING
		 {
		 fillDataStructure(STRING);   // Fill the dataStructure
		 }
		 infile.close();
		 //return 0;
	}
	//print data structure values... .. (NOT using MAPS anymore)
	//for(int i=0; i < data.size(); i++){
	  // map<string, vector<GNode> > symbolRules = data[i];
	   // show content:
	   //TODO : 
	   //for (map<string,vector<GNode> >::iterator it=symbolRules.begin(); it!=symbolRules.end(); ++it)
	     //   cout << it->first ;
	  //}

}

vector<pair<string,vector<GNode> > > parsing()
{
	cout<<"-----------------------"<<endl<<"PARSING"<<endl<<"-----------------------"<<endl<<endl<<endl;

	// Added my code here, to use the already defined "ruleSet" variable to output the Data
	doParsing();
	
	return ruleSet;
}

//int main(int argc, char **argv)
//{
//	//testENV();
//	//Symbol start;
//	vector< pair < string, vector<GNode> > > parse = parsing();
//	//modeling(start,parse);
//	//visualization(argc, argv);
//	
//
//	return 0;
//}

