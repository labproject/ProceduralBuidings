#include "Parsing.h"


int globalCount=0;
static map<string,float> config;
static map<string,vector<GNode>> ruleSet;


/*
=======================================================================================================================
PARSING MAIN FUNCTION. READ config.txt and office_/simple_building.txt, SEPERATE EACH LINE AND SEND IT TO split(string)
=======================================================================================================================
*/
map<string,vector<GNode>> parsing()
{
	cout<<"-----------------------"<<endl<<"PARSING"<<endl<<"-----------------------"<<endl<<endl<<endl;
	
	//Read Config File and save parameters to map<string,float>config;
	string cLine;
	ifstream cStream;
	cStream.open("config.txt");
	while(!cStream.eof()){
		while(getline(cStream,cLine)){
		readConfig(cLine);
		}
		cStream.close();
		break;
	}

	//Read Rule Set Line by Line
	string line;
	ifstream infile;			
	infile.open("Office Building.txt");         
	while(!infile.eof()){
		while(getline(infile,line)){			//post Line in line
			split(line);						//Splint Line into Commands
		}
		infile.close();
		break;
	}

	return ruleSet;
}

/*
=============================================================================
READ CONFIG FILE AND WRITE GLOBAL VARIABLES INTO MAP map<string,float> config
=============================================================================
*/
void readConfig(string str)
{
	if(str.find("//")!=-1)return; //exit if commented Line is found
	
	int pos = str.find("=");
	string ID = str.substr(0,pos);
	str.erase(0,pos+1);
	//convert string to float
	string num = str;
	float val = (float)atof(num.c_str());
	//Save in Global congig map<string,float>
	config.insert(pair<string,float>(ID,val));
}


/*
=======================================================================================================
SPLIT sting (EACH LINE) INTO ITS COMPONENTS: STRINGS: ID,FUNCTION,PARAMETERS,SYMBOL IDs and PROBABILITY
=======================================================================================================
*/
void split(string str)
{
	
	if (str.find("//")!=str.npos)return;
	else if(str=="")return;
	
	string ID ="";						//ID of Symbol that rules are applied to
	vector<string> function;
	vector<string> parameters;
	vector<string> SymbolIDs;
	vector<string> probability;
	int pos = 0;
	int end = 0;
	
	//SEGMENT LINE INTO ITS COMPONENTS ID, FUNCTION, PARAMETERS and SYMBOLIDs
	while(str!="")
{	

		//extract SymbolID
		pos = str.find("->");
		ID += str.substr(0, pos);
		str.erase(0, pos + 2);

		//extract function name	
		pos = str.find("(");			
		function.push_back(str.substr(0, pos));
		str.erase(0, pos+1);
		
		//extract Parameters
		pos = str.find(")");
		parameters.push_back(str.substr(0,pos));
		str.erase(0,pos+2);

		//extract NewIDs
		pos = str.find("}");
		SymbolIDs.push_back(str.substr(0,pos));
		str.erase(0,pos+1);
	
		//extract Probability
		end = str.find("->");
		pos = str.find(":");
		if(pos!=str.npos){
			probability.push_back(str.substr(pos+1,end-1));
			str.erase(0,end);
		}else{
			probability.push_back("None");
			str.erase(0,end);
		}
	}
	//PRINT RULE BLOCK STRINGS
	cout<<endl<<"RuleNr.: "<<++globalCount<<endl;
	for (unsigned int i=0;i<function.size();i++){
		cout<<"ID:			"<<ID<<endl;
		cout <<"Function:		"<<function.at(i)<<endl;
		cout<<"Parameter:		"<<parameters.at(i)<<endl;
		cout<<"SymbolID:		"<<SymbolIDs.at(i)<<endl;
		cout<<"Probability:		"<<probability.at(i)<<endl;
		cout<<"-----------"<<endl;
		
	}

	//CONVERT STRINGS AND FILL PARAMETERS IN GNODE:
	writeGNode(ID,function,parameters,SymbolIDs,probability);

	/*	
	cout<<"-----------"<<endl;
	cout<<"-----------"<<endl<<endl;
	*/
	
	
}
/*
====================================
WRITE CONVERTED PARAMETERS IN GNODE:
====================================
*/
void writeGNode(string ID,vector<string> fnct ,vector<string>param,vector<string>symb,vector<string>prob)
{
	/*
	Remeber the structure: map<ID,vector<GNode>>!! 

	this function receives the functions, parameters, SymbolIDs and Probabilities as strings.
	Those strings need to be processed:
	@Functions:
	Each entry in vector<string> fnct holds the name of the function that is used!
	@Parameters: 
	Each entry in vector<string>param holds ONE string of ALL parameters for a function.
	The parameters need to be split up using @function: proceedPARAM().
	@Symbols:
	Similar to the parameters the Symbols are stored in a STRING
	The Symbols need to be split up and saved using @function: proceedSYMBID()
	@Probability:
	The Probability of a function comes in as string. 
	It needs to be converted using @function: proceedPROB()

	The whole SET above can be applied multiple times to a single ID,
	We store a vector of GNodes containing the above functions, parameters, Symbolsnames and probabilities.
	This is why we need to go through each vector (they all have the same lenght)...
	*/
	for(unsigned int i=0;i<fnct.size();i++){
		GNode node; 
		node.function = fnct.at(i);
		vector<pair<float,float>>iParameter = proceedPARAM(param.at(i));
		vector<string>iSymbol = proceedSYMBID(symb.at(i));
		float probability = proceedPROB(prob.at(i));
		//
		node.parameters=iParameter;
		node.symbolNames=iSymbol;
		node.prob=probability;
		vector<GNode> vec;
		vec.push_back(node);
		
		}
	}

/*
===========================================================
CONVERT string OF PARAMETERS INTO vector<pair<float,float>>
===========================================================
*/
vector<pair<float,float>>proceedPARAM(string str)
{
	vector<string> params;
	string tmp;
	string res;

	//SEGMENT STRING AND SAVE IT TO VECTOR
	int pos =0;
	while(pos!=-1){
		pos = str.find(",");
		tmp = str.substr(0,pos);
		params.push_back(tmp);
		str.erase(0,pos+1);
		res+="(";
		res+=tmp;
		res+=")";
	}
	//cout<<res<<endl;		//PRINT

	//CONVERT STRING IN VECTOR<PAIR<FLOAT,FLOAT>>
	vector<pair<float,float>> vec;
	
	string par;
	string sub;
	int mult;
	int rel;
	float relVal;

	float first;
	float second;
	
	//FOR EACH PARAMETER
	for(vector<string>::iterator it = params.begin();it!=params.end();it++){
		par = *it;
		mult = par.find("*");
		rel  = par.find("r");
		sub = par.substr(0,rel);
		relVal = (float)atof(sub.c_str());
		map<string,float>::iterator confIT= config.find(par);
		
		//CONTENT QUERY

		if(par =="X"||par =="Y"||par =="Z"){
			//QUERY IF DIMENSION
			cout<<"DIMENSION:	";
			if(par=="X")first= 1;
			if(par=="Y")first= 2;
			if(par=="Z")first= 3;
			
			second = 0;
			
		}else if(confIT!=config.end()){
			//QUERY IF GLOBAL VARIABLE IS FOUND
			cout<<"GLOBALVALUE:	";
			first = config.at(par);			//look up global variable and save it in first
			second = 1;						//set second to 1 because both values are multiplied

		}else if(mult!=-1){
			//QUERY IF MULTIPLICATION IS FOUND
			cout<<"MULTIPLY:	";
			string mFirst = par.substr(0,mult);
			string mSecond = par.substr(mult+1,par.npos);
			//CALL FUNCTION THAT DISTINGUISHES BETWEEN GLOBAL VARIABLE, rand() and absolute values
			first = interpret(mFirst); 
			second = interpret(mSecond);

		
		}else if(rel!=-1&&relVal!=0&&rel==par.length()-1){
			//QUERY IF RELATIVE VALUE IS FOUND
			cout<<"RELATIVE:	";
			first = -4;
			second = relVal;

		}else if((float)atof(par.c_str())!=0){
			//QUERY IF ABSOLUTE VALUE IS FOUND
			cout<<"ABSOLUTE:	";
			first = 1;
			second = (float)atof(par.c_str());
		
		}else if(par==""){
			cout<<"EMPTY:		";
			first = -5;
			second = 0;
		}else if (par == "sidefaces"){
			cout<<"SIDEFACES	";
			first = -6;
			second = 0;
		}else{
			first	= -100;
			second	= -100;
			cout<<par<<"					";
			drawRed("ERROR!");cout<<endl;
		}
		vec.push_back(pair<float,float>(first,second));
		cout<<"<"<<first<<">	"<<"<"<<second<<">"<<endl;
		
	}//end for
	cout<<"--------------------------------"<<endl;
	cout<<"# of Parameters: " <<vec.size()<<endl<<endl;
	return vec;
}



/*
================================================
CONVERT string OF SYMBOL IDs INTO vector<string>
================================================
*/
vector<string>proceedSYMBID(string str)
{
	vector<string> Symbols;
	string tmp;
	string res;
	//Segment String
	int pos =0;
	while(pos!=-1){
		pos = str.find("|");
		tmp = str.substr(0,pos);
		Symbols.push_back(tmp);
		str.erase(0,pos+1);
			res+="{";
		res+=tmp;
		res+="}";
	}
	//cout<<res<<endl;			//PRINT
	return Symbols;
}


/*
========================================
CONVERT string OF PROBABILITY INTO float
========================================
*/
float proceedPROB(string str)
{
	
	string num =str;
	float val = (float)atof(num.c_str());
	//cout<<"Pr["<<val<<"]"<<endl<<endl;		//PRINT
	return val;
}
/*
==========================================
IF THERE IS MULTIPLICATION 
THIS FUNCTION INTERPRETS A GIVEN STRING AS
@Params:
-ABSOLUTE VALUE, 
-SCOPE.SX/Y/Z, 
-RANDOM FUNCTION 
-OR GLOBAL VARIABLE
==========================================
*/
float interpret(string par)
{
	
	float result=0;
	int random = par.find("rand[");
	int scope = par.find("Scope.s");
	string tmp1;
	string tmp2;
	float rVal1;
	float rVal2;

	map<string,float>::iterator confIT = config.find(par);
	
	if (confIT!=config.end()) // test if global variable exists in map config.
	{
		//SET RETURN VALUE TO VALUE OF VARIABLE
		result = config.at(par);
	}
	else if(scope!=-1){
		//Check dimension of scope
		if (par.at(scope+7)=='x')return -1;
		if (par.at(scope+7)=='y')return -2;
		if (par.at(scope+7)=='z')return -3;
	}
	else if(random!=-1)
	{
		//IF ARGUMENT CALLS RANDOM FUNCTION:
	
		//VARIABLES
		int sRand = par.find("[");		//start Random position
		int mRand = par.find("-");		//seperator	position
		int eRand = par.find("]");		//end	Random position
		
		//READ STRINGS 
		tmp1 = par.substr(sRand+1,mRand-sRand-1);
		tmp2 = par.substr(mRand+1,eRand-mRand-1);
		//CONVERT STRINGS TO FLOAT
		rVal1= (float)atof(tmp1.c_str()); 
		rVal2= (float)atof(tmp2.c_str());
		//CALL RANDOM FUNCTION IN GLOBAL.CPP
		result = rand(rVal1,rVal2);
		
	}
	else{
		result= (float)atof(par.c_str());
	}
	//RETURN VALUE
	return result;
}