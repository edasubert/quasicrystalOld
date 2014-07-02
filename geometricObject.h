#ifndef _GEOMETRICoBJECT_
#define _GEOMETRICoBJECT_

#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <cmath>

#include "betaSet.h"


//typedef double numberType;
#define _ERROR_
#define _IMG_OUTPUT_


template <typename numberType>
class Cfigure
{
	protected:
		std::string name;
		std::string description;
		
		std::string fillColor;	// format rgb(R,G,B)
		std::string strokeColor;
		std::string strokeWidth;
		
		
	public:
		Cfigure();
		void var_dump( std::ostream& out ) const;
		void setDescription( const std::string input );
		std::string getDescription();
		
		void setColor( const std::string I_fillColor, const std::string I_strokeColor, const std::string I_strokeWidth );
		void setFillColor( const std::string I_fillColor );
		void svg( std::ostream& out ) const;
		void svg( std::ostream& out, double a, double b, double c, double d ) const;
};


template <typename numberType>
class Cpoint : public virtual Cfigure<numberType>
{
	protected:
		numberType x;
		numberType y;
	public:
		Cpoint();
		Cpoint( const Cpoint<numberType>& I_Point );
		Cpoint( numberType xCoord, numberType yCoord );
		
		void var_dump( std::ostream& out ) const;
		
		numberType getX() const;
		numberType getY() const;
		
		void setX( numberType xCoord );
		void setY( numberType yCoord );
		
		void set( numberType xCoord, numberType yCoord );
		
		Cpoint<numberType> operator * ( const int multiplicator )const;
		Cpoint<numberType> operator / ( const int divider )const;
		
		bool operator == ( const Cpoint<numberType> &compare ) const;
		bool operator != ( const Cpoint<numberType> &compare ) const;

		Cpoint<numberType> operator - ( const Cpoint<numberType> &term ) const;
		
		void svg( std::ostream& out ) const;
		void svg( std::ostream& out, double a, double b, double c, double d ) const;
};


template <typename numberType>
class Cvector : public virtual Cpoint<numberType>
{
	public:
		Cvector();
		Cvector( const Cpoint<numberType>& I_Point );
		Cvector( const Cvector& I_Vector );
		Cvector( numberType xCoord, numberType yCoord );
		
		Cvector operator * ( const int multiplicator )const;
		Cvector operator * ( const numberType multiplicator )const;
		Cvector operator / ( const int divider )const;
		Cvector operator + ( const Cpoint<numberType> term )const;
		Cvector operator - ( const Cpoint<numberType> term )const;
		
		Cvector operator * ( const Cvector term )const;
		
		numberType sum()const;
		
		void var_dump( std::ostream& out ) const;
		
		void svg( std::ostream& out ) const;
		void svg( std::ostream& out, double a, double b, double c, double d ) const;
};


template <typename numberType>
class CpointSet : public virtual Cfigure<numberType>
{
	protected:
		std::list<Cpoint<numberType> >* points;
	public:
		CpointSet();
		CpointSet( const CpointSet& I_PointSet );
		~CpointSet();
		
		void var_dump( std::ostream& out ) const;
		
		void addPoint( Cpoint<numberType> addition );
		
		CpointSet& operator << ( Cpoint<numberType> addition );
		CpointSet& operator = ( const CpointSet& I_PointSet );
		
		typename std::list<Cpoint<numberType> >::iterator begin();
		typename std::list<Cpoint<numberType> >::iterator end();
		
		typename std::list<Cpoint<numberType> >::reverse_iterator rbegin();
		typename std::list<Cpoint<numberType> >::reverse_iterator rend();
		
		void transform( const numberType a, const numberType b, const numberType c, const numberType d );
		
		const Cpoint<numberType>& front() const;
		const Cpoint<numberType>& back() const;
		
		void clear();
		int size();
		void unique();
};

template <typename numberType>
class CdeloneSet : public CpointSet<numberType>, public virtual Cfigure<numberType>
{
	protected:
		double PackingR;
		double CoveringR;
	public:
		CdeloneSet();
		CdeloneSet( const CdeloneSet<numberType>& I_PointSet );
		
		void var_dump( std::ostream& out ) const;
		
		CdeloneSet<numberType>& operator = ( const CdeloneSet<numberType>& I_DeloneSet );
		
		void setPackingR( double I_PackingR );
		void setCoveringR( double I_CoveringR );
		
		double getPackingR();
		double getCoveringR();
		
		void setPackingR();
		void setCoveringR();
		
		void svg( std::ostream& out ) const;
		void svg( std::ostream& out, double a, double b, double c, double d ) const;
};


template <typename numberType>
class CvoronoiCell : public virtual Cfigure<numberType>
{
	public:
		CdeloneSet<numberType> *CarrierSet;
		CpointSet<numberType> *Cell;
		Cpoint<numberType> Center;
	public:
		static numberType large;
		CvoronoiCell();
		CvoronoiCell( const CdeloneSet<numberType>& I_CarrierSet, const Cpoint<numberType> I_Center );
		CvoronoiCell( const CdeloneSet<numberType>& I_CarrierSet );
		CvoronoiCell( const CvoronoiCell<numberType>& I_VoronoiCell);
		~CvoronoiCell();
		
		
		void setCenter( const Cpoint<numberType> I_Center );
		
		void var_dump( std::ostream& out ) const;
		
		void construct();
		
		CvoronoiCell<numberType>& operator = ( const CvoronoiCell<numberType>& I_VoronoiCell );
		
		bool operator == ( const CvoronoiCell<numberType> &compare ) const;
		bool operator < ( const CvoronoiCell<numberType> &compare ) const;
		
		void svg( std::ostream& out ) const;
		void svg( std::ostream& out, double a, double b, double c, double d ) const;
		
		double value() const;
		void colorify();
};

template <typename numberType>
double euklid( const Cpoint<numberType>& a, const Cpoint<numberType>& b );







// FIGURE ==============================================================
template <typename numberType>
Cfigure<numberType>::Cfigure()
{
	this->name = "[UNSPECIFIED_FIGURE]";
	description = "[UNSPECIFIED_FIGURE]";
}

template <typename numberType>
void Cfigure<numberType>::var_dump( std::ostream& out ) const
{
	out << std::endl << "====================" << std::endl; 
	out << "Name: " << this->name << std::endl << "Description: " << description << std::endl; 
	out << "====================" << std::endl;
}

template <typename numberType>
void Cfigure<numberType>::setDescription( const std::string input )
{
	description = input;
}

template <typename numberType>
std::string Cfigure<numberType>::getDescription()
{
	return description;
}

template <typename numberType>
void Cfigure<numberType>::setColor( const std::string I_fillColor, const std::string I_strokeColor, const std::string I_strokeWidth )
{
	fillColor = I_fillColor;
	strokeColor = I_strokeColor;
	strokeWidth = I_strokeWidth;
}

template <typename numberType>
void Cfigure<numberType>::setFillColor( const std::string I_fillColor )
{
	this->fillColor = I_fillColor;
}



// POINT ===============================================================
template <typename numberType>
Cpoint<numberType>::Cpoint()
:Cfigure<numberType>()
{
	this->name = "Point";
	this->description = "";
	
	x = 0;
	y = 0;
}

template <typename numberType>
Cpoint<numberType>::Cpoint( const Cpoint<numberType>& I_Point )
{
	this->name = "Point";
	this->description = I_Point.fillColor;
	
	x = I_Point.x;
	y = I_Point.y;
	
	this->fillColor = I_Point.fillColor;
	this->strokeColor = I_Point.strokeColor;
	this->strokeWidth = I_Point.strokeWidth;
}

template <typename numberType>
Cpoint<numberType>::Cpoint( numberType xCoord, numberType yCoord )
{
	this->name = "Point";
	this->description = "";
	
	x = xCoord;
	y = yCoord;
}

template <typename numberType>
void Cpoint<numberType>::var_dump( std::ostream& out ) const
{
	out << std::endl << "====================" << std::endl; 
	out << "Name: " << this->name << std::endl;
	out << "Coordinates: X = ";
	print( out, x );
	out << " Y = ";
	print( out, y );
	out << std::endl;
	out << "Description: " << this->description << std::endl; 
	out << "====================" << std::endl;
}

template <typename numberType>
numberType Cpoint<numberType>::getX() const
{
	return x;
}

template <typename numberType>
numberType Cpoint<numberType>::getY() const
{
	return y;
}

template <typename numberType>
void Cpoint<numberType>::setX( numberType xCoord )
{
	x = xCoord;
}

template <typename numberType>
void Cpoint<numberType>::setY( numberType yCoord )
{
	y = yCoord;
}

template <typename numberType>
void Cpoint<numberType>::set( numberType xCoord, numberType yCoord )
{
	x = xCoord;
	y = yCoord;
}

template <typename numberType>
Cpoint<numberType> Cpoint<numberType>::operator * ( const int multiplicator )const
{
	Cpoint<numberType> Output;
	Output.x = x*multiplicator;
	Output.y = y*multiplicator;
	
	//Output.x = x.operator*(multiplicator);
	//Output.y = y.operator*(multiplicator);
	
	return Output;
}

template <typename numberType>
Cpoint<numberType> Cpoint<numberType>::operator / ( const int divider )const
{
	Cpoint<numberType> Output;
	Output.x = x/divider;
	Output.y = y/divider;
	
	return Output;
}

template <typename numberType>
bool Cpoint<numberType>::operator == ( const Cpoint<numberType> &compare ) const
{
	return ( ( x == compare.x ) && ( y == compare.y ) );
}

template <typename numberType>
bool Cpoint<numberType>::operator != ( const Cpoint<numberType> &compare ) const
{
	return ( ( x != compare.x ) || ( y != compare.y ) );
}

template <typename numberType>
Cpoint<numberType> Cpoint<numberType>::operator - ( const Cpoint<numberType> &term ) const
{
	Cpoint<numberType> Output( *this );
	Output.x = x - term.x;
	Output.y = y - term.y;
	
	return Output;
}

template <typename numberType>
void Cpoint<numberType>::svg( std::ostream& out ) const
{
	out << "<circle cx=\"" << x << "\" cy=\"" << y << "\" r=\"" << this->strokeWidth << "\" stroke=\"" << this->strokeColor << "\" stroke-width=\"" << 0 << "\" fill=\"" << this->strokeColor << "\" />" << std::endl;
}

template <typename numberType>
void Cpoint<numberType>::svg( std::ostream& out, double a, double b, double c, double d ) const
{
	out << "<circle cx=\"" << a*x + b*y << "\" cy=\"" << c*x + d*y << "\" r=\"" << this->strokeWidth << "\" stroke=\"" << this->strokeColor << "\" stroke-width=\"" << 0 << "\" fill=\"" << this->strokeColor << "\" />" << std::endl;
}



// VECTOR ==============================================================
template <typename numberType>
Cvector<numberType>::Cvector()
:Cpoint<numberType>::Cpoint()
{
	this->name = "Vector";
}

template <typename numberType>
Cvector<numberType>::Cvector( const Cvector<numberType>& I_Vector )
:Cpoint<numberType>::Cpoint( I_Vector )
{
	this->name = "Vector";
}

template <typename numberType>
Cvector<numberType>::Cvector( const Cpoint<numberType>& I_Point )
:Cpoint<numberType>::Cpoint( I_Point )
{
	this->name = "Vector";
}

template <typename numberType>
Cvector<numberType>::Cvector( numberType xCoord, numberType yCoord )
:Cpoint<numberType>::Cpoint( xCoord, yCoord )
{
	this->name = "Vector";
}

template <typename numberType>
Cvector<numberType> Cvector<numberType>::operator * ( const int multiplicator )const
{
	Cvector<numberType> Output;
	Output.x = this->x*multiplicator;//x.operator*(multiplicator);
	Output.y = this->y*multiplicator;//y.operator*(multiplicator);
	
	//Output.x = this->x.operator*(multiplicator);
	//Output.y = this->y.operator*(multiplicator);
	
	return Output;
}

template <typename numberType>
Cvector<numberType> Cvector<numberType>::operator * ( const numberType multiplicator )const
{
	Cvector<numberType> Output;
	Output.x = this->x*(multiplicator);
	Output.y = this->y*(multiplicator);
	
	return Output;
}

template <typename numberType>
Cvector<numberType> Cvector<numberType>::operator / ( const int divider )const
{
	Cvector<numberType> Output;
	Output.x = this->x/divider;
	Output.y = this->y/divider;
	
	return Output;
}

template <typename numberType>
Cvector<numberType> Cvector<numberType>::operator + ( const Cpoint<numberType> term )const
{
	Cvector<numberType> Output;
	Output.x = this->x + term.getX();
	Output.y = this->y + term.getY();
	
	return Output;
}

template <typename numberType>
Cvector<numberType> Cvector<numberType>::operator - ( const Cpoint<numberType> term )const
{
	Cvector<numberType> Output;
	Output.x = this->x - term.getX();
	Output.y = this->y - term.getY();
	
	return Output;
}

template <typename numberType>
Cvector<numberType> Cvector<numberType>::operator * ( const Cvector<numberType> term )const
{
	Cvector<numberType> Output;
	Output.x = this->x * term.getX();
	Output.y = this->y * term.getY();
	
	return Output;
}

template <typename numberType>
numberType Cvector<numberType>::sum()const
{
	return this->x+this->y;
}

template <typename numberType>
void Cvector<numberType>::var_dump( std::ostream& out ) const
{
	out << std::endl << "=>=>=>=>=>=>=>=>=>=>" << std::endl; 
	out << "Name: " << this->name << std::endl;
	out << "Coordinates: X = " << this->x << " Y = " << this->y << std::endl;
	out << "Description: " << this->description << std::endl; 
	out << "=>=>=>=>=>=>=>=>=>=>" << std::endl;
}

template <typename numberType>
void Cvector<numberType>::svg( std::ostream& out ) const
{
	out << "<line x1=\"0\" y1=\"0\" x2=\"" << this->x << "\" y2=\"" << this->y << "\" marker-end=\"url(#triangle)\"  stroke=\"" << this->strokeColor << "\" stroke-width=\"" << 0 << "\" fill=\"" << this->strokeColor << "\" />" << std::endl;
}

template <typename numberType>
void Cvector<numberType>::svg( std::ostream& out, double a, double b, double c, double d ) const
{
	out << "<line x1=\"0\" y1=\"0\" x2=\"" << a*this->x + b*this->y << "\" y2=\"" << c*this->x + d*this->y << "\" marker-end=\"url(#triangle)\"  stroke=\"" << this->strokeColor << "\" stroke-width=\"" << 0 << "\" fill=\"" << this->strokeColor << "\" />" << std::endl;
}


// POINT SET ===========================================================
template <typename numberType>
CpointSet<numberType>::CpointSet()
{
	this->name = "Point Set";
	this->description = "";
	
	points = new std::list<Cpoint<numberType> >;
}

template <typename numberType>
CpointSet<numberType>::CpointSet( const CpointSet<numberType>& I_PointSet )
{
	this->name = "Point Set";
	this->description = "";
	
	points = new std::list<Cpoint<numberType> >;
	
	this->description = I_PointSet.description;
	*points = *(I_PointSet.points);
		
	this->fillColor = I_PointSet.fillColor;
	this->strokeColor = I_PointSet.strokeColor;
	this->strokeWidth = I_PointSet.strokeWidth;
}

template <typename numberType>
CpointSet<numberType>::~CpointSet()
{
	delete points;
}

template <typename numberType>
void CpointSet<numberType>::var_dump( std::ostream& out ) const
{
	out << std::endl << "*************************" << std::endl; 
	out << "Name: " << this->name << std::endl;
	out << "Description: " << this->description << std::endl; 
	
	for ( typename std::list<Cpoint<numberType> >::iterator it = points->begin(); it != points->end(); ++it )
    {
		it->var_dump( out );
	}
	
	out << "*************************" << std::endl;
}

template <typename numberType>
void CpointSet<numberType>::addPoint( Cpoint<numberType> addition )
{
	points->push_front( addition );
}

template <typename numberType>
CpointSet<numberType>& CpointSet<numberType>::operator << ( Cpoint<numberType> addition )
{
	for ( typename std::list< Cpoint<numberType> >::iterator it = points->begin(); it != points->end(); ++it )
	{
		if ( *it == addition )
			return *this;
	}
	
	points->push_front( addition );
	
	return *this;
}

template <typename numberType>
CpointSet<numberType>& CpointSet<numberType>::operator = ( const CpointSet<numberType>& I_PointSet )
{
	this->description = I_PointSet.description;
	*points = *(I_PointSet.points);
	
	this->fillColor = I_PointSet.fillColor;
	this->strokeColor = I_PointSet.strokeColor;
	this->strokeWidth = I_PointSet.strokeWidth;
}

template <typename numberType>
typename std::list<Cpoint<numberType> >::iterator CpointSet<numberType>::begin()
{
	return points->begin();
}

template <typename numberType>
typename std::list<Cpoint<numberType> >::iterator CpointSet<numberType>::end()
{
	return points->end();
}

template <typename numberType>
typename std::list<Cpoint<numberType> >::reverse_iterator CpointSet<numberType>::rbegin()
{
	return points->rbegin();
}

template <typename numberType>
typename std::list<Cpoint<numberType> >::reverse_iterator CpointSet<numberType>::rend()
{
	return points->rend();
}

template <typename numberType>
void CpointSet<numberType>::clear()
{
	points->clear();
}

template <typename numberType>
int CpointSet<numberType>::size()
{
	return points->size();
}

template <typename numberType>
void CpointSet<numberType>::unique()
{
	points->unique();
}

template <typename numberType>
const Cpoint<numberType>& CpointSet<numberType>::front() const
{
	return points->front(); 
}

template <typename numberType>
const Cpoint<numberType>& CpointSet<numberType>::back() const
{
	return points->back(); 
}

template <typename numberType>
void CpointSet<numberType>::transform( const numberType a, const numberType b, const numberType c, const numberType d )
{
	for ( typename std::list<Cpoint<numberType> >::iterator it = points->begin(); it != points->end(); ++it )
	{
		it->set( a*it->getX() + b*it->getY(), c*it->getX() + d*it->getY() );
	}
}


// DELONE SET ==========================================================
template <typename numberType>
CdeloneSet<numberType>::CdeloneSet() : CpointSet<numberType>()
{
	this->name = "Delone Set";
	
	PackingR = 0;
	CoveringR = 0;
}

template <typename numberType>
CdeloneSet<numberType>::CdeloneSet( const CdeloneSet<numberType>& I_DeloneSet ) : CpointSet<numberType>()
{
	this->name = "Delone Set";
	
	this->description = I_DeloneSet.description;
	*(this->points) = *(I_DeloneSet.points);
	PackingR = I_DeloneSet.PackingR;
	CoveringR = I_DeloneSet.CoveringR;
	
	this->fillColor = I_DeloneSet.fillColor;
	this->strokeColor = I_DeloneSet.strokeColor;
	this->strokeWidth = I_DeloneSet.strokeWidth;
}

template <typename numberType>
CdeloneSet<numberType>& CdeloneSet<numberType>::operator = ( const CdeloneSet<numberType>& I_DeloneSet )
{
	this->name = "Delone Set";
	
	this->description = I_DeloneSet.description;
	*(this->points) = *(I_DeloneSet.points);
	PackingR = I_DeloneSet.PackingR;
	CoveringR = I_DeloneSet.CoveringR;
	
	this->fillColor = I_DeloneSet.fillColor;
	this->strokeColor = I_DeloneSet.strokeColor;
	this->strokeWidth = I_DeloneSet.strokeWidth;
}

template <typename numberType>
void CdeloneSet<numberType>::var_dump( std::ostream& out ) const
{
	out << std::endl << "*************************" << std::endl; 
	out << "Name: " << this->name << std::endl;
	out << "Description: " << this->description << std::endl; 
	out << "Packing radius: " << PackingR << std::endl; 
	out << "Covering radius: " << CoveringR << std::endl; 
	
	for ( typename std::list<Cpoint<numberType> >::iterator it = this->points->begin(); it != this->points->end(); ++it )
    {
		it->var_dump( out );
	}
	
	out << "*************************" << std::endl;
}

template <typename numberType>
void CdeloneSet<numberType>::setPackingR( double I_PackingR )
{
	PackingR = I_PackingR;
}

template <typename numberType>
void CdeloneSet<numberType>::setCoveringR( double I_CoveringR )
{
	CoveringR = I_CoveringR;
}

template <typename numberType>
double CdeloneSet<numberType>::getPackingR()
{
	return PackingR;
}

template <typename numberType>
double CdeloneSet<numberType>::getCoveringR()
{
	return CoveringR;
}

template <typename numberType>
void CdeloneSet<numberType>::setPackingR()
{
	typename std::list<Cpoint<numberType> >::iterator tmp = this->points->begin();
	
	double radius = euklid( *(++tmp), *tmp );
	double swap;
	
	for ( typename std::list<Cpoint<numberType> >::iterator it = this->points->begin(); it != this->points->end(); ++it )
	{
		tmp = it;
		++tmp;
		
		for ( typename std::list<Cpoint<numberType> >::iterator ot = tmp; ot != this->points->end(); ++ot )
		{
			swap = euklid( *it, *ot );
			radius = (radius > swap) ? swap : radius;
		}
	}
	
	PackingR = radius/2;
}

template <typename numberType>
void CdeloneSet<numberType>::setCoveringR()
{
	typename std::list<Cpoint<numberType> >::iterator tmp;
	
	double radius = 0;
	double swap;
	double closest;
	
	for ( typename std::list<Cpoint<numberType> >::iterator it = this->points->begin(); it != this->points->end(); ++it )
	{
		tmp = it;
		++tmp;
		
		closest = euklid( *it, *tmp );
		
		for ( typename std::list<Cpoint<numberType> >::iterator ot = tmp; ot != this->points->end(); ++ot )
		{
			swap = euklid( *it, *ot );
			closest = (closest > swap) ? swap : closest;
		}
		
		radius = (radius < closest) ? closest : radius;
	}
	
	CoveringR = radius;
}

template <typename numberType>
void CdeloneSet<numberType>::svg( std::ostream& out ) const
{
	for ( typename std::list<Cpoint<numberType> >::iterator it = this->points->begin(); it != this->points->end(); ++it )
    {
		it->setColor( this->fillColor, this->strokeColor, this->strokeWidth );
		it->svg(out);
	}
}

template <typename numberType>
void CdeloneSet<numberType>::svg( std::ostream& out, double a, double b, double c, double d ) const
{
	for ( typename std::list<Cpoint<numberType> >::iterator it = this->points->begin(); it != this->points->end(); ++it )
    {
		it->svg(out, a, b, c, d);
	}
}

// VORONOI CELL ========================================================
template <typename numberType>
CvoronoiCell<numberType>::CvoronoiCell()
{
	this->name = "Voronoi cell";
	this->description = "";
	
	CarrierSet = new CdeloneSet<numberType>();
	Cell = new CpointSet<numberType>();
}

template <typename numberType>
CvoronoiCell<numberType>::~CvoronoiCell()
{
	delete CarrierSet;
	delete Cell;
}

template <typename numberType>
CvoronoiCell<numberType>::CvoronoiCell( const CdeloneSet<numberType>& I_CarrierSet, const Cpoint<numberType> I_Center )
{
	this->name = "Voronoi cell";
	this->description = "";
	
	this->CarrierSet = new CdeloneSet<numberType>();
	this->Cell = new CpointSet<numberType>();
	
	*(this->CarrierSet) = I_CarrierSet;
	this->Center = I_Center;
}

template <typename numberType>
CvoronoiCell<numberType>::CvoronoiCell( const CdeloneSet<numberType>& I_CarrierSet )
{
	this->name = "Voronoi cell";
	this->description = "";
	
	this->CarrierSet = new CdeloneSet<numberType>();
	this->Cell = new CpointSet<numberType>();
	
	*(this->CarrierSet) = I_CarrierSet;
}

template <typename numberType>
CvoronoiCell<numberType>::CvoronoiCell( const CvoronoiCell<numberType>& I_VoronoiCell )
{
	this->name = "Voronoi cell";
	this->description = I_VoronoiCell.description;
	
	this->CarrierSet = new CdeloneSet<numberType>();
	this->Cell = new CpointSet<numberType>();
	
	*(this->CarrierSet) = *(I_VoronoiCell.CarrierSet);
	*(this->Cell) = *(I_VoronoiCell.Cell);
	this->Center = I_VoronoiCell.Center;
	
	this->fillColor = I_VoronoiCell.fillColor;
	this->strokeColor = I_VoronoiCell.strokeColor;
	this->strokeWidth = I_VoronoiCell.strokeWidth;
}

template <typename numberType>
void CvoronoiCell<numberType>::setCenter( const Cpoint<numberType> I_Center )
{
	this->Center = I_Center;
}

template <typename numberType>
CvoronoiCell<numberType>& CvoronoiCell<numberType>::operator = ( const CvoronoiCell<numberType>& I_VoronoiCell )
{
	this->name = "Voronoi cell";
	this->description = I_VoronoiCell.description;
	
	delete this->CarrierSet;
	delete this->Cell;
	
	this->CarrierSet = new CdeloneSet<numberType>();
	this->Cell = new CpointSet<numberType>();
	
	*(this->CarrierSet) = *(I_VoronoiCell.CarrierSet);
	*(this->Cell) = *(I_VoronoiCell.Cell);
	this->Center = I_VoronoiCell.Center;
	
	this->fillColor = I_VoronoiCell.fillColor;
	this->strokeColor = I_VoronoiCell.strokeColor;
	this->strokeWidth = I_VoronoiCell.strokeWidth;
}

template <typename numberType>
void CvoronoiCell<numberType>::var_dump( std::ostream& out ) const
{
	out << std::endl << "##############################" << std::endl; 
	out << "Name: " << this->name << std::endl;
	out << "Description: " << this->description << std::endl; 
	out << "Center: " << std::endl; 
	Center.var_dump( out );
	
	out << std::endl << "###############" << std::endl; 
	out << "Cell: " << std::endl; 
	Cell->var_dump( out );
	
	out << std::endl << "###############" << std::endl; 
	out << "Carrier set: " << std::endl; 
	CarrierSet->var_dump( out );
	
	out << std::endl << "##############################" << std::endl; 
}

template <typename numberType>
void CvoronoiCell<numberType>::construct()
{
	Cell->clear();
	
	// initialization of polygon
	Cpoint<numberType> point( Center.getX() + large.operator*(4), Center.getY() + large.operator*(4) );
	point.setDescription( "original" );
	*Cell << point;
	point.set( Center.getX() - large.operator*(1), Center.getY() + large.operator*(1) );
	*Cell << point;
	point.set( Center.getX() - large.operator*(1), Center.getY() - large.operator*(1) );
	*Cell << point;
	point.set( Center.getX() + large.operator*(1), Center.getY() - large.operator*(1) );
	*Cell << point;
	
	CpointSet<numberType> newCell = *Cell;

#ifndef _ERROR_	
std::cout << "EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE původní trojúhelník" << std::endl;
Cell->var_dump(std::cout);
#endif
	
	// cutting algorythm
	for ( typename std::list<Cpoint<numberType> >::iterator it = CarrierSet->begin(); it != CarrierSet->end(); ++it )
	{
		
		if ( ( euklid( *it, Center ) > CarrierSet->getCoveringR() ) || ( *it == Center ) )
			continue;
	
#ifndef _ERROR_
svg( std::cout );
std::cout << "EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE bod z množiny (předloha ořezu - it)" << std::endl;
#endif
		
		// vector from it toward center
		Cvector<numberType> n = Center - *it;
		n.setDescription( "n" );

#ifndef _ERROR_
std::cout <<std::endl << "n = Center - *it" <<std::endl;
n.var_dump(std::cout);
Center.var_dump(std::cout);
it->var_dump(std::cout);
#endif
		
		// normal form of axis of center and active point
		Cvector<numberType> c = n/2 + *it;
		c.setDescription( "c" );

#ifndef _ERROR_
std::cout <<std::endl << "c = n/2 + *it" <<std::endl;
c.var_dump(std::cout);
(n/2).var_dump(std::cout);
it->var_dump(std::cout);
#endif
		
		numberType d = (n*c).sum();	// constant for cut line
		
#ifndef _ERROR_
std::cout <<std::endl << "d = (n*c).sum() = ";
std::cout << d << std::endl;
(n*c).var_dump(std::cout);
#endif
		
		// check for position of Cell and axis
		newCell.clear();
		bool position, positionOld;
		typename std::list<Cpoint<numberType> >::iterator old = Cell->end();
		--old;
		position = ( (n*(*old)).sum() >= d );
		
		for ( typename std::list<Cpoint<numberType> >::iterator ot = Cell->begin(); ot != Cell->end(); ++ot )
		{
			positionOld = position;
			position = ( (n*(*ot)).sum() >= d );

#ifndef _ERROR_
std::cout << "EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE body z mnohoúhelníka" << std::endl;
old->var_dump(std::cout);
ot->var_dump(std::cout);
std::cout << "old position: " << positionOld << ", ot position:" << position << std::endl;
#endif			
			
			if ( positionOld != position )	// old and ot are on different sides of cut line
			{
				// vector from old to ot
				Cvector<numberType> u = *ot - *old;
				u.setDescription( "u" );
				
				numberType t = ( ( n*(c - (*old) )).sum() ) / ( (u*n).sum() ); // ( nx*( cx - old->getX() ) + ny*( cy - old->getY() ) )/( ux*nx + uy*ny );
				
#ifndef _IMG_OUTPUT_
std::cout << std::endl << std::endl << "<svg>" << std::endl;
svg( std::cout );
u.setColor( "rgb(51,181,229)", "rgb(250,25,25)", "0.01em" );
u.svg( std::cout );
n.setColor( "rgb(51,181,229)", "rgb(25,250,25)", "0.01em" );
n.svg( std::cout );
Center.setColor( "rgb(51,181,229)", "rgb(25,250,25)", "0.1em" );
Center.svg( std::cout );
it->setColor( "rgb(51,181,229)", "rgb(25,250,25)", "0.1em" );
it->svg( std::cout );
ot->setColor( "rgb(51,181,229)", "rgb(250,25,25)", "0.1em" );
ot->svg( std::cout );
old->setColor( "rgb(51,181,229)", "rgb(250,25,25)", "0.1em" );
old->svg( std::cout );
std::cout << "</svg>" << std::endl << std::endl;
#endif


#ifndef _ERROR_
std::cout <<std::endl << "t = (n*(c - old)).sum() / (u*n).sum() = ";
std::cout << t << std::endl << "old:" << std::endl;
(old)->var_dump(std::cout);
(c).var_dump(std::cout);
std::cout << "c - old:" << std::endl;
(c-(*old)).var_dump(std::cout);
				
u.var_dump(std::cout);
n.var_dump(std::cout);
(u*n).var_dump(std::cout);
std::cout << ( u*n ).sum() << '\t' << t << std::endl;
#endif

				
				Cpoint<numberType> newPoint( u*t + *old );
				newPoint.setDescription( "newPoint" );

#ifndef _ERROR_
(u*t).var_dump(std::cout);
#endif

				
				newCell << newPoint;

#ifndef _ERROR_
std::cout << "EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE přidávám dopočítaný" << (n*newPoint).sum() << "=" << d << std::endl;
newPoint.var_dump(std::cout);
#endif

			}
			
			if ( ( position ) && ( *ot != newCell.front() ) )	// ot is on same side of cut line as center
			{
				newCell << *ot;

#ifndef _ERROR_
std::cout << "EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE přidávám původní" << std::endl;
ot->var_dump(std::cout);
#endif

			}
			
			old = ot;
		}

#ifndef _ERROR_
std::cout << "EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE hotové dílo" << std::endl;
newCell.var_dump(std::cout);
std::cout << "OOOOOOOOOOOOOOOOOOOOOOOOOOOO" << std::endl;
#endif

		*Cell = newCell;
	}
	
}

template <typename numberType>
void CvoronoiCell<numberType>::svg( std::ostream& out ) const
{
	
	out << "<!-- " << this->description << " -->" << std::endl;
	out << "<polygon points=\"";
	for ( typename std::list<Cpoint<numberType> >::iterator it = Cell->begin(); it != Cell->end(); ++it )
    {
		out << it->getX() << "," << it->getY() << " ";
	}
	out << "\" fill=\"" << this->fillColor << "\" stroke=\"" << this->strokeColor << "\" stroke-width=\"" << this->strokeWidth << "\" />" << std::endl;
}

template <typename numberType>
void CvoronoiCell<numberType>::svg( std::ostream& out, double a, double b, double c, double d ) const
{
	out << "<polygon points=\"";
	for ( typename std::list<Cpoint<numberType> >::iterator it = Cell->begin(); it != Cell->end(); ++it )
    {
		out << a*it->getX() + b*it->getY() << "," << c*it->getX() + d*it->getY() << " ";
	}
	out << "\" fill=\"" << this->fillColor << "\" stroke=\"" << this->strokeColor << "\" stroke-width=\"" << this->strokeWidth << "\" fill-opacity=\"" << 0.6 << "\" />" << std::endl;
}

template <typename numberType>
bool CvoronoiCell<numberType>::operator == ( const CvoronoiCell<numberType> &compare ) const
{
	if ( Cell->size() != compare.Cell->size() )
		return false;
	
	typename std::list<Cpoint<numberType> >::iterator it = compare.Cell->begin();
	
	typename std::list<Cpoint<numberType> >::iterator ot = Cell->begin(); 
	
	bool check = false;
	
	while ( (ot != Cell->end()) && (!check) )
	{
		if ( *it == *ot )
			check = true;
		else
			++ot;
	}
	
	if ( !check )
		return false;
	
	typename std::list<Cpoint<numberType> >::iterator cache = ot;
	
	for ( it = compare.Cell->begin(); it != compare.Cell->end(); ++it, ++ot )
	{
		if ( ot == Cell->end() )
			ot = Cell->begin();
			
		if ( *ot != *it )
			check = false;
	}
	
	if ( !check )
	{
		ot = ++cache;
		for ( typename std::list<Cpoint<numberType> >::reverse_iterator ut = compare.Cell->rbegin(); ut != compare.Cell->rend(); ++ut, ++ot )
		{
			if ( ot == Cell->end() )
				ot = Cell->begin();
				
			if ( *ot != *ut )
				return false;
		}
	}
	
	return true;
}

template <typename numberType>
bool CvoronoiCell<numberType>::operator < ( const CvoronoiCell<numberType> &compare ) const
{
	
	if ( Cell->size() < compare.Cell->size() )
	{
		return true;
	}
	
	if ( ( Cell->size() == compare.Cell->size() ) && ( value() < compare.value() ) )
	{
		return true;
	}
	
	return false;
	
}


template <typename numberType>
double CvoronoiCell<numberType>::value() const
{
	double value = 0;
	
	for ( typename std::list<Cpoint<numberType> >::iterator it = Cell->begin(); it != Cell->end(); ++it )
	{
		value+= Cell->size()*sqrt( fabs( it->getX() - Center.getX() )*fabs( it->getX() - Center.getX() ) + fabs( it->getY() - Center.getY() )*fabs( it->getY() - Center.getY() ) );
	}
	
	return 10000*value;
}

template <typename numberType>
void CvoronoiCell<numberType>::colorify()
{
	std::map<double,std::string> color;
	
	
color[	999015	]	 = "rgb(26, 19, 52)";
color[	1076289	]	 = "rgb(38, 41, 74)";
color[	1153563	]	 = "rgb(1, 84, 90)";
color[	2595517	]	 = "rgb(1, 115, 81)";
color[	267685	]	 = "rgb(26, 19, 52)";
color[	288391	]	 = "rgb(38, 41, 74)";
color[	309096	]	 = "rgb(1, 84, 90)";
color[	695467	]	 = "rgb(1, 115, 81)";
color[	1871551	]	 = "rgb(3, 195, 131)";
color[	1549086	]	 = "rgb(170, 217, 98)";
color[	1196725	]	 = "rgb(251, 191, 69)";
color[	1243501	]	 = "rgb(239, 106, 50)";
color[	453112	]	 = "rgb(237, 3, 69)";
color[	1295730	]	 = "rgb(161, 42, 94)";
color[	1425280	]	 = "rgb(113, 1, 98)";
color[	1652097	]	 = "rgb(17, 1, 65)";
color[	1564629	]	 = "rgb(46, 39, 72)";
color[	1683434	]	 = "rgb(58, 61, 94)";
color[	1369149	]	 = "rgb(21, 104, 110)";
color[	1313018	]	 = "rgb(21, 135, 101)";
color[	4587634	]	 = "rgb(23, 215, 151)";
color[	3032875	]	 = "rgb(190, 237, 118)";
color[	1022840	]	 = "rgb(255, 211, 89)";
color[	1100133	]	 = "rgb(255, 23, 89)";
color[	1677928	]	 = "rgb(181, 62, 114)";
color[	387293	]	 = "rgb(133, 21, 118)";
color[	1270640	]	 = "rgb(37, 21, 85)";
color[	670719	]	 = "rgb(66, 59, 92)";
color[	481396	]	 = "rgb(78, 81, 114)";
color[	911304	]	 = "rgb(41, 124, 130)";
color[	864528	]	 = "rgb(41, 155, 121)";
color[	1146407	]	 = "rgb(43, 235, 171)";
color[	960177	]	 = "rgb(210, 255, 138)";
color[	1237823	]	 = "rgb(255, 43, 109)";
color[	1162628	]	 = "rgb(201, 82, 134)";
color[	630613	]	 = "rgb(153, 41, 138)";
color[	809912	]	 = "rgb(57, 41, 105)";
color[	791377	]	 = "rgb(86, 79, 112)";
color[	525120	]	 = "rgb(98, 101, 134)";
color[	747211	]	 = "rgb(61, 144, 150)";
color[	621846	]	 = "rgb(61, 175, 141)";
color[	1452493	]	 = "rgb(63, 255, 191)";
color[	865709	]	 = "rgb(230, 255, 158)";
color[	692557	]	 = "rgb(255, 63, 129)";
color[	940041	]	 = "rgb(221, 102, 154)";
color[	1071212	]	 = "rgb(173, 61, 158)";
color[	1924787	]	 = "rgb(77, 61, 125)";
color[	513385	]	 = "rgb(6, 0, 32)";
color[	1426379	]	 = "rgb(18, 21, 54)";
color[	505248	]	 = "rgb(0, 175, 111)";
color[	1199137	]	 = "rgb(150, 197, 78)";
color[	727091	]	 = "rgb(231, 171, 49)";
color[	735579	]	 = "rgb(219, 86, 30)";
	
	if (color.find(round(value())) == color.end() )
	{
		std::cout << "COLOR NOT FOUND" << std::endl;
	}
	
	this->setFillColor( color[round(value())] );
}



template<typename numberType> numberType CvoronoiCell<numberType>::large = 0;

// SUPPORT FUNCTION ====================================================
template <typename numberType>
double euklid( const Cpoint<numberType>& a, const Cpoint<numberType>& b )
{
	return sqrt( (a.getX()-b.getX())*(a.getX()-b.getX()) + (a.getY()-b.getY())*(a.getY()-b.getY()) );
}

#endif
