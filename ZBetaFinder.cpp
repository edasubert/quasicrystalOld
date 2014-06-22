
#include "betaSet.h"

#include <iostream>

int main( int argc, char ** argv )
{
	betaSet x(0,0);
	betaSet y;
	double t1, t2;
	
	betaSet in1, in2;
	std::cin >> in1;
	std::cin >> in2;
	
	t1 = in1;
	t2 = in2;
	
	
	while ( !( ( t1 < x ) && ( t2 > x ) ) )
	{
		if ( t1 > x )
		{
			x = x + betaSet::get( 1, 0 );
		}
		else
		{
			x = x + betaSet::get( 0, -1 );
		}
		
		//std::cout << t1 << '\t';
		//print( std::cout, x );
		//std::cout << " = " << x;
		//std::cout << '\t' << t2;
		//std::cout << std::endl;
	}
	
	y = x;
	x = betaSet::get(0,0);
	
	while ( !( ( t1 < x ) && ( t2 > x ) ) )
	{
		if ( t1 > x )
		{
			x = x + betaSet::get( 0, 1 );
		}
		else
		{
			x = x + betaSet::get( -1, 0 );
		}
		
		//std::cout << t1 << '\t';
		//print( std::cout, x );
		//std::cout << " = " << x;
		//std::cout << '\t' << t2;
		//std::cout << std::endl;
	}
	
	std::cout << std::endl;
	print( std::cout, y );
	std::cout << " = " << y;
	std::cout << std::endl;
	print( std::cout, x );
	std::cout << " = " << x;
	std::cout << std::endl;
	
}
