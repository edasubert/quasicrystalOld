#include "generate.h"
#include "geometricObject.h"
#include "betaSet.h"

#include <iostream>

int main( int argc, char ** argv )
{
	betaSet c1, d1, c2, d2;
	betaSet x1, y1, x2, y2;
	
	std::cin >> c1 >> d1;
	std::cin >> c2 >> d2;
	
	std::cin >> x1 >> y1;
	std::cin >> x2 >> y2;
	
	y1 = x1 + y1;
	y2 = x2 + y2;
	
	char mark = ' ';
	
	std::list<betaSet> list1 = quasicrystal1D( c1, d1, x1, y1, c1.star(), &iterateBeta );
	
	std::list<betaSet> list2 = quasicrystal1D( c2, d2, x2, y2, c2.star(), &iterateBeta );
	
	CdeloneSet<betaSet> delone = quasicrystal2D( list1, list2 );
	
	betaSet L1 = letterSpace( c1, d1, 'L' );
	betaSet L2 = letterSpace( c2, d2, 'L' );
	
	if ( L1 < L2 )
	{
		print( std::cout, L2 );
	}
	else
	{
		print( std::cout, L1 );
	}
	std::cout << std::endl;
	
	
	for ( std::list<Cpoint<betaSet> >::iterator it = delone.begin(); it != delone.end(); ++it )
	{
		//std::cout << it->getX();
		print( std::cout, it->getX() );
		std::cout << '\t';
		//std::cout << it->getY();
		print( std::cout, it->getY() );
		std::cout << std::endl;
	}
}
