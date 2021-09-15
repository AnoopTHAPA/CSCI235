#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

#include "AdditionalManip.h"
#include "MyTemplates.h"
#include "Point3D.h"
#include "Line3D.h"

	//Operator overload to print info of Line3D
	ostream &operator <<(ostream& os, Line3D& aLine3D)
	{
		os << "[" << coordinateFormat << aLine3D.pt1.getX() << ", " << 
		coordinateFormat << aLine3D.pt1.getY() << ", "<< coordinateFormat 
		<< aLine3D.pt1.getZ() << "]" << spacing3 ;
		
		os << "[" << coordinateFormat << aLine3D.pt2.getX() << ", " << 
		coordinateFormat << aLine3D.pt2.getY() << ", "<< coordinateFormat 
		<< aLine3D.pt2.getZ() << "]" << spacing3 ;
		
		os << fixed << setprecision(3) << aLine3D.getScalarValue() << endl;
		
		return os;
	}
	
	//Function to calculate and set the length
	void Line3D::setLength()
	{
		double x = pow(pt1.getX() - pt2.getX(), 2);
		double y = pow(pt1.getY() - pt2.getY(), 2);
		double z = pow(pt1.getZ() - pt2.getZ(), 2);
		
		length = sqrt((x+y+z));
	}
	
	//Default Constructr
	Line3D::Line3D()
	{
	
	}
	//Constructor
	Line3D::Line3D(Point3D pt1, Point3D pt2)
	{
		setPt1(pt1);
		setPt2(pt2);
		setLength();
	}
	
	//Operator overload to check if duplicate
	bool Line3D::operator==(Line3D a)
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
	Point3D Line3D::getPt1()
	{
		return pt1;
	}
	
	//Get method for pt2
	Point3D Line3D::getPt2()
	{
		return pt2;
	}
	
	//Set method for pt1
	void Line3D::setPt1(Point3D pt1)
	{
		this->pt1.setX(pt1.getX());
		this->pt1.setY(pt1.getY());
		this->pt1.setZ(pt1.getZ());
	}
	
	//Set method for pt2
	void Line3D::setPt2(Point3D pt2)
	{
		this->pt2.setX(pt2.getX());
		this->pt2.setY(pt2.getY());
		this->pt2.setZ(pt2.getZ());
	}
	
	//Comparator function to sort pt1 in an ascending order
	bool Line3D::comparePt1Ascend(Line3D* a, Line3D* b)
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
			else if(a->pt1.getY() == b->pt1.getY())
			{
				if(a->pt1.getZ() < b->pt1.getZ())
				{
					return true;
				}
				else if(a->pt1.getZ() > b->pt1.getZ())
				{
					return false;
				}
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
	bool Line3D::comparePt2Ascend(Line3D* a, Line3D* b)
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
			else if(a->pt2.getY() == b->pt2.getY())
			{
				if(a->pt2.getZ() < b->pt2.getZ())
				{
					return true;
				}
				else if(a->pt2.getZ() > b->pt2.getZ())
				{
					return false;
				}
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
	bool Line3D::compareLengthAscend(Line3D* a, Line3D* b)
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
	
	//Comparator function to sort pt1 in a descending order
	bool Line3D::comparePt1Descend(Line3D* a, Line3D* b)
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
			else if(a->pt1.getY() == b->pt1.getY())
			{
				if(a->pt1.getZ() > b->pt1.getZ())
				{
					return true;
				}
				else if(a->pt1.getZ() < b->pt1.getZ())
				{
					return false;
				}
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
	bool Line3D::comparePt2Descend(Line3D* a, Line3D* b)
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
			else if(a->pt2.getY() == b->pt2.getY())
			{
				if(a->pt2.getZ() > b->pt2.getZ())
				{
					return true;
				}
				else if(a->pt2.getZ() < b->pt2.getZ())
				{
					return false;
				}
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
	bool Line3D::compareLengthDescend(Line3D* a, Line3D* b)
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



