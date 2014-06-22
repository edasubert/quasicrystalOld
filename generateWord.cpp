#include "generate.h"
#include "geometricObject.h"
#include "betaSet.h"

#include <iostream>

int main( int argc, char ** argv )
{
	betaSet c, d;
	betaSet x, y;
	
	std::cin >> c >> d;
	std::cin >> x >> y;
	std::cin >> x >> y;
	
	y = x + y;
	
	char mark = ' ';
	
	
	betaSet a = c.star();
	
	betaSet old;
	
	while (a < x)
	{
		old = a;
		a = iterateBeta( c, d, a, mark );
	}
	
	std::list<betaSet> quasicrystal;
	
	while (a < y )
	{
		a = iterateBeta( c, d, a, mark );
		std::cout << mark;
	}
}
