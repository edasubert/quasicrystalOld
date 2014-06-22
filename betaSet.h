#ifndef _BETAsET_
#define _BETAsET_

#include <cstring>
#include <iostream>
#include <cstdio>

#include <gmp.h>

typedef long long number;

class betaSet
{
	protected:
		number a, b;
		number c;
		static double constant;
	public:
		betaSet();
		betaSet(number I_a);
		betaSet(number I_a, number I_b);
		betaSet(number I_a, number I_b, number I_c);
		//~betaSet();
		
		betaSet static get(number I_a, number I_b);
		betaSet static get(number I_a, number I_b, number I_c);
		
		void set(number I_a, number I_b, number I_c);
		
		int simplify();
		
		betaSet star()const;
		
		betaSet& operator = ( const int &Input );
		
		betaSet operator + ( const betaSet &Input )const;
		betaSet operator - ( const betaSet &Input )const;
		betaSet operator * ( const betaSet &Input )const;
		betaSet operator / ( const betaSet &Input )const;
		betaSet& operator += ( const betaSet &Input );
		betaSet& operator -= ( const betaSet &Input );
		betaSet& operator *= ( const betaSet &Input );
		betaSet& operator /= ( const betaSet &Input );
		
		betaSet operator * ( const number multiplicator )const;
		betaSet operator / ( const number divider )const;
		betaSet operator / ( const int term )const;
		betaSet operator + ( const int term )const;
		
		bool operator == ( const betaSet &Input )const;
		bool operator < ( const betaSet &Input )const;
		bool operator > ( const betaSet &Input )const;
		bool operator <= ( const betaSet &Input )const;
		bool operator >= ( const betaSet &Input )const;
		bool operator != ( const betaSet &Input )const;
		
		operator double() const;
		
		friend std::ostream& operator << ( std::ostream & stream, const betaSet Input );
		friend void print( std::ostream & stream, const betaSet Input );
		friend std::istream& operator >> ( std::istream & stream, betaSet& Input );
		
};

number gcd( number a, number b );
number sign( number a );

#endif
