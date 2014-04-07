#include "integration.h"
#include "Parsing.h"
#include "Modeling.h"
#include "Visualization.h"
#include "tree.hh"

int main(int argc, char **argv)
{
	//testENV();
	Symbol start;
	vector< pair < string, vector<GNode>> > parse = parsing();
	tree<Symbol> derivTree = modeling( parse);
	visualization(argc, argv,derivTree);
	

	return 0;
}