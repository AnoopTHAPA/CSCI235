//Kenndy 6742014


#include "Circle.h"
#include "Coordinate.h"

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

	//Friend operator overloader to get center coordinate and radius
	istream &operator>>(istream &in, Circle& aCircle)
	{
		
		
		cout << "Please enter x-ordinate of center" << " : ";
		in >> aCircle.circleCoord.x;
		
		cout << "Please enter y-ordinate of center" << " : ";
		in >> aCircle.circleCoord.y;	
		
		cout << endl;
		
		cout << "Please enter radius (units) : " ;
		in >> aCircle.radius;
		
		cout << aCircle.radius;
		
	
		return in;
	}
	
	//Constructor
	Circle::Circle(string name, bool containsWarpSpace) :
	ShapeTwoD(name,containsWarpSpace)
	{	
		ShapeTwoD::configDone = false;
	}
	
	//Copy Constructor
	Circle::Circle(const Circle &s1) 
	{
		string name = s1.name;
		bool warpSpace = s1.containsWarpSpace;
		
		ShapeTwoD::setName(name);
		ShapeTwoD::setContainsWarpSpace(warpSpace);
		
		radius = s1.radius;
		circleCoord.x = s1.circleCoord.x;
		circleCoord.y = s1.circleCoord.y;
		
	}
	
	//Copy assignment
	Circle &Circle::operator =(const Circle &s1)
	{
		if(this != &s1)
		{
			name  = s1.name;
			containsWarpSpace = containsWarpSpace;
			
			radius = s1.radius;
			circleCoord.x = s1.circleCoord.x;
			circleCoord.y = s1.circleCoord.y;
			
		}
		return *this;
	}
	
	//Function to return center, perimeter, and inshape
	string Circle::toString()
	{
		
		string shapeInfo;
		shapeInfo += ShapeTwoD::toString();
		
		shapeInfo += string("Center") + ": (" +
		to_string(circleCoord.x) + " , " + 
		to_string(circleCoord.y) + ")";
		
		shapeInfo += "\n";
		
		shapeInfo += "Points on perimiter : ";
		for(int j=0; j < onShape.size(); j++)
		{
			shapeInfo += "(" + to_string(onShape[j].x) + ", " +
						to_string(onShape[j].y) + ")";
			shapeInfo = (j == onShape.size()-1) ? shapeInfo+= "\n" :
						shapeInfo += ",";
		}
			
		shapeInfo += "\n";
		
		shapeInfo += "Points within shape : ";
		for(int j=0; j < inShape.size(); j++)
		{
			shapeInfo += "(" + to_string(inShape[j].x) + ", " +
						to_string(inShape[j].y) + ")";
			shapeInfo = (j == inShape.size()-1) ? shapeInfo+= "\n" :
						shapeInfo += ",";
		}
		shapeInfo += "\n\n";
		return shapeInfo;
	}
	
	//Function to compute and return area;
	double Circle::computeArea()
	{
		double pi = 2*acos(0.0);
		double area = pi*pow(radius,2);
		
		return area;
	}
	
	//Function to set area
	void Circle::setShapeArea()
	{
		ShapeTwoD::area = computeArea();
	}
	
	//Function to initialize minX,minY,maxX,maxY
	void Circle::initializeMinAndMaxCoord()
	{
		minWithinX = circleCoord.x - (radius-1);
		minWithinY = circleCoord.y - (radius-1);
		
		maxWithinX = circleCoord.x + (radius-1);
		maxWithinY = circleCoord.y + (radius-1);
	}
	
	//Function to populate inShape and onShape
	void Circle::getInAndOnShape()
	{
		initializeMinAndMaxCoord();
		
		for(int x=circleCoord.x-radius; x <= circleCoord.x+radius ; x++)
		{
			for(int y=circleCoord.y-radius; y <= circleCoord.y+radius ; y++)
			{
				if(isPointOnShape(x,y))
				{
					coordinate tmp;
					tmp.x = x;
					tmp.y = y;
					
					onShape.push_back(tmp);
				}
			}
		}
		
		for(int x=minWithinX ; x <= maxWithinX ; x++)
		{
			for(int y=minWithinY ; y <= maxWithinY ; y++)
			{
				if(isPointInShape(x,y))
				{
					coordinate tmp;
					tmp.x = x;
					tmp.y = y;
					
					inShape.push_back(tmp);
				}
			}
		}
	}
	
	//Function to determine if x,y is in shape
	bool Circle::isPointInShape(int x, int y)
	{
		if(x>=minWithinX && x<=maxWithinX)
		{
			if(y>=minWithinX && y <= maxWithinY)
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
	
	//Function to determine if x,y is on perimeter
	bool Circle::isPointOnShape(int x, int y)
	{
		if(x== circleCoord.x + radius || x== circleCoord.x - radius)
		{
			if(y== circleCoord.y)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if(y== circleCoord.y + radius || y== circleCoord.y - radius)
		{
			if(x== circleCoord.x)
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
	
	//Virtual destructor
	Circle::~Circle()
	{
	
	}
