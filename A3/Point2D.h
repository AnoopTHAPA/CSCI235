#ifndef POINT2D_H
#define POINT2D_H

#include <iostream>
#include <string>

using namespace std;

class Point2D
{
	//Operator overload to print info of Point2D
	friend ostream &operator <<(ostream&, Point2D&);
	protected:
		int x;
		int y;
		double distFrOrigin;
		//Function to compute and set distFrOrigin variable
		void setDistFrOrigin();
	public:
		//Default Constructor
		Point2D();
		//Constructor
		Point2D(int x, int y);
		//Operator overload to check if duplicate
		bool operator==(Point2D a);
		//Function to get x
		int getX();
		//Function to get y
		int getY();
		//Function to get distFrOrigin
		double getScalarValue();
		//Function to set x
		void setX(int x);
		//Function to set y
		void setY(int y);
		
		//Comparator function to sort x in an ascending order
		static bool compareXAscend(Point2D* a, Point2D* b);
		//Comparator function to sort y in an ascending order
		static bool compareYAscend(Point2D* a, Point2D* b);
		//Comparator function to sort distFrOrigin in an
		//ascending order
		static bool compareDistFrOriginAscend(Point2D* a, Point2D* b);
		
		//Comparator function to sort x in a descending order
		static bool compareXDescend(Point2D* a, Point2D* b);
		//Comparator function to sort y in a descending order
		static bool compareYDescend(Point2D* a, Point2D* b);
		//Comparator function to sort distFrOrigin in a
		//descending order
		static bool compareDistFrOriginDescend(Point2D* a, Point2D* b);
		
};

#endif
