#include "integration.h"
#include "Parsing.h"
#include "Modeling.h"
#include "Visualization.h"


int main()
{
	testENV();
	parsing();
	modeling();
	visualization();

	return 0;
}