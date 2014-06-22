#include "generate.h"
#include "geometricObject.h"
#include "betaSet.h"

#include <iostream>

//#define _ERROR_

betaSet steppingFunction( betaSet c, betaSet d, betaSet x, bool limit /*=false*/ ) // limit parametr: returns right limit
{
	if ( ( ( x < c ) || ( x > d ) ) )
	{
		std::cout << "SteppingFunction: out of window" << std::endl;
		
		return betaSet::get(0,0);
	}
	if ( !( ( (d-c) <= betaSet::get( 1, 0 ) ) && ( (d-c) >= betaSet::get( 4, -1 ) ) ) )
	{
		std::cout << "SteppingFunction: too big or too small window" << std::endl;
		return betaSet::get(0,0);
	}
	
	
	if ( ( ( x < d + betaSet::get(-4,1) ) && !limit ) || ( ( x <= d + betaSet::get(-4,1) ) && limit) )
	{
		return (x + betaSet::get(4,-1) );
	}
	
	
	if ( (d-c) <= betaSet::get( -7, 2 ) )
	{
		if ( ( ( x >= ( c + betaSet::get( -11, 3 ) ) ) && !limit ) || ( ( x > ( c + betaSet::get( -11, 3 ) ) ) && limit ) )
			return ( x + betaSet::get(11,-3) );
		else
			return ( x + betaSet::get(15,-4) );
	}
	else if ( (d-c) <= betaSet::get( -3, 1 ) )
	{
		if ( ( ( x >= ( c + betaSet::get( -7, 2 ) ) ) && !limit ) || ( ( x > ( c + betaSet::get( -7, 2 ) ) ) && limit ) )
			return ( x + betaSet::get(7,-2) );
		else
			return ( x + betaSet::get(11,-3) );
	}
	else
	{
		if ( ( ( x >= ( c + betaSet::get( -3, 1 ) ) ) && !limit ) || ( ( x > ( c + betaSet::get( -3, 1 ) ) ) && limit ) )
			return ( x + betaSet::get(3,-1) );
		else
			return ( x + betaSet::get(7,-2) );
	}	
}


betaSet iterateBeta( betaSet c, betaSet d, betaSet x, char &mark )
{
	if ( (d-c) <= betaSet::get( 1, 0 ) )
	{
		if ( (d-c) >= betaSet::get( 4, -1 ) ) // 1/beta
		{
			
			if ( (d-c) <= betaSet::get( -7, 2 ) )
			{
				
				#ifndef _ERROR_
				std::cout << "big ones" << std::endl;
				#endif
				
				if ( x.star() < ( d + betaSet::get( -4, 1 ) ) )
				{
					mark = 'S';
					return (x + betaSet::get(0,1) );
				}
				else if ( x.star() < ( c + betaSet::get( -11, 3 ) ) )
				{
					mark = 'L';
					return (x + betaSet::get(-1,4) );
				}
				else
				{
					mark = 'M';
					return (x + betaSet::get(-1,3) );
				}
			}
			else if ( (d-c) <= betaSet::get( -3, 1 ) )
			{
				
				#ifndef _ERROR_
				std::cout << "medium ones" << std::endl;
				#endif
				
				if ( x.star() < ( d + betaSet::get( -4, 1 ) ) )
				{
					mark = 'S';
					return (x + betaSet::get(0,1) );
				}
				else if ( x.star() < ( c + betaSet::get( -7, 2 ) ) )
				{
					mark = 'L';
					return (x + betaSet::get(-1,3) );
				}
				else
				{
					mark = 'M';
					return (x + betaSet::get(-1,2) );
				}
			}
			else
			{
				#ifndef _ERROR_
				std::cout << "small ones" << std::endl;
				#endif
				
				if ( x.star() < ( d + betaSet::get( -4, 1 ) ) )
				{
					mark = 'M';
					return (x + betaSet::get(0,1) );
				}
				else if ( x.star() < ( c + betaSet::get( -3, 1 ) ) )
				{
					mark = 'L';
					return (x + betaSet::get(-1,2) );
				}
				else
				{
					mark = 'S';
					return (x + betaSet::get(-1,1) );
				}
			}
		}
		else
		{
			std::cout << "too small window" << std::endl;
		}
		
		
	}
	else
	{
		std::cout << "too big window" << std::endl;
	}
}


betaSet letterSpace( betaSet c, betaSet d, char mark )
{
	if ( (d-c) <= betaSet::get( 1, 0 ) )
	{
		if ( (d-c) >= betaSet::get( 4, -1 ) ) // 1/beta
		{
			
			if ( (d-c) <= betaSet::get( -7, 2 ) )
			{
				
				#ifndef _ERROR_
				std::cout << "big ones" << std::endl;
				#endif
				
				if ( mark == 'S' )
				{
					return ( betaSet::get(0,1) );
				}
				else if ( mark == 'L' )
				{
					return ( betaSet::get(-1,4) );
				}
				else
				{
					return ( betaSet::get(-1,3) );
				}
			}
			else if ( (d-c) <= betaSet::get( -3, 1 ) )
			{
				
				#ifndef _ERROR_
				std::cout << "medium ones" << std::endl;
				#endif
				
				if ( mark == 'S' )
				{
					return ( betaSet::get(0,1) );
				}
				else if ( mark == 'L' )
				{
					return ( betaSet::get(-1,3) );
				}
				else
				{
					return ( betaSet::get(-1,2) );
				}
			}
			else
			{
				#ifndef _ERROR_
				std::cout << "small ones" << std::endl;
				#endif
				
				if ( mark == 'M' )
				{
					return ( betaSet::get(0,1) );
				}
				else if ( mark == 'L' )
				{
					return ( betaSet::get(-1,2) );
				}
				else
				{
					return ( betaSet::get(-1,1) );
				}
			}
		}
		else
		{
			std::cout << "too small window" << std::endl;
		}
		
		
	}
	else
	{
		std::cout << "too big window" << std::endl;
	}
}


std::list<betaSet> quasicrystal1D( const betaSet c, const betaSet d, const betaSet x, const betaSet y, const betaSet start, betaSet (*iterate)(betaSet, betaSet, betaSet, char&) )
{
	#ifndef _ERROR_
	std::cout << "Quasicrystal1D" << std::endl;
	#endif
	
	betaSet a = start;
	char mark;
	
	betaSet old;
	
	while (a < x)
	{
		old = a;
		a = iterate( c, d, a, mark );
	}
	
	#ifndef _ERROR_
	std::cout << "inside window" << std::endl;
	#endif
	
	std::list<betaSet> quasicrystal;
	
	while (a < y )
	{
		quasicrystal.push_back( a );
		a = iterate( c, d, a, mark );
		#ifndef _ERROR_
		std::cout << mark;
		#endif
	}
	
	return quasicrystal;
}

CdeloneSet<betaSet> quasicrystal2D( std::list<betaSet> &x, std::list<betaSet> &y )
{
	CdeloneSet<betaSet> delone;
	delone.setDescription("2D quasicrystal parallelogram");
	//delone.setColor( fillColor, strokeColor, strokeWidth );
	
	for ( std::list<betaSet>::iterator it = x.begin(); it != x.end(); ++it )
	{
		for ( std::list<betaSet>::iterator ot = y.begin(); ot != y.end(); ++ot )
		{
			
			delone << transformBeta( Cpoint<betaSet>( *it, *ot ) );
			
		}
	}
	
	return delone;
}

Cpoint<betaSet> transformBeta( const Cpoint<betaSet> &point )
{
	Cpoint<betaSet> Output( point.getX() - (point.getY()*betaSet::get(-2,1))/2, point.getY()/2 );
	
	return Output;
}
