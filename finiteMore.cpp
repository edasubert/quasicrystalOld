#include "generate.h"
#include "geometricObject.h"
#include "betaSet.h"

#include <iostream>

#define _ERROR_

struct division
{
	betaSet a;
	betaSet b;
	std::string word;
	betaSet length;
	
	bool operator<(division const &b) { 
        return word < b.word;
    }
    
    bool operator==(division const &other) { 
        return ( (word == other.word) );
    }
};


int getWord( betaSet c, betaSet d, int n)
{
	
	
	betaSet S,M,L;
	
	betaSet a, b;
	
	
	#ifndef _ERROR_
	std::cout << "Input DONE" << std::endl;
	print( std::cout, c );
	std::cout << std::endl;
	print( std::cout, d );
	std::cout << std::endl;
	#endif
	
	std::list<betaSet> Dx;
	std::list<betaSet> Dy;
	std::list<std::string> W;
	
	std::list<division> D;
	
	// vnitřní mezery
	if ( ( (d-c) <= betaSet::get( 1, 0 ) ) && ( (d-c) > betaSet::get( 4, -1 ) ) )
	{
			
			if ( (d-c) <= betaSet::get( -7, 2 ) )
			{
				
				#ifndef _ERROR_
				std::cout << "big ones" << std::endl;
				#endif
				
				a = d + betaSet::get( -4, 1 );
				b = c + betaSet::get( -11, 3 );
				L.set(-1,4,1);
				M.set(-1,3,1);
				S.set(0,1,1);
			}
			else if ( (d-c) <= betaSet::get( -3, 1 ) )
			{
				
				#ifndef _ERROR_
				std::cout << "medium ones" << std::endl;
				#endif
				
				a = d + betaSet::get( -4, 1 );
				b = c + betaSet::get( -7, 2 );
				L.set(-1,3,1);
				M.set(-1,2,1);
				S.set(0,1,1);
			}
			else
			{
				#ifndef _ERROR_
				std::cout << "small ones" << std::endl;
				#endif
				
				a = d + betaSet::get( -4, 1 );
				b = c + betaSet::get( -3, 1 );
				L.set(-1,2,1);
				S.set(-1,1,1);
				M.set(0,1,1);
			}
	}
	else
	{
		std::cout << "too big or too small window" << std::endl;
		return 0;
	}
	
	division cache;
	cache.a = c;
	cache.b = a;
	cache.word = "S";
	cache.length = S;
	D.push_back(cache);
	
	cache.a = a;
	cache.b = b;
	cache.word = "L";
	cache.length = L;
	D.push_back(cache);
	
	cache.a = b;
	cache.b = d;
	cache.word = "M";
	cache.length = M;
	D.push_back(cache);
	
	#ifndef _ERROR_
	std::cout << "Separators:" << std::endl << "a: ";
	print( std::cout, a );
	std::cout << std::endl << "b: ";
	print( std::cout, b );
	std::cout << std::endl;
	#endif
	
	#ifndef _ERROR_
	std::cout << "D dump" << std::endl;
	for ( std::list<division>::iterator it = D.begin(); it != D.end(); ++it )
	{
		print( std::cout, it->a );
		std::cout << '\t';
		print( std::cout, it->b );
		std::cout << '\t' << it->word << std::endl;
	}
	std::cout << std::endl;
	#endif
	
	betaSet u,v;
	
	
// SEARCH LOOP =========================================================
	for ( int o = 1; o != n; ++o )
	{
		std::list<division> Dnew;
		
		for ( std::list<division>::iterator it = D.begin(); it != D.end(); ++it )
		{
			//if ( it->a == it->b )
				//continue;
			
			u = steppingFunction( c, d, it->a );
			v = steppingFunction( c, d, it->b, true );
			
			#ifndef _ERROR_
			std::cout << "Interval image" << std::endl << "u: ";
			print( std::cout, it->a );
			std::cout << " -> ";
			print( std::cout, u );
			std::cout  << std::endl << "v: ";
			print( std::cout, it->b );
			std::cout << " -> ";
			print( std::cout, v );
			std::cout << std::endl;
			#endif
			
			if ( ( ( a > u) && ( a < v) ) && ( ( b > u) && ( b < v) ) )
			{
				
				#ifndef _ERROR_
				std::cout << "a in [u,v) && b in [u,v) - S,L,M :: " << it->word << std::endl;
				#endif
				cache.a = u;
				cache.b = a;
				cache.word = it->word + "S";
				cache.length = it->length + S;
				Dnew.push_back(cache);
				
				cache.a = a;
				cache.b = b;
				cache.word = it->word + "L";
				cache.length = it->length + L;
				Dnew.push_back(cache);
				
				cache.a = b;
				cache.b = v;
				cache.word = it->word + "M";
				cache.length = it->length + M;
				Dnew.push_back(cache);
			}
			else if ( ( b > u) && ( b < v) )
			{
				#ifndef _ERROR_
				std::cout << "b in [u,v) - L,M :: " << it->word << std::endl;
				#endif
				
				cache.a = u;
				cache.b = b;
				cache.word = it->word + "L";
				cache.length = it->length + L;
				Dnew.push_back(cache);
				
				cache.a = b;
				cache.b = v;
				cache.word = it->word + "M";
				cache.length = it->length + M;
				Dnew.push_back(cache);
				
			}
			else if ( ( a > u) && ( a < v) )
			{
				#ifndef _ERROR_
				std::cout << "a in [u,v) - S,L :: " << it->word << std::endl;
				#endif
				
				cache.a = u;
				cache.b = a;
				cache.word = it->word + "S";
				cache.length = it->length + S;
				Dnew.push_back(cache);
				
				cache.a = a;
				cache.b = v;
				cache.word = it->word + "L";
				cache.length = it->length + L;
				Dnew.push_back(cache);
		
			}
			else if ( v <= a )
			{
				#ifndef _ERROR_
				std::cout << "v <= a - S :: " << it->word << std::endl;
				#endif
				
				cache.a = u;
				cache.b = v;
				cache.word = it->word + "S";
				cache.length = it->length + S;
				Dnew.push_back(cache);
				
			}
			else if ( v <= b )
			{
				#ifndef _ERROR_
				std::cout << "v <= b - L :: " << it->word << std::endl;
				#endif
				
				cache.a = u;
				cache.b = v;
				cache.word = it->word + "L";
				cache.length = it->length + L;
				Dnew.push_back(cache);
				
			}
			else if ( v <= d )
			{
				#ifndef _ERROR_
				std::cout << "v <= d - M :: " << it->word << std::endl;
				#endif
				
				cache.a = u;
				cache.b = v;
				cache.word = it->word + "M";
				cache.length = it->length + M;
				Dnew.push_back(cache);
				
			}
			
		}
		
		D = Dnew;
		D.sort();
	
	}
	
	for ( std::list<division>::iterator it = D.begin(); it != D.end(); ++it )
	{
		std::cout << '\t' << it->word << '\t';
	}
	std::cout << '\t' << d-c << '\t';
	print( std::cout, d-c );
	std::cout << std::endl;
	
	return 1;
}




int main( int argc, char ** argv )
{
	
	betaSet c = betaSet::get(0,0);
	while ( std::cin >> c )
	{
	
		getWord( betaSet::get( 0, 0 ), c, 6 );
		
	}
	
	
	return 0;
}

