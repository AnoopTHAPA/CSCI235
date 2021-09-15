#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

#include "AdditionalManip.h"
#include "Point2D.h"
#include "Point3D.h"

	//Operator overload to print info of Point3D
	ostream &operator<<(ostream &out, Point3D& aPoint3D)
	{
		out << "[" << coordinateFormat << aPoint3D.getX() <<
		", " << coordinateFormat << aPoint3D.getY() << ", " << 
		coordinateFormat << aPoint3D.getZ() << "]" << spacing3 <<
		fixed << setprecision(3) << aPoint3D.getScalarValue() << endl;
		
		return out;
	}
	//Function to compute and set distFrOrigin
	void Point3D::setDistFrOrigin()
	{
		double xPowOf2 = pow((double)x,2.0);
		double yPowOf2 = pow((double)y,2.0);
		double zPowOf2 = pow((double)z,2.0);
		
		distFrOrigin = sqrt((xPowOf2 + yPowOf2 + zPowOf2));
	}
	//Default Constructor
	Point3D::Point3D()
	{
		
	}
	//Constructor
	Point3D::Point3D(int x, int y, int z) :
	Point2D(x, y)
	{
		this->z = z;
		setDistFrOrigin();
	}
	
	//Operator overload to check if duplicate
	bool Point3D::operator ==(Point3D a)
	{
		int x = Point2D::getX(); 
		int y = Point2D::getY();
		int z = getZ();
		
		if(x==a.getX() && y==a.getY() && z==a.getZ())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
	//Get method for z
	int Point3D::getZ()
	{
		return z;
	}
	
	//Set method for z
	void Point3D::setZ(int z)
	{
		this->z = z;
	}
	
	//Comparator function to sort x in an ascending order
	bool Point3D::compareXAscend(Point3D* a, Point3D* b)
	{
		if(a->getX() < b->getX())
		{
			return true;
		}
		else if(a->getX() == b ->getX())
		{
			return compareYAscend(a,b);
		}
		else if(a->getX() > b->getX())
		{
			return false;
		}
	}
	
	//Comparator function to sort y in an ascending order
	bool Point3D::compareYAscend(Point3D* a, Point3D* b)
	{
		if(a->getY() < b->getY())
		{
			return true;
		}
		else if(a->getY() == b->getY())
		{	
			return compareZAscend(a,b);
		}
		else if(a->getY() < b->getY())
		{
			return false;
		}
	}
	
	//Comparator function to sort z in an ascending order
	bool Point3D::compareZAscend(Point3D* a, Point3D* b)
	{
		if(a->getZ() < b->getZ())
		{
			return true;
		}
		else if(a->getZ() == b ->getZ())
		{
			return compareXAscend(a, b);
		}
		else if(a->getZ() > b->getZ())
		{
			return false;
		}
	}
	
	//Comparator function to sort distFrOrigin in an ascending order
	bool Point3D::compareDistFrOriginAscend(Point3D* a, Point3D* b)
	{
		if(a->getScalarValue() <= b->getScalarValue())
		{
			return true;
		}
		else if(a->getScalarValue() > b->getScalarValue())
		{
			return false;
		}
	}
	
	//Comparator function to sort x in a descending order
	bool Point3D::compareXDescend(Point3D* a, Point3D* b)
	{
		if(a->getX() > b->getX())
		{
			return true;
		}
		else if(a->getX() == b ->getX())
		{
			return compareYDescend(a,b);
		}
		else if(a->getX() < b->getX())
		{
			return false;
		}
	}
	
	//Comparator function to sort y in a descending order
	bool Point3D::compareYDescend(Point3D* a, Point3D* b)
	{
		if(a->getY() > b->getY())
		{
			return true;
		}
		else if(a->getY() == b->getY())
		{	
			return compareZDescend(a,b);
		}
		else if(a->getY() < b->getY())
		{
			return false;
		}
	}
	
	//Comparator function to sort z in a descending order
	bool Point3D::compareZDescend(Point3D* a, Point3D* b)
	{
		if(a->getZ() > b->getZ())
		{
			return true;
		}
		else if(a->getZ() == b ->getZ())
		{
			return compareXDescend(a,b);
		}
		else if(a->getZ() < b->getZ())
		{
			return false;
		}
	}
	
	//Comparator function to sort distFrOrigin in a descending order
	bool Point3D::compareDistFrOriginDescend(Point3D* a, Point3D* b)
	{
		if(a->getScalarValue() >= b->getScalarValue())
		{
			return true;
		}
		else if(a->getScalarValue() < b->getScalarValue())
		{
			return false;
		}
	}
