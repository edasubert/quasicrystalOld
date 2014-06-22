#include <cmath>
#include <iostream>

#include "betaSet.h"

double betaSet::constant = 2 + sqrt(3);

betaSet::betaSet()
{
	a = 0;
	b = 0;
	c = 1;
}

betaSet::betaSet(number I_a)
{
	a = I_a;
	b = 0;
	c = 1;
}

betaSet::betaSet(number I_a, number I_b)
{
	a = I_a;
	b = I_b;
	c = 1;
}

betaSet::betaSet(number I_a, number I_b, number I_c)
{
	a = I_a;
	b = I_b;
	c = I_c;
}

void betaSet::set(number I_a, number I_b, number I_c)
{
	a = I_a;
	b = I_b;
	c = I_c;
}

betaSet betaSet::get(number I_a, number I_b)
{
	betaSet Output;
	Output.a = I_a;
	Output.b = I_b;
	Output.c = 1;
	
	return Output;
}

betaSet betaSet::get(number I_a, number I_b, number I_c)
{
	betaSet Output;
	Output.a = I_a;
	Output.b = I_b;
	Output.c = I_c;
	
	return Output;
}

betaSet& betaSet::operator = ( const int &Input )
{
	constant = 2 + sqrt(3);
	a = Input;
	b = 0;
	c = 1;
	
	return *this;
}

int betaSet::simplify()
{
	number cache;
	if ( ( ( cache = gcd(a,b) ) != 0 ) && ( ( cache = gcd(cache,c) ) != 0 ) && ( cache > 1 ) )
	{
		//std::cout << a << ", " << b << ", " << c << " => " << cache << std::endl;
		a = static_cast<number>(a/cache);
		b = static_cast<number>(b/cache);
		c = static_cast<number>(c/cache);
		
		return 1;
	}
	
	return 0;
}

betaSet betaSet::star()const
{
	betaSet Output;
	Output.a = a + 4*b;
	Output.b = -b;
	Output.c = c;
	
	Output.simplify();
	
	return Output;
}

betaSet betaSet::operator + ( const betaSet &Input )const
{
	betaSet Output;
	Output.a = a*Input.c + Input.a*c;
	Output.b = b*Input.c + Input.b*c;
	Output.c = Input.c*c;
	
	Output.simplify();
	
	return Output;
}

betaSet betaSet::operator - ( const betaSet &Input )const
{
	betaSet Output;
	Output.a = a*Input.c - Input.a*c;
	Output.b = b*Input.c - Input.b*c;
	Output.c = Input.c*c;
	
	Output.simplify();
	
	return Output;
}

betaSet betaSet::operator * ( const betaSet &Input )const
{
	betaSet Output;
	
	Output.a = a*Input.a - b*Input.b;
	Output.b = b*Input.a + a*Input.b + 4*b*Input.b;
	Output.c = Input.c*c;
	
	Output.simplify();
	
	return Output;
}

betaSet betaSet::operator / ( const betaSet &Input )const
{
	betaSet Output;
	
	Output.a = (a*Input.a + b*Input.b + 4*a*Input.b)*Input.c;
	Output.b = (b*Input.a - a*Input.b)*Input.c;
	Output.c = (Input.a*Input.a + 4*Input.a*Input.b + Input.b*Input.b)*c;
	
	Output.simplify();
	
	return Output;
}

betaSet& betaSet::operator += ( const betaSet &Input )
{
	a = a*Input.c + Input.a*c;
	b = b*Input.c + Input.b*c;
	c = Input.c*c;
	
	return *this;
}

betaSet& betaSet::operator -= ( const betaSet &Input )
{
	a = a*Input.c - Input.a*c;
	b = b*Input.c - Input.b*c;
	c = Input.c*c;
	
	return *this;
}

betaSet& betaSet::operator *= ( const betaSet &Input )
{
	number cache = a*Input.a - b*Input.b;
	b = b*Input.a + a*Input.b + 4*b*Input.b;
	a = cache;
	c = Input.c*c;
	
	return *this;
}

betaSet& betaSet::operator /= ( const betaSet &Input )
{
	number cache = (a*Input.a + b*Input.b + 4*a*Input.b)*Input.c;
	b = (b*Input.a - a*Input.b)*Input.c;
	a = cache;
	c = (Input.a*Input.a + 4*Input.a*Input.b + Input.b*Input.b)*c;
	
	return *this;
}

betaSet betaSet::operator * ( const number multiplicator )const
{
	betaSet Output;
	Output.a = a*multiplicator;
	Output.b = b*multiplicator;
	Output.c = c;
	
	Output.simplify();
	
	return Output;
}

betaSet betaSet::operator / ( const number divider )const
{
	betaSet Output;
	Output.a = a;
	Output.b = b;
	Output.c = c*divider;
	
	Output.simplify();
	
	return Output;
}

betaSet betaSet::operator + ( const int term )const
{
	betaSet Output;
	Output.a = a + term;
	Output.b = b;
	Output.c = c;
	
	return Output;
}

betaSet betaSet::operator / ( const int term )const
{
	betaSet Output;
	Output.a = a;
	Output.b = b;
	Output.c = c*term;
	
	return Output;
}

bool betaSet::operator == ( const betaSet &Input )const
{
	if ( ( Input.c*a == Input.a*c ) && ( Input.c*b == Input.b*c ) )
		return true;
	
	return false;
}

bool betaSet::operator != ( const betaSet &Input )const
{
	if ( ( Input.c*a == Input.a*c ) && ( Input.c*b == Input.b*c ) )
		return false;
	
	return true;
}

bool betaSet::operator < ( const betaSet &Input )const // numerical
{
	
	number x = Input.a;
	number y = Input.b;
	number z = Input.c;

//std::cout << sign( a*z+b*z*2 - x*c-y*c*2 )*( a*z+b*z*2 - x*c-y*c*2 )*( a*z+b*z*2 - x*c-y*c*2 ) << " " << sign(y*c - b*z)*(y*c - b*z)*(y*c - b*z)*3 << std::endl;
//std::cout << ( a+b*(2+sqrt(3)) )*z << " " << ( x+y*(2+sqrt(3)) )*c << std::endl;
//std::cout << ( a*z+b*z*2 - x*c-y*c*2 ) << " " << ( (y*c - b*z)*sqrt(3) ) << std::endl;
//std::cout << ( a*z+b*z*2 - x*c-y*c*2 )*( a*z+b*z*2 - x*c-y*c*2 ) << " " << ( (y*c - b*z)*sqrt(3) )*( (y*c - b*z)*sqrt(3) ) << std::endl;
//std::cout << ( z*z*(a+2*b)*(a+2*b) + c*c*(x+2*y)*(x+2*y) ) << " " << ( 3*b*b*z*z + 3*y*y*c*c + 2*c*z*( x*(a+2*b) + y*(2*a+b) ) ) << std::endl;
//std::cout << a*a*z*z + 4*a*b*z*z + b*b*z*z + x*x*c*c + 4*x*y*c*c + y*y*c*c << " " << 2*a*c*x*z + 4*a*c*z*y + 4*b*c*x*z + 2*b*c*y*z << std::endl;
//std::cout << a*a*z*z + 4*a*b*z*z + b*b*z*z + x*x*c*c + 4*x*y*c*c + y*y*c*c << " " << 2*a*c*x*z + 4*a*c*z*y + 4*b*c*x*z + 2*b*c*y*z << std::endl;
	
	//if ( static_cast<double>(*this) < static_cast<double>(Input) )
	//if ( ( z*z*(a+2*b)*(a+2*b) + c*c*(x+2*y)*(x+2*y) ) < ( 3*b*b*z*z + 3*y*y*c*c + 2*c*z*( x*(a+2*b) + y*(2*a+b) ) ) )
	//if ( a*a*z*z + 4*a*b*z*z + b*b*z*z + x*x*c*c + 4*x*y*c*c + y*y*c*c < 2*a*c*x*z + 4*a*c*z*y + 4*b*c*x*z + 2*b*c*y*z )
	if ( sign( a*z+b*z*2 - x*c-y*c*2 )*( a*z+b*z*2 - x*c-y*c*2 )*( a*z+b*z*2 - x*c-y*c*2 ) < sign(y*c - b*z)*(y*c - b*z)*(y*c - b*z)*3 )
		return true;
	
	return false;
}

bool betaSet::operator > ( const betaSet &Input )const // numerical
{
	
	number x = Input.a;
	number y = Input.b;
	number z = Input.c;
	
	//if ( static_cast<double>(*this) > static_cast<double>(Input) )
	if ( sign( a*z+b*z*2 - x*c-y*c*2 )*( a*z+b*z*2 - x*c-y*c*2 )*( a*z+b*z*2 - x*c-y*c*2 ) > sign(y*c - b*z)*(y*c - b*z)*(y*c - b*z)*3 )
		return true;
	
	return false;
}

bool betaSet::operator <= ( const betaSet &Input )const
{
	return ( (*this == Input) || (*this < Input) );
}

bool betaSet::operator >= ( const betaSet &Input )const
{
	return ( (*this == Input) || (*this > Input) );
}

betaSet::operator double() const
{
	return (a + b*constant)/c;
}

std::ostream& operator << ( std::ostream & stream, const betaSet Input )
{
	//stream << "( " << Input.a << " + " << Input.b << "*beta )/ " << Input.c;
	stream << static_cast<double>(Input);
	
	return stream;
}

void print( std::ostream & stream, const betaSet Input )
{
	if ( Input.b >= 0 )
	{
		stream << "(" << Input.a << "+" << Input.b << "*beta)/" << Input.c;
	}
	else
	{
		stream << "(" << Input.a << "" << Input.b << "*beta)/" << Input.c;
	}
}

std::istream& operator >> ( std::istream & stream, betaSet& Input )
{
	//scanf( "( %ld %ld * sqrt(3) ) / %ld \t\n", &Input.a, &Input.b, &Input.c );
	stream.ignore(256,'(');
	stream >> Input.a >> Input.b;
	stream.ignore(256,'/');
	stream >> Input.c;
	
	return stream;
}

//SUPORT FUNCTIONS
number gcd( number a, number b )
{
	a = ( a > 0 ) ? a : -a;
	b = ( b > 0 ) ? b : -b;
	number tmp;
	while ( b != 0 )
	{
		tmp = b;
		b = a % b;
		a = tmp;
	}
	return a;
}

number sign( number a )
{
	if ( a > 0 )
		return 1;
	else if ( a < 0 )
		return -1;
	else
		return 0;
}
