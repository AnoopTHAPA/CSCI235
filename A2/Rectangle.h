//Kenndy 6742014

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Coordinate.h"
#include "ShapeTwoD.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Rectangle : public ShapeTwoD
{
	//Friend operator overloader to get rectangle coordinates
	friend istream &operator >>(istream&, Rectangle&);
	
	protected:
		coordinate recCoords [4];
		vector <coordinate> inShape;
		vector <coordinate> onShape;
		int minX;
		int minY;
		int maxX;
		int maxY;
	public:
		//Constructor
		Rectangle(string name, bool containsWarpSpace);
		//Copy Constructor
		Rectangle(const Rectangle &s1);
		//Copy Assignment
		Rectangle& operator =(const Rectangle &s1);

		//Function to print shape info
		virtual string toString();
		//Function to compute and return area
		virtual double computeArea();
		//Function to set area
		virtual void setShapeArea();
		//Function to insert coordinates into recCoords
		void insertCoords(int x1, int y1, int x2, int y2, int x3, int y3,
							int x4, int y4);
		//Function to initialize minX,minY,maxX,maxY
		void initializeMinAndMaxCoord();
		//Function to get onShape size
		int getOnShapeSize();
		//Function to get inShape size
		int getInShapeSize();
		//Function to get recCoords content
		int getRecCoordsContent(int i,bool XorY);
		//Function to get onShape content
		int getOnShapeContent(int i,bool XorY);
		//Function to get inShape content
		int getInShapeContent(int i,bool XorY);
		//Function to populate inShape and onShape
		void getInAndOnShape();
		//Function to determine if x,y is in shape
		bool isPointInShape(int x, int y);
		//Function to determine if x,y is on perimeter
		bool isPointOnShape(int x, int y);
	
		// Destructor
		~Rectangle();
};

#endif
