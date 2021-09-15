#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

#include "AdditionalManip.h"
#include "MyTemplates.h"
#include "Point2D.h"
#include "Line2D.h"

using namespace std;
	
	//Operator overload to print info of Line2D
	ostream &operator <<(ostream& os, Line2D& aLine2D)
	{
		os << "[" << coordinateFormat << aLine2D.pt1.getX() << ", " <<
		coordinateFormat << aLine2D.pt1.getY() << "]" << spacing3;
		
		os << "[" << coordinateFormat << aLine2D.pt2.getX() << ", " <<
		coordinateFormat << aLine2D.pt2.getY() << "]" << spacing3;
		
		os << fixed << setprecision(3) << aLine2D.getScalarValue() << endl;
		
		return os;
	}
	
	//Function to calculate and set the length variable
	void Line2D::setLength()
	{
		double x = pow(pt1.getX() - pt2.getX(), 2);
		double y = pow(pt1.getY() - pt2.getY(), 2);
		
		length = sqrt((x+y));
	}
	
	//Default Constructor
	Line2D::Line2D()
	{
	
	}
	
	//Constructor
	Line2D::Line2D(Point2D pt1, Point2D pt2)
	{
		setPt1(pt1);
		setPt2(pt2);
		setLength();
	}
	
	////Operator overload to check if duplicate
	bool Line2D::operator==(Line2D a)
	{
		if(equal(pt1, a.getPt1()))
		{
			if(equal(pt2, a.getPt2()))
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
	
	//Get method for pt1
	Point2D Line2D::getPt1()
	{
		return pt1;
	}
	
	//Get method for pt2
	Point2D Line2D::getPt2()
	{
		return pt2;
	}
	
	//Get method for length
	double Line2D::getScalarValue()
	{
		return length;
	}
	
	//Set method for pt1
	void Line2D::setPt1(Point2D pt1)
	{
		this->pt1.setX(pt1.getX());
		this->pt1.setY(pt1.getY());
	}
	
	//Set method for pt2
	void Line2D::setPt2(Point2D pt2)
	{
		this->pt2.setX(pt2.getX());
		this->pt2.setY(pt2.getY());
	}
	
	//Comparator function to sort pt1 in an ascending order
	bool Line2D::comparePt1Ascend(Line2D* a, Line2D* b)
	{
		if(a->pt1.getX() < b->pt1.getX())
		{
			return true;
		}
		else if(a->pt1.getX() == b->pt1.getX())
		{
			if(a->pt1.getY() < b->pt1.getY())
			{
				return true;
			}
			else if(a->pt1.getY() > b->pt1.getY())
			{
				return false;
			}
		}
		else if(a->pt1.getX() > b->pt1.getX())
		{
			return false;
		}
	}	
	
	//Comparator function to sort pt2 in an ascending order
	bool Line2D::comparePt2Ascend(Line2D* a, Line2D* b)
	{
		if(a->pt2.getX() < b->pt2.getX())
		{
			return true;
		}
		else if(a->pt2.getX() == b->pt2.getX())
		{
			if(a->pt2.getY() < b->pt2.getY())
			{
				return true;
			}
			else if(a->pt2.getY() > b->pt2.getY())
			{
				return false;
			}
		}
		else if(a->pt2.getX() > b->pt2.getX())
		{
			return false;
		}
	}	
	
	//Comparator function to sort length in an ascending order
	bool Line2D::compareLengthAscend(Line2D* a, Line2D* b)
	{
		if(a->getScalarValue() <= b->getScalarValue())
		{
			return true;
		}
		else if(a->getScalarValue() > b-> getScalarValue())
		{
			return false;
		}
	}	
	
	//Comparator function to sort pt1 in a descending order
	bool Line2D::comparePt1Descend(Line2D* a, Line2D* b)
	{
		if(a->pt1.getX() > b->pt1.getX())
		{
			return true;
		}
		else if(a->pt1.getX() == b->pt1.getX())
		{
			if(a->pt1.getY() > b->pt1.getY())
			{
				return true;
			}
			else if(a->pt1.getY() < b->pt1.getY())
			{
				return false;
			}
		}
		else if(a->pt1.getX() < b->pt1.getX())
		{
			return false;
		}
	}	
	
	//Comparator function to sort pt2 in a descending order
	bool Line2D::comparePt2Descend(Line2D* a, Line2D* b)
	{
		if(a->pt2.getX() > b->pt2.getX())
		{
			return true;
		}
		else if(a->pt2.getX() == b->pt2.getX())
		{
			if(a->pt2.getY() > b->pt2.getY())
			{
				return true;
			}
			else if(a->pt2.getY() < b->pt2.getY())
			{
				return false;
			}
		}
		else if(a->pt2.getX() < b->pt2.getX())
		{
			return false;
		}
	}	
	
	//Comparator function to sort length in a descending order
	bool Line2D::compareLengthDescend(Line2D* a, Line2D* b)
	{
		if(a->getScalarValue() >= b->getScalarValue())
		{
			return true;
		}
		else if(a->getScalarValue() < b-> getScalarValue())
		{
			return false;
		}
	}	
