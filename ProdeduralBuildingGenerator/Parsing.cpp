#include "Parsing.h"



vector<pair<string,vector<GNode>>> ruleSet;

/*
===================================================
PARSING MAIN FUNCTION: 
READ config.txt AND office_/simple_building.txt, 
SEPERATE EACH LINE AND SEND IT TO 
readConfig() AND split(string)
RESPECTIVELY
===================================================
*/
vector<pair<string,vector<GNode>>> parsing()
{
	cout<<"-----------------------"<<endl<<"PARSING"<<endl<<"-----------------------"<<endl<<endl<<endl;
	
	cout<<"Please choose the grammar you want do read: \n- Office Building\n- Empire State\n- Simple Building"<<endl;
	string grammar;
	getline(cin,grammar);
	while(1==1){
	if (grammar == "1"||grammar == "Office"||grammar=="office"||grammar=="Office Building"|| grammar == "office building"){
		grammar = "Office Building.txt";
		break;
	}
	else if(grammar =="2"||grammar=="Empire State"||grammar =="empire state"||grammar == "empire"||grammar=="state"){
		grammar= "Empire State.txt";
		break;
	}
	else if(grammar=="3"||grammar=="Simple"||grammar == "simple"||grammar=="Simple Building"||grammar == "simple building"){
		grammar = "Simple Building.txt";
		break;
	}
	else
		cout<< "Please use the following keywords:"<<endl<<endl;
		drawRed("Office Building");
		cout<<endl<<	"	1\n	office\n	Office\n	Office Building\n	office building"<<endl;

		drawRed("Empire State Building");
		cout<<endl<<	"	2\n	empire\n	state\n	empire state\n	Empire State"<<endl;

		drawRed("Simple Building");
		cout<<endl<<	"	3\n	simple\n	Simple\n	Simple Building\n	simple building"<<endl;
		getline(cin,grammar);
	}
	
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
	infile.open(grammar);         
	while(!infile.eof()){
		while(getline(infile,line)){					//post Line in line
			if(line.find("END")!=line.npos){break;}		//Break reading file if END is found
			split(line);								//Splint Line into Commands
		}
		infile.close();
		break;
	}
	//PRINT RULE SET
	for(vector<pair<string,vector<GNode>> >::iterator rule = ruleSet.begin(); rule != ruleSet.end(); rule++){
		drawRed(rule->first+": ");
		for (vector<GNode>::iterator node = rule->second.begin(); node != rule->second.end(); node++){
			cout<<endl<<"  ";
			cout<< node->function<< "  ";
			for(vector<pair<float,float>>::iterator param = node->parameters.begin(); param != node->parameters.end(); param++){
				cout<<"<"<< param->first<<","<<param->second<<">";
			}
			cout<<"{ ";
			for(vector<string>::iterator sym = node->symbolNames.begin(); sym != node->symbolNames.end(); sym++){
				cout<<*sym+" ";
			}
			cout<<"}";
			cout<<" Pr["<<node->prob<<"]";
		}
		cout <<endl<<endl;
	}
	//RETURN RULE SET;
	return ruleSet;
}

/*
===================================================
READ CONFIG FILE AND WRITE GLOBAL VARIABLES INTO A
MAP map<string,float> CALLED config. FROM HERE ALL
GLOBAL VARIABLES CAN BE LOOKED UP.
===================================================
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
===================================================
SPLIT sting (EACH LINE) FROM GRAMMAR FILE INTO ITS
COMPONENTS AS STRINGS:
ID, FUNCTION, PARAMETERS, SYMBOLIDs and PROBABILITY
===================================================
*/
void split(string str)
{
	//RETURN IF COMMENTED OR EMPTY LINES ARE FOUND
	if (str.find("//")!=str.npos)return;
	else if(str=="")return;
	else if(str.find("END")!=str.npos)return;

	
	//DECLARE VARIABLES FOR SEGMENTATION OF THE STRING
	int pos = 0;
	int end = 0;
	
	//DECLARE VARIABLES FOR SEGMENTED STRINGS
	string ID ="";					
	vector<string> function;
	vector<string> parameters;
	vector<string> SymbolIDs;
	vector<string> probability;
	
	
	/*
	===================================================
	THIS PART SEGMENTS EACH LINE INTO ITS COMPONENTS: 
	ID, FUNCTION, PARAMETERS and SYMBOLIDs 
	HEREBY IS IT POSSIBLE THAT ONE LINE CONTAINS MORE 
	THAN ONE RULE. THIS IS WHEN SEVERAL RULES ARE TO BE 
	APPLIED TO THE ONE SYMBOL ID.
	FOR EACH RULE, AN ENTRY IN A vector<string> IS 
	CREATED, THOSE VECTORS ARE PROCESSED LATER IN THEIR
	RESPECIVE FUNCTION proceedFNCT(), proceedSYMB() ETC;
	===================================================
	*/
	while(str!=""){	

		//extract SymbolID
		pos = str.find("->");
		ID += str.substr(0, pos);
		str.erase(0, pos + 2);

		//extract function name(s)	
		pos = str.find("(");			
		function.push_back(proceedFNCT(str.substr(0, pos)));
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

	//SPLIT STRINGS, CONVERT TO FLOAT VALUES AND FILL GNODE:
	writeGNode(ID,function,parameters,SymbolIDs,probability);
		
}
/*
======================================
CONVERT PARAMETERS AND WRITE IN GNODE:
======================================
*/
void writeGNode(string ID,vector<string> fnct ,vector<string>param,vector<string>symb,vector<string>prob)
{
	/*
	Remeber the structure: vector<pair<STRING,vector<GNode>>!! 

	this function receives the FUNCTIONS, PARAMETERS, SYMBOLIDs and PROBABILITIES as vector<strings>.
	Those strings contained in the vectors need to be processed:
	@Functions:
	Each entry in vector<string> fnct holds the name of the function that CAN be used under the ID!
	@Parameters: 
	Each entry in vector<string>param holds ONE string of ALL parameters for ONE function.
	The parameters need to be split up using the method: proceedPARAM().
		@RETURN: A vector of pair<float,float> Coding in the System explained by Ruotong!
	@Symbols:
	Similar to the parameters the Symbols are stored in a STRING
	The Symbols need to be split up and saved using the method: proceedSYMBID()
		@RETURN: A vector of strings -> the new IDs
	@Probability:
	The Probability of a function comes in as string. 
	It needs to be converted using the method: proceedPROB()
		@RETURN: A the string of the probability converted to float



	Each ID can have multiple functions (and therefore also parameters, symbolids and probabilities).
	Such a Set is passed as a level of depth in each vector. 
	the FUNCTION funct.at(3); gets the PARAMETERS params.at(3); that results in the new IDs with the 
	names stored in symb.at(3); with a PROBABILITY prob.at(3);
	Therefore we need to check each vector in its depth. Each of those Level define the Content of 
	one GNODE
	
	Accessing the Parameters etc. Level by Level we need to proceed as indicated above using 
	proceedPARAM();
	proceedSYMBID();
	proceedPROB();
	*/
	vector<GNode> vec;
	for(unsigned int i=0;i<fnct.size();i++){ //Check each LEVEL of Depth in the Vectors
		GNode node; 
		node.function = fnct.at(i);

		vector<pair<float,float>>iParameter = proceedPARAM(param.at(i));
		vector<string>iSymbol = proceedSYMBID(symb.at(i));
		float probability = proceedPROB(prob.at(i));
		
		node.parameters=iParameter;
		node.symbolNames=iSymbol;
		node.prob=probability;
		
		vec.push_back(node);
		
		
		}
	
		ruleSet.push_back(pair<string,vector<GNode>>(ID,vec));
}

/*
===========================================================
CONVERT string OF PARAMETERS INTO vector<pair<float,float>>
===========================================================
*/
vector<pair<float,float>>proceedPARAM(string str)
{
	/*
	VARIABLES:
		The single parameters in the string of parameters are split and saved in
		vector<String> @Params.
		*/
	vector<string> params;
	string tmp;


	//SEGMENT STRING AND SAVE IT TO VECTOR
	int pos =0;
	while(pos!=-1){
		pos = str.find(",");
		tmp = str.substr(0,pos);
		params.push_back(tmp);
		str.erase(0,pos+1);
	}

	/*
	===========================================================
	DECLARE VARIABLES FOR CONVERSION IN pair<float,float>;
	@vec: VECTOR OF PAIRS
		each contains the information that was originally given by the STRING
	@par: PARAMETER FROM ABOVE DECLARED AND DEFINED vector<string>PARAMS
		temporary slot to save parameter strings.
	@sub: TEMPORARY SUB-STRING
		used to save "possible relative values" 
		it is used once the RELATIVE QUERY starts!
	@mult: SAVES THE POSITION WITHIN THE STRING IF "*" IS FOUND
		used to indicate "possible multiplication operations"
		it is used once the MULTIPLICATION QUERY starts!
	@relVal: SAVES THE POSSIBLE RELATIVE VALUE AS FLOAT
		it is used once the RELATUVE QUERY starts
	@First,Second: STORE THE VALUE FOR ENTRIES IN THE pair<first,second>
	===========================================================
	*/

	vector<pair<float,float>> vec;
	string parameterType;
	string par;
	string sub;
	int mult;
	int rel;
	float relVal;

	float first;
	float second;
	
	//FOR EACH PARAMETER IN THE EARLIER SEPERATED vector<string>PARAMS
	for(vector<string>::iterator it = params.begin();it!=params.end();it++){
		par = *it;
		mult = par.find("*");
		rel  = par.find("r");
		sub = par.substr(0,rel);
		relVal = (float)atof(sub.c_str());
		map<string,float>::iterator confIT= config.find(par);
		
		//CONTENT QUERY

		if(par =="X"||par =="Y"||par =="Z"){
			//QUERY DIMENSION
			parameterType="DIMENSION:	";
			if(par=="X")first= -1;
			if(par=="Y")first= -2;
			if(par=="Z")first= -3;
			
			second = 0;
			
		}else if(confIT!=config.end()){					//CHECK IF MAP config RETURNS A VALUE
			//QUERY IF GLOBAL VARIABLE IS FOUND
			parameterType="GLOBALVALUE:	";
			first = 1;						//set second to 1 because both values are multiplied
			second = config.at(par);		//look up global variable and save it as first

		}else if(mult!=-1){								//CHECK IF PARAMETER DESCRIBES MULTIPLICATION
			//QUERY IF MULTIPLICATION IS FOUND
			parameterType="MULTIPLY:	";
			string mFirst = par.substr(0,mult);			//save Parameter BEFORE "*" as string
			string mSecond = par.substr(mult+1,par.npos);//save Parameter AFTER "*" as string

			//CALL FUNCTION THAT DISTINGUISHES BETWEEN globalVariables, ScopeOperations, randomValues and absoluteValues
			first = interpret(mFirst); 
			second = interpret(mSecond);

		}else if(rel!=-1&&relVal!=0&&rel==par.length()-1){	//QUERY IF RELATIVE VALUE IS FOUND
			/*The Line above checks: 
				is Letter "r" found in string?
				is the Rest of the string is a Number ?
				is the found Letter "r" is the LAST letter In the string
			*/
			
			parameterType="RELATIVE:	";
			first = -4;				//CODE FOR RELATIVE VALUES
			second = relVal;		//ACTUAL RELATIVE VALUE (calculated on top!)

		}else if((float)atof(par.c_str())!=0){				//QUERY IF ABSOLUTE VALUE IS FOUND
			/*
			The Line above Checks:
				is the String found a Valid float number?
			*/
			parameterType="ABSOLUTE:	";
			first = 1;
			second = (float)atof(par.c_str());
		
		}else if (par == "sidefaces"){		//QUERY IF A CERTAIN STRING IS GIVEN AS PARAMETER!
			parameterType="SIDEFACES	";
			first = 0;		//TO ASK RUOTONG ABOUT THIS CASE
			second = 0;		//TO ASK RUOTONG ABOUT THIS CASE
		
		}else if(par==""){					//QUERY IF NO PARAMETERS ARE GIVEN
			parameterType="EMPTY:		";
			first = -5;		//TO ASK RUOTONG ABOUT THIS CASE
			second = 0;		//TO ASK RUOTONG ABOUT THIS CASE
		
		
		}else{				//ANY OTHER CASE WILL REPORT AN ERROR!
			parameterType=par+"					";
			//drawRed("ERROR!");cout<<endl;
			first	= 1;
			second	= 0;

		}
		//THE CREATED VALUES first AND second ARE NOW PUSHED TO A VECTOR OF pairs<float,float> CODING THE ACTUAL PARAMETERS
		
		
		vec.push_back(pair<float,float>(first,second));
		
	}//end forLoop


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
	}
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
	if (str=="None")
		return 1;
	float val = (float)atof(num.c_str());
	//cout<<"Pr["<<val<<"]"<<endl<<endl;		//PRINT
	return val;
}


string proceedFNCT(string str)
{
	if (str=="") return "rename";
	else return str;
}


/*
==========================================
NOW WHAT HAPPENS IF THERE IS MULTIPLICATION? 
THE FUNCTION interpret() INTERPRETS A 
GIVEN STRING AS
@Params:
-ABSOLUTE VALUE, 
-SCOPE.SX/Y/Z, 
-RANDOM FUNCTION 
-OR GLOBAL VARIABLE
AND RETURNS THE RIGHT VALUE THAT IS TO BE 
WRITTEN IN THE pair<float,float> FOR 
THE MODELING PART
OTHER POSSIBILITIES AS THE ONES MENTIONED 
ABOVE ARE NOT VALID!!
==========================================
*/
float interpret(string par)
{
	
	float result=-1;
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