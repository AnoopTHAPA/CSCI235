//Kenndy 6742014

#ifndef CIRCLE_H
#define CIRCLE_H

#include "Coordinate.h"
#include "ShapeTwoD.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Circle : public ShapeTwoD
{
	//Friend operator overloader to get center coordinate
	//and radius
	friend istream &operator >>(istream&, Circle&);
	
	protected:
		coordinate circleCoord;
		int radius;
		vector <coordinate> inShape;
		vector <coordinate> onShape;
		int minWithinX;
		int minWithinY;
		int maxWithinX;
		int maxWithinY;
	public:
		//Constructor
		Circle(string name, bool containsWarpSpace);
		//Copy constructor
		Circle(const Circle &s1);
		//Copy assignment
		Circle& operator =(const Circle &s1);

		//Function to return shape info
		string toString();
		//Function to compute and return area
		double computeArea();
		//Function to set area
		void setShapeArea();
		//Function to initialize minX,minY,maxX,maxY
		void initializeMinAndMaxCoord();
		//Function to populate inShape and onShape
		void getInAndOnShape();
		//Function to determine if x,y is in shape
		bool isPointInShape(int x, int y);
		//Function to determine if x,y is on perimeter
		bool isPointOnShape(int x, int y);
		
		//Virtual destructor
		~Circle();
	
};

#endif
