#include "geometricObject.h"
#include "betaSet.h"
#include "generate.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <iterator> 
#include <iomanip>

const double BASE_WIDTH = 0.015;
const int OUTPUT_STEP = 5000;

typedef betaSet numberType;

int main( int argc, char ** argv )
{
	
	unsigned int start = clock();
	

	std::string fileName = argv[1];
	
	std::cout << "Diagram generator" << std::endl << "====================" << std::endl;
	
	std::string fillColor = "rgb(51,181,229)";
	std::string strokeColor = "rgb(25,25,25)";
	std::string strokeWidth = "0.01em";
	
	
	// generate quasi ==================================================
	betaSet c, d;
	betaSet x1, y1;
	betaSet x2, y2;
	
	c = betaSet::get( 0, 0 );
	x1 = betaSet::get(  100, 0 );
	y1 = betaSet::get(  420, 0 );
	x2 = betaSet::get(  100, 0 );
	y2 = betaSet::get(  250, 0 );
	
	y1 = x1 + y1;
	y2 = x2 + y2;
	
	
	char mark = ' ';
	int countDiagrams = 0;
	
	while ( std::cin >> d )
	{
		++countDiagrams;
		
		CvoronoiCell<numberType>* voronoi;
		voronoi = new CvoronoiCell<numberType>();
		
		std::cout << "Diagram " << countDiagrams << std::endl << std::flush;
		std::cout << "Generating points " << std::flush;
		
		std::list<numberType> list1 = quasicrystal1D( c, d, x1, y1, c.star(), &iterateBeta );
		
		std::list<numberType> list2 = quasicrystal1D( c, d, x2, y2, c.star(), &iterateBeta );
		
		int listSize = list1.size()*list2.size();
		
		CvoronoiCell<numberType>::large = letterSpace( c, d, 'L' );
		
		
		// generate tile ===================================================
		
		//std::cout << "DONE: " << voronoi->CarrierSet->size() << std::endl << clock()-start << std::endl << std::flush;
		
		
		int count = 0;
		
		std::ostringstream cache;
		
		std::cout << "Generation: " << std::endl << std::flush;
		
		std::list<numberType>::iterator upperList1 = list1.begin();
		std::advance( upperList1, 5 );
		
		std::list<numberType>::iterator middleList1 = list1.begin();
		std::advance( middleList1, 2 );
		
		
		for ( std::list<numberType>::iterator it = list1.begin(); upperList1 != list1.end(); ++it, ++upperList1, ++middleList1 )
		{
			std::list<numberType>::iterator upperList2 = list2.begin();
			std::advance( upperList2, 5 );
			
			std::list<numberType>::iterator middleList2 = list2.begin();
			std::advance( middleList2, 2 );
			
			for ( std::list<numberType>::iterator ot = list2.begin(); upperList2 != list2.end(); ++ot, ++upperList2, ++middleList2 )
			{
				std::ostringstream strokeWidthComp;
				strokeWidthComp << ((7+4*sqrt(3)) *BASE_WIDTH)/(15*(sqrt(3)-1))-(11*BASE_WIDTH*(d-c))/(15*(sqrt(3)-1)) << "em";
				
				strokeWidth = strokeWidthComp.str().c_str();
				
				
				std::list<numberType> subList1( it, upperList1 );
				std::list<numberType> subList2( ot, upperList2 );
				
				*voronoi->CarrierSet = quasicrystal2D( subList1, subList2 );
				voronoi->CarrierSet->setDescription("Deloneovská množina bodů");
				voronoi->CarrierSet->setColor( fillColor, strokeColor, strokeWidth );
				
				voronoi->CarrierSet->setPackingR();
				voronoi->CarrierSet->setCoveringR(CvoronoiCell<numberType>::large);
				
				std::list<Cpoint<numberType> >::iterator centerPoint = voronoi->CarrierSet->begin();
				std::advance( centerPoint, 12 );
				voronoi->setCenter( *centerPoint );
				
				voronoi->setColor( fillColor, strokeColor, strokeWidth );
				
				voronoi->construct();
				voronoi->colorify();
				voronoi->svg( cache );
				voronoi->Center.setColor( fillColor, strokeColor, strokeWidth );
				voronoi->Center.svg( cache );
				
				++count;
				if ( count%OUTPUT_STEP == 1 )
				{
					std::cout << count << "/" << listSize << std::endl << clock()-start << std::endl << std::flush;
				}
				
				
			}
		}
		
		std::ostringstream oss;
		oss << fileName << std::setfill('0') << std::setw(5) << countDiagrams;
				
		std::ofstream myfile ( oss.str().c_str() );
		
		myfile << "<svg width=\"3840\" height=\"2160\" viewBox=\"80 -152 112.5 84.25\">\n" << std::endl;
		myfile << "<g transform=\"scale(1,-1)\">" << '\n';
		myfile << "<!-- ";
		print( myfile, c );
		myfile << ", ";
		print( myfile, d );
		myfile << " -->";
		
		myfile << cache.str().c_str();
		
		voronoi->CarrierSet->svg( myfile );
		
		//myfile << "<circle cx=\"0\" cy=\"0\" r=\"0.03em\" stroke=\"rgb(25,25,25)\" stroke-width=\"0\" fill=\"rgb(200,25,25)\" />" << std::endl;
		
		myfile << "</g>\n";
		myfile << "</svg>";
		
		
		delete voronoi;
		
		myfile.close();
		
		std::cout << std::endl << clock()-start << std::endl << "====================" << std::endl << std::endl << std::flush;
	}
}
