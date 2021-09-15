//Kenndy 6742014


#include "Square.h"
#include "Coordinate.h"

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

	//Friend operator overloader to insert square coords
	istream &operator>>(istream &in, Square& aSquare)
	{
		
		for(int i=0; i < 4 ; i++)
		{
			int xValue;
			int yValue;
			cout << "Please enter x-ordinate of pt." << i+1 << " : ";
			in >> aSquare.squareCoords[i].x;

			cout << "Please enter y-ordinate of pt." << i+1 << " : ";
			in >> aSquare.squareCoords[i].y;	
			
			cout << endl;
		}
	
		return in;
	}

	//Constructor
	Square::Square(string name, bool containsWarpSpace) :
	ShapeTwoD(name,containsWarpSpace)
	{	
		ShapeTwoD::configDone = false;
	}

	//Copy Constructor
	Square::Square(const Square &s1) 
	{
		string name = s1.name;
		bool warpSpace = s1.containsWarpSpace;
		
		ShapeTwoD::setName(name);
		ShapeTwoD::setContainsWarpSpace(warpSpace);
		for(int i=0; i < 4 ; i++)
		{
			squareCoords[i].x = s1.squareCoords[i].x;
			squareCoords[i].y = s1.squareCoords[i].y;
		}
	}
	
	//Copy Assignment
	Square &Square::operator =(const Square &s1)
	{
		if(this != &s1)
		{
			name  = s1.name;
			containsWarpSpace = containsWarpSpace;
			
			for(int i=0; i < 4 ; i++)
			{
				squareCoords[i].x = s1.squareCoords[i].x;
				squareCoords[i].y = s1.squareCoords[i].y;
			}
		}
		return *this;
	}

	//to_String() function to get vertices, perimeter, and in shape
	string Square::toString()
	{
		
		string shapeInfo;
		shapeInfo += ShapeTwoD::toString();
		
		shapeInfo += "Vertices  : ";
		shapeInfo += "\n";
		for(int i=0; i < 4 ;i++)
		{
			shapeInfo += "Point[" + to_string(i) + "]" + ": (" +
					to_string(squareCoords[i].x) + " , " + 
						to_string(squareCoords[i].y) + ")" + "\n";
		}
		
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

	//Function to compute and return area
	double Square::computeArea()
	{
		int x = squareCoords[3].x;
 		int y = squareCoords[3].y;
	
		int xWidth, yWidth;
		int xLength, yLength;

		for(int i=0 ; i < 4 ; i++)
		{
			if(squareCoords[i].x == x)
			{
				if(squareCoords[i].y != y)
				{
					xWidth = squareCoords[i].x;
					yWidth = squareCoords[i].y;
				}			
			}
			else if(squareCoords[i].y == y)
			{
				if(squareCoords[i].x != x)
				{
					xLength = squareCoords[i].x;
					xWidth = squareCoords[i].x;
				}
			}
		}

		double s1 = abs(x-xLength);
		double s2 = abs(y-yWidth);
		return s1*s2;
	}
	
	//Function to set area
	void Square::setShapeArea()
	{
		ShapeTwoD::area = computeArea();
	}
	
	//Function to initialize minX,minY,maxX,maxY
	void Square::initializeMinAndMaxCoord()
	{
		minX = squareCoords[0].x;
		minY = squareCoords[0].y;
		
		maxX = squareCoords[0].x;
		maxY = squareCoords[0].y;
		
		for(int i=0; i < 4 ; i++)
		{
			if(squareCoords[i].x < minX)
			{
				minX = squareCoords[i].x;
			}
			if(squareCoords[i].y < minY)
			{
				minY = squareCoords[i].y;
			}
			if(squareCoords[i].x > minX)
			{
				maxX = squareCoords[i].x;
			}
			if(squareCoords[i].y > minY)
			{
				maxY = squareCoords[i].y;
			}
		}
		
	}
	
	//Function to populate inShape() and onShape()
	void Square::getInAndOnShape()
	{
		initializeMinAndMaxCoord();
		
		
		for(int x=minX ; x <= maxX ; x++)
		{
			for(int y=minY ; y <= maxY ; y++)
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
		
		for(int x=minX ; x <= maxX ; x++)
		{
			for(int y=minY ; y <= maxY ; y++)
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
	}
	
	//Function to determine if x,y is inside shape
	bool Square::isPointInShape(int x, int y)
	{
		if(x > minX && x < maxX)
		{
			if(y > minY && y < maxY)
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
	bool Square::isPointOnShape(int x, int y)
	{
	
		if(x > minX && x < maxX)
		{
			if(y == minY || y == maxY)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if(y > minY && y < maxY)
		{
			if(x == minX || x == maxX)
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
	
	Square::~Square()
	{
	
	}
