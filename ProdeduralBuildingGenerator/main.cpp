#include "integration.h"
#include "Parsing.h"
#include "Modeling.h"
#include "Visualization.h"
#include "Global.h"

int main(int argc, char **argv)
{
	Symbol start;
	
	vector< pair < string, vector<GNode>> > parse = parsing();
	modeling(start,parse);
	visualization(argc, argv);
	testENV();

	return 0;
}