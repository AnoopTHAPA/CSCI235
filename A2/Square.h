//Kenndy 6742014

#ifndef SQUARE_H
#define SQUARE_H

#include "Coordinate.h"
#include "ShapeTwoD.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Square : public ShapeTwoD
{
	//Friend operator overload to insert coordinates
	friend istream &operator >>(istream&, Square&);
	protected:
		coordinate squareCoords [4];
		vector <coordinate> inShape;
		vector <coordinate> onShape;
		int minX;
		int minY;
		int maxX;
		int maxY;
	public:
		//Constructor
		Square(string name, bool containsWarpSpace);
		//Copy Constructor
		Square(const Square &s1);
		//Copy Assignment
		Square& operator =(const Square &s1);
		
		//Function to print shape info
		string toString();
		//Function to compute and return area
		double computeArea();
		//Function to set area
		void setShapeArea();
		//Function to determine minX,minY,maxX,maxY
		void initializeMinAndMaxCoord();
		//Function to populate inShape and onShape
		void getInAndOnShape();
		//Function to check if x,y is in shape
		bool isPointInShape(int x, int y);
		//Function to check if x,y in on perimeter
		bool isPointOnShape(int x, int y);
		
		// Destructor
		~Square();
	
};

#endif
