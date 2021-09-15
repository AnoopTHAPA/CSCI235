#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

#include "AdditionalManip.h"
#include "Point2D.h"
using namespace std;

	//Friend operator overload to print info of Point2D 
	ostream &operator<<(ostream &out, Point2D& aPoint2D)
	{
		out << "[" << coordinateFormat << aPoint2D.x <<
		", " << coordinateFormat << aPoint2D.y << "]" << spacing3 <<
		fixed << setprecision(3) << aPoint2D.distFrOrigin << endl;
		
		return out;
	}
	
	//Function to compute and set distFrOrigin variable
	void Point2D::setDistFrOrigin()
	{
		double xPowOf2 = pow((double)x,2.0);
		double yPowOf2 = pow((double)y,2.0);
		
		distFrOrigin = sqrt((xPowOf2 + yPowOf2));
	}
	
	//Default Constructor
	Point2D::Point2D()
	{
	
	}
	
	//Constructor
	Point2D::Point2D(int x, int y)
	{
		this->x = x;
		this->y = y;
		setDistFrOrigin();
	}
	
	//Operator overload for == to check
	//if 2 objects are the same
	bool Point2D::operator==(Point2D a)
	{
		if(x == a.x)
		{
			if(y == a.y)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	
	//Get method for x
	int Point2D::getX()
	{
		return x;
	}
	
	//Get method for y
	int Point2D::getY()
	{
		return y;
	}
	
	//Get method for distFrOrigin
	double Point2D::getScalarValue()
	{
		return distFrOrigin;
	}
	
	//Set method for x
	void Point2D::setX(int x)
	{
		this->x = x;
	}
	
	//Set method for y
	void Point2D::setY(int y)
	{
		this->y = y;
	}
	
	//Comparator function to sort x in an ascending manner
	bool Point2D::compareXAscend(Point2D* a, Point2D* b)
	{
		if(a->x < b->x)
		{
			return true;
		}
		else if(a->x == b->x)
		{
			return compareYAscend(a,b);
		}
		else if(a->x > b->x)
		{
			return false;
		}
	}
	
	//Comparator function to sort y in an ascending manner
	bool Point2D::compareYAscend(Point2D* a, Point2D* b)
	{
		if(a->y < b->y)
		{
			return true;
		}
		else if(a->y == b->y)
		{
			return compareXAscend(a,b);
		}
		else if(a->y > b->y)
		{
			return false;
		}
	}
	
	//Comparator function to sort distFrOrigin in an ascending manner
	bool Point2D::compareDistFrOriginAscend(Point2D* a, Point2D* b)
	{
		double aDist = a->getScalarValue();
		double bDist = b->getScalarValue();
		
		if(aDist <= bDist)
		{
			return true;
		}
		else if(aDist > bDist)
		{
			return false;
		}
	}
	
	//Comparator function to sort x in a descending manner
	bool Point2D::compareXDescend(Point2D* a, Point2D* b)
	{
		if(a->x > b->x)
		{
			return true;
		}
		else if(a->x == b->x)
		{
			return compareYDescend(a,b);
		}
		else if(a->x < b->x)
		{
			return false;
		}
	}
	
	//Comparator function to sort y in a descending manner
	bool Point2D::compareYDescend(Point2D* a, Point2D* b)
	{
		if(a->y > b->y)
		{
			return true;
		}
		else if(a->y == b->y)
		{
			return compareXDescend(a,b);
		}
		else if(a->y < b->y)
		{
			return false;
		}
	}
	
	//Comparator function to sort y in a descending manner
	bool Point2D::compareDistFrOriginDescend(Point2D* a, Point2D* b)
	{
		double aDist = a->getScalarValue();
		double bDist = b->getScalarValue();
		
		if(aDist >= bDist)
		{
			return true;
		}
		else if(aDist < bDist)
		{
			return false;
		}
	}

