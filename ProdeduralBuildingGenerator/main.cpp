#include "integration.h"
#include "Parsing.h"
#include "Modeling.h"
#include "Visualization.h"


int main(int argc, char **argv)
{
	
	parsing();
	modeling();
	//visualization(argc, argv);
	testENV();

	return 0;
}