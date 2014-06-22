#include "betaSet.h"

#include <iostream>

int main( int argc, char ** argv )
{
	int step = 500;
	
	betaSet c, d;
	
	c = betaSet::get(4, -1);
	d = betaSet::get(1, 0);
	
	betaSet STEP = (d-c)/step;
	
	for ( int i = 0; i <= step; ++i )
	{
		print( std::cout, STEP.operator*(i)+c );
		std::cout << std::endl;
	}
}
