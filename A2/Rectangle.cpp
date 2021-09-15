//Kenndy 6742014


#include "Rectangle.h"
#include "Coordinate.h"

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

	//Friend operator overload to insert rectangle coords
	istream &operator>>(istream &in, Rectangle& aRec)
	{
		
		for(int i=0; i < 4 ; i++)
		{
			int xValue;
			int yValue;
			cout << "Please enter x-ordinate of pt." << i+1 << " : ";
			in >> aRec.recCoords[i].x;

			cout << "Please enter y-ordinate of pt." << i+1 << " : ";
			in >> aRec.recCoords[i].y;	
			
			cout << endl;
		}
	
		return in;
	}
	
	//Constructor
	Rectangle::Rectangle(string name, bool containsWarpSpace) :
	ShapeTwoD(name,containsWarpSpace)
	{	
		ShapeTwoD::configDone = false;
	}
	
	//Copy Constructor
	Rectangle::Rectangle(const Rectangle &s1) 
	{
		string name = s1.name;
		bool warpSpace = s1.containsWarpSpace;
		
		ShapeTwoD::setName(name);
		ShapeTwoD::setContainsWarpSpace(warpSpace);
		for(int i=0; i < 4 ; i++)
		{
			recCoords[i].x = s1.recCoords[i].x;
			recCoords[i].y = s1.recCoords[i].y;
		}
	}
	
	//Copy Assignment
	Rectangle &Rectangle::operator =(const Rectangle &s1)
	{
		if(this != &s1)
		{
			name  = s1.name;
			containsWarpSpace = containsWarpSpace;
			
			for(int i=0; i < 4 ; i++)
			{
				recCoords[i].x = s1.recCoords[i].x;
				recCoords[i].y = s1.recCoords[i].y;
			}
		}
		return *this;
	}
	
	//to_String() to return vertices, perimeter, and in shape
	string Rectangle::toString()
	{
		
		string shapeInfo;
		shapeInfo += ShapeTwoD::toString();
		
		shapeInfo += "Vertices  : ";
		shapeInfo += "\n";
		for(int i=0; i < 4 ;i++)
		{
			shapeInfo += "Point[" + to_string(i) + "]" + ": (" +
					to_string(recCoords[i].x) + " , " + 
						to_string(recCoords[i].y) + ")" + "\n";
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
	double Rectangle::computeArea()
	{
		int x = recCoords[3].x;
 		int y = recCoords[3].y;
	
		int xWidth, yWidth;
		int xLength, yLength;

		for(int i=0 ; i < 4 ; i++)
		{
			if(recCoords[i].x == x)
			{
				if(recCoords[i].y != y)
				{
					xWidth = recCoords[i].x;
					yWidth = recCoords[i].y;
				}			
			}
			else if(recCoords[i].y == y)
			{
				if(recCoords[i].x != x)
				{
					xLength = recCoords[i].x;
					xWidth = recCoords[i].x;
				}
			}
		}

		double length = abs(x-xLength);
		double width = abs(y-yWidth);
		return length*width;
	}
	
	//Function to set area
	void Rectangle::setShapeArea()
	{
		ShapeTwoD::area = computeArea();
	}
	
	//Function to insert rectangle coords
	void Rectangle::insertCoords(int x1, int y1, int x2, int y2, int x3, 
	int y3, int x4, int y4)
	{
		recCoords[0].x = x1;
		recCoords[0].y = y1;
		
		recCoords[1].x = x2;
		recCoords[1].y = y2;
		
		recCoords[2].x = x3;
		recCoords[2].y = y3;
		
		recCoords[3].x = x4;
		recCoords[3].y = y4;
	}
	
	//Function to initialize minX,minY,maxX,maxY
	void Rectangle::initializeMinAndMaxCoord()
	{
		minX = recCoords[0].x;
		minY = recCoords[0].y;
		
		maxX = recCoords[0].x;
		maxY = recCoords[0].y;
		
		for(int i=0; i < 4 ; i++)
		{
			if(recCoords[i].x < minX)
			{
				minX = recCoords[i].x;
			}
			if(recCoords[i].y < minY)
			{
				minY = recCoords[i].y;
			}
			if(recCoords[i].x > minX)
			{
				maxX = recCoords[i].x;
			}
			if(recCoords[i].y > minY)
			{
				maxY = recCoords[i].y;
			}
		}
	}
	
	//Function to get onShape size
	int Rectangle::getOnShapeSize()
	{
		return onShape.size();
	}
	
	//Function to get inShape size
	int Rectangle::getInShapeSize()
	{
		return inShape.size();
	}
	
	//Function to get content of recCoords at index i
	int Rectangle::getRecCoordsContent(int i, bool XorY)
	{
		//Int i is the counter
		//bool x or y tells us whether its trying to get 
		//x or y, if it's true then its getting x, if false
		//then it's trying to get y
		
		if(XorY)
		{
			return recCoords[i].x;
		}
		else
		{
			return recCoords[i].y;
		}
	}
	
	//Function to get content of onShape at index i
	int Rectangle::getOnShapeContent(int i, bool XorY)
	{
		//Int i is the counter
		//bool x or y tells us whether its trying to get 
		//x or y, if it's true then its getting x, if false
		//then it's trying to get y
		
		if(XorY)
		{
			return onShape[i].x;
		}
		else
		{
			return onShape[i].y;
		}
	}
	
	//Function to get content of inShape at index i
	int Rectangle::getInShapeContent(int i, bool XorY)
	{
		//Int i is the counter
		//bool x or y tells us whether its trying to get 
		//x or y, if it's true then its getting x, if false
		//then it's trying to get y
		
		if(XorY)
		{
			return inShape[i].x;
		}
		else
		{
			return inShape[i].y;
		}
	}
	
	//Function to populate inShape and onShape
	void Rectangle::getInAndOnShape()
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
	
	//Function to determine if x,y is in shape
	bool Rectangle::isPointInShape(int x, int y)
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
	bool Rectangle::isPointOnShape(int x, int y)
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
	
	//Virtual destructor
	Rectangle::~Rectangle()
	{
	
	}
