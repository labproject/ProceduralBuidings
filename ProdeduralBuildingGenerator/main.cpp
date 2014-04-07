#include "integration.h"
#include "Parsing.h"
#include "Modeling.h"
#include "Visualization.h"


int main(int argc, char **argv)
{
	//testENV();
	Symbol start;
	vector< pair < string, vector<GNode>> > parse = parsing();
	modeling( parse);
	//visualization(argc, argv);
	

	return 0;
}