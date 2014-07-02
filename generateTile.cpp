#include "generate.h"
#include "geometricObject.h"
#include "betaSet.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

const int LENGTH = 4;
const int HALF = 2;

struct division
{
	betaSet a;
	betaSet b;
	std::string word;
	betaSet length;
	
	bool operator<(division const &b) { 
        return a < b.a;
    }
    
    bool operator==(division const &other) { 
        return ( (a == other.a) && (b == other.b) );
    }
};

std::list<std::string> generateWord( betaSet c, betaSet d )
{
	betaSet a, b;
	
	betaSet S,M,L;
	
	std::list<betaSet> Dx;
	std::list<betaSet> Dy;
	std::list<std::string> W;
	
	char CA, AB, BD;
	
	std::list<division> D;
	
	// vnitřní mezery
	if ( ( (d-c) <= betaSet::get( 1, 0 ) ) && ( (d-c) >= betaSet::get( 4, -1 ) ) )
	{
			
			if ( (d-c) <= betaSet::get( -7, 2 ) )
			{
							
				a = d + betaSet::get( -4, 1 );
				b = c + betaSet::get( -11, 3 );
				L.set(-1,4,1);
				M.set(-1,3,1);
				S.set(0,1,1);
				
				CA = 'S';
				AB = 'L';
				BD = 'M';
			}
			else if ( (d-c) <= betaSet::get( -3, 1 ) )
			{
				
				a = d + betaSet::get( -4, 1 );
				b = c + betaSet::get( -7, 2 );
				L.set(-1,3,1);
				M.set(-1,2,1);
				S.set(0,1,1);
				
				CA = 'S';
				AB = 'L';
				BD = 'M';
			}
			else
			{
				a = d + betaSet::get( -4, 1 );
				b = c + betaSet::get( -3, 1 );
				L.set(-1,2,1);
				S.set(-1,1,1);
				M.set(0,1,1);
				
				CA = 'M';
				AB = 'L';
				BD = 'S';
			}
	}
	else
	{
		std::cout << "too big or too small window" << std::endl;
		std::exit(0);
	}
	
	division cache;
	cache.a = c;
	cache.b = a;
	cache.word = CA;
	cache.length = S;
	D.push_back(cache);
	
	cache.a = a;
	cache.b = b;
	cache.word = AB;
	cache.length = L;
	D.push_back(cache);
	
	cache.a = b;
	cache.b = d;
	cache.word = BD;
	cache.length = M;
	D.push_back(cache);
	
	betaSet u,v;
	
	
// SEARCH LOOP =========================================================
	for ( int o = 1; o != LENGTH; ++o )
	{
		std::list<division> Dnew;
		
		for ( std::list<division>::iterator it = D.begin(); it != D.end(); ++it )
		{
			if ( it->a == it->b )
				continue;
			
			u = steppingFunction( c, d, it->a );
			v = steppingFunction( c, d, it->b, true );
			
			if ( ( ( a > u) && ( a < v) ) && ( ( b > u) && ( b < v) ) )
			{
				cache.a = u;
				cache.b = a;
				cache.word = it->word + CA;
				cache.length = it->length + S;
				Dnew.push_back(cache);
				
				cache.a = a;
				cache.b = b;
				cache.word = it->word + AB;
				cache.length = it->length + L;
				Dnew.push_back(cache);
				
				cache.a = b;
				cache.b = v;
				cache.word = it->word + BD;
				cache.length = it->length + M;
				Dnew.push_back(cache);
			}
			else if ( ( b > u) && ( b < v) )
			{
				cache.a = u;
				cache.b = b;
				cache.word = it->word + AB;
				cache.length = it->length + L;
				Dnew.push_back(cache);
				
				cache.a = b;
				cache.b = v;
				cache.word = it->word + BD;
				cache.length = it->length + M;
				Dnew.push_back(cache);
				
			}
			else if ( ( a > u) && ( a < v) )
			{
				cache.a = u;
				cache.b = a;
				cache.word = it->word + CA;
				cache.length = it->length + S;
				Dnew.push_back(cache);
				
				cache.a = a;
				cache.b = v;
				cache.word = it->word + AB;
				cache.length = it->length + L;
				Dnew.push_back(cache);
		
			}
			else if ( v <= a )
			{
				cache.a = u;
				cache.b = v;
				cache.word = it->word + CA;
				cache.length = it->length + S;
				Dnew.push_back(cache);
				
			}
			else if ( v <= b )
			{
				cache.a = u;
				cache.b = v;
				cache.word = it->word + AB;
				cache.length = it->length + L;
				Dnew.push_back(cache);
				
			}
			else if ( v <= d )
			{
				cache.a = u;
				cache.b = v;
				cache.word = it->word + BD;
				cache.length = it->length + M;
				Dnew.push_back(cache);
				
			}
			
		}
		
		D = Dnew;
		D.sort();
	
	}
	
	std::list<std::string> output;
	
	for ( std::list<division>::iterator it = D.begin(); it != D.end(); ++it )
	{
		output.push_back( it->word );
	}
	
	return output;
}

CvoronoiCell<betaSet>* generateTile( betaSet c1, betaSet d1, betaSet c2, betaSet d2, std::string word1pre, std::string word1post, std::string word2pre, std::string word2post, std::string fillColor, std::string strokeColor, std::string strokeWidth )
{	
	betaSet a,b;
	
	std::list<betaSet> list1;
	std::list<betaSet> list2;
	
	betaSet last(0,0);
	
	list1.push_front( last );
	for ( std::string::reverse_iterator it = word1pre.rbegin(); it != word1pre.rend(); ++it )
	{
		last-= letterSpace( c1, d1, *it );
		list1.push_front( last );
	}
	last = betaSet::get(0,0);
	for ( std::string::iterator it = word1post.begin(); it != word1post.end(); ++it )
	{
		last+= letterSpace( c1, d1, *it );
		list1.push_back( last );
	}
	
	last = betaSet::get(0,0);
	list2.push_front( last );
	for ( std::string::reverse_iterator it = word2pre.rbegin(); it != word2pre.rend(); ++it )
	{
		last-= letterSpace( c2, d2, *it );
		list2.push_front( last );
	}
	last = betaSet::get(0,0);
	for ( std::string::iterator it = word2post.begin(); it != word2post.end(); ++it )
	{
		last+= letterSpace( c2, d2, *it );
		list2.push_back( last );
	}
	
	CdeloneSet<betaSet> delone = quasicrystal2D( list1, list2 );
	
	
	Cpoint<betaSet> center = transformBeta( Cpoint<betaSet>( betaSet::get(0,0), betaSet::get(0,0) ) );
	center.setColor( fillColor, strokeColor, strokeWidth );
	
	
	betaSet L1 = letterSpace( c1, d1, 'L' );
	betaSet L2 = letterSpace( c2, d2, 'L' );
	betaSet L;
	
	if ( L1 < L2 )
	{
		CvoronoiCell<betaSet>::large = L2;
		L = L2;
	}
	else
	{
		CvoronoiCell<betaSet>::large = L1;
		L = L1;
	}
	
	
	delone.setColor( fillColor, strokeColor, strokeWidth );
	delone.setPackingR();
	delone.setCoveringR(4*L);
	
	
	CvoronoiCell<betaSet> *voronoi = new CvoronoiCell<betaSet>( delone, center );
	voronoi->setColor( fillColor, strokeColor, strokeWidth );
	
	voronoi->setDescription( word1pre + word1post + " - " + word2pre + word2post );
		
	return voronoi;
	
}


void testTiles( betaSet c, betaSet d, std::list<CvoronoiCell<betaSet> > * list, std::string fillColor )
{
	
	std::string strokeColor = "rgb(25,25,25)";
	std::string strokeWidth = "0.01em";
	
	
	betaSet c1, d1;
	betaSet c2, d2;
	
	c1 = c;
	c2 = c;
	d1 = d;
	d2 = d;
	
	std::list<std::string> word1 = generateWord( c1, d1 );
	std::list<std::string> word2 = generateWord( c2, d2 );
	
	CvoronoiCell<betaSet> *voronoi;
	CvoronoiCell<betaSet> *voronoi1R = new CvoronoiCell<betaSet>;
	CvoronoiCell<betaSet> *voronoi2R = new CvoronoiCell<betaSet>;
	CvoronoiCell<betaSet> *voronoi3R = new CvoronoiCell<betaSet>;
	
	bool check = false;
	std::list<int> tileList;
	
	for ( std::list<std::string>::iterator it = word1.begin(); it != word1.end(); ++it )
	{
		for ( std::list<std::string>::iterator ot = word2.begin(); ot != word2.end(); ++ot )
		{
			check = false;
			
			voronoi = generateTile( c1, d1, c2, d2, it->substr(0,HALF), it->substr(HALF,HALF), ot->substr(0,HALF), ot->substr(HALF,HALF), fillColor, strokeColor, strokeWidth);
			voronoi->construct();
			
			*voronoi1R = *voronoi;
			*voronoi2R = *voronoi;
			*voronoi3R = *voronoi;
			
			voronoi1R->Cell->transform( betaSet::get( -2, 1, 2 ), betaSet::get( -1, 0, 2 ), betaSet::get( -1, 0, 2 ), betaSet::get( 2, -1, 2 ) );
			voronoi1R->CarrierSet->transform( betaSet::get( -2, 1, 2 ), betaSet::get( -1, 0, 2 ), betaSet::get( -1, 0, 2 ), betaSet::get( 2, -1, 2 ) );
			voronoi2R->Cell->transform( betaSet::get( 2, -1, 2 ), betaSet::get( 1, 0, 2 ), betaSet::get( 1, 0, 2 ), betaSet::get( -2, 1, 2 ) );
			voronoi2R->CarrierSet->transform( betaSet::get( 2, -1, 2 ), betaSet::get( 1, 0, 2 ), betaSet::get( 1, 0, 2 ), betaSet::get( -2, 1, 2 ) );
			voronoi3R->Cell->transform( betaSet::get( -1, 0, 1 ), betaSet::get( 0, 0, 1 ), betaSet::get( 0, 0, 1 ), betaSet::get( -1, 0, 1 ) );
			voronoi3R->CarrierSet->transform( betaSet::get( -1, 0, 1 ), betaSet::get( 0, 0, 1 ), betaSet::get( 0, 0, 1 ), betaSet::get( -1, 0, 1 ) );
			
			int count = 1;
			
			for ( std::list<CvoronoiCell<betaSet> >::iterator ut = list->begin(); ut != list->end(); ++ut )
			{
				if ( ( *ut == *voronoi ) || ( *ut == *voronoi1R ) || ( *ut == *voronoi2R ) || ( *ut == *voronoi3R ) )
				{
					tileList.push_front( count );
					check = true;
				}
				++count;
			}
			
			if (!check)
			{	
				if ( ( *voronoi1R < *voronoi ) && ( *voronoi2R < *voronoi ) && ( *voronoi3R < *voronoi ) )
				{
					list->push_back( *voronoi );
				}
				else if ( ( *voronoi2R < *voronoi1R ) && ( *voronoi3R < *voronoi1R ) )
				{
					list->push_back( *voronoi1R );
				}
				else if ( *voronoi3R < *voronoi2R )
				{
					list->push_back( *voronoi2R );
				}
				else
				{
					list->push_back( *voronoi3R );
				}
				
				tileList.push_front( list->size() );
			}
			
		}
	}
	tileList.sort();
	tileList.unique();
	
	std::cout << " (" << tileList.size() << "): " << std::endl;
	
	for ( std::list<int>::iterator it = tileList.begin(); it != tileList.end(); ++it )
	{
		//std::cout << "\\includegraphics[width=0.8\\textwidth]{tile" << *it << "}" << std::endl;
		std::cout << *it << std::endl;
	}
	
	std::cout << std::endl << std::endl;
}


int main( int argc, char ** argv )
{
	
	std::string folder = argv[1];
	std::string fileName = argv[2];
	std::string fillColor = "nay";
	
	betaSet a,b;
	
	betaSet c, d;
	std::list<CvoronoiCell<betaSet> > list;
	
	c = betaSet::get(0,0);
	while ( std::cin >> d )
	{
		print( std::cout, d );
		
		testTiles( c, d, &list, fillColor );
	}
	
	betaSet Large = betaSet::get(-1,4);
	
	//list.sort();
	
	int count = 0;
	for ( std::list<CvoronoiCell<betaSet> >::iterator it = list.begin(); it != list.end(); ++it )
	{
			std::ostringstream oss;
			oss << folder << "/" << fileName << ++count << "_svg";
			
			std::ofstream myfile ( oss.str().c_str() );
			
			if (myfile.is_open())
			{
				myfile << "<svg " << " width=\"100\" height=\"100\" viewBox=\"-8 -8 16 16\" >" << '\n';
				
				//myfile << "<rect x=\"-8\" y=\"-8\" width=\"3\" height=\"3\" style=\"fill:rgb(255,255,255);stroke-width:0.1;stroke:rgb(0,0,0);fill-opacity:0\" />" << std::endl;

				//myfile << "<text x=\"-8\" y=\"-6.2\" fill=\"black\" font-size=\"3\">" << count << "</text>" << std::endl;

				myfile << "<!-- " << round(it->value()) << " -->" << std::endl;
				myfile << "<g transform=\"scale(1,-1)\">" << '\n';
				
				it->colorify();
				
				it->svg( myfile );
				
				//it->CarrierSet->svg( myfile );
				
				it->Center.setColor( "rgb(25,25,25)", "rgb(255,255,255)", "0.01em" );
				it->Center.svg( myfile );
				
				
				//it->Cell->svg( myfile );
				
				myfile << "</g>" << '\n';
				
				myfile << "</svg>" << '\n';
				
				
				myfile.close();
				
				
				std::cout << std::fixed << round(it->value()) << std::endl;
				
				//std::cout << fileName << ": " << it->getDescription() << std::endl;
			}
			
	}
	
	
}
