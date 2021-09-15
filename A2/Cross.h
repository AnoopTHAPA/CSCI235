//Kenndy 6742014

#ifndef CROSS_H
#define CROSS_H

#include "Coordinate.h"
#include "ShapeTwoD.h"
#include "Rectangle.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Cross : public ShapeTwoD
{
	friend istream &operator >>(istream&, Cross&);
	protected:
		coordinate crossCoords [12];
		vector <Rectangle*> fiveShape;
		vector <coordinate> inShape;
		vector <coordinate> onShape;
		
		vector <coordinate> bottomCoords;
		vector <coordinate> topCoords;
		vector <coordinate> leftCoords;
		vector <coordinate> rightCoords;
		
		vector <coordinate> cornerCoords;
		int minX;
		int minY;
		int maxX;
		int maxY;
		
		//Coordinates for rectangle 5
		int Rec1x;
		int Rec1y;
		
		int Rec2x;
		int Rec2y;
		
		int Rec3x;
		int Rec3y;
		
		int Rec4x;
		int Rec4y;
	public:
		Cross(string name, bool containsWarpSpace);
		Cross(const Cross &s1);
		Cross& operator =(const Cross &s1);
		
		
		string toString();
		double computeArea();
		void setShapeArea();
		void initializeCoords();
		void populateCoords();
		static bool compareCoordinate(coordinate a, coordinate b);
		void populateCornerCoords();
		void divideInto5Rectangle();
		
		void getInAndOnShape();
		bool isPointInShape(int x, int y);
		bool isPointOnShape(int x, int y);
		
		~Cross();
	
};

#endif
