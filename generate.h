#ifndef _GENERATE_
#define _GENERATE_

#include <iostream>
#include <cmath>

#include "betaSet.h"
#include "geometricObject.h"

betaSet steppingFunction( betaSet c, betaSet d, betaSet x, bool limit = false );

betaSet iterateBeta( betaSet c, betaSet d, betaSet x, char &mark );

betaSet letterSpace( betaSet c, betaSet d, char mark );

std::list<betaSet> quasicrystal1D( const betaSet c, const betaSet d, const betaSet x, const betaSet y, const betaSet a, betaSet (*iterate)(betaSet, betaSet, betaSet, char&) );

CdeloneSet<betaSet> quasicrystal2D( std::list<betaSet> &x, std::list<betaSet> &y );

Cpoint<betaSet> transformBeta( const Cpoint<betaSet> &point );


#endif
