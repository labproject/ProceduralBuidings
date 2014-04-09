#include "Global.h"

using namespace std;
float rand(float a, float b)
{
	float result;
	float low = min(a,b);
	float diff = abs(a-b);
	float tmp;

	srand(time(NULL));
	tmp = rand()%10;
	tmp = (tmp/10);
	result = low+tmp*diff;
	return result;
}


void drawRed(string str)
{
		/*
		const WORD colors[] =
			{
			0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
			0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
			};
		WORD   index   = 120;
		*/
	
	HANDLE hstdin  = GetStdHandle( STD_INPUT_HANDLE  );
	HANDLE hstdout = GetStdHandle( STD_OUTPUT_HANDLE );
	
	// Remember how things were when we started
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo( hstdout, &csbi );

	// Tell the user how to stop
	SetConsoleTextAttribute( hstdout, 0x0C );
	std::cout <<str;

	
	// Keep users happy
	SetConsoleTextAttribute( hstdout, csbi.wAttributes );
}