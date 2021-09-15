#ifndef LINE3D_H
#define LINE3D_H

#include <iostream>
#include <string>
#include "Point3D.h"
#include "Line2D.h"

using namespace std;

class Line3D : public Line2D
{
	//Operator overload to print info of Line3D
	friend ostream &operator <<(ostream&, Line3D&);
	private: 
		Point3D pt1;
		Point3D pt2;
	protected:
		//Function to calculate and set the length
		void setLength();
	public:
		//Default Constructor
		Line3D();
		//Constructor
		Line3D(Point3D pt1, Point3D pt2);
		//Operator overload to check if duplicate
		bool operator==(Line3D a);
		//Get method for pt1
		Point3D getPt1();
		//Get method for pt2
		Point3D getPt2();
		//Set method for pt1
		void setPt1(Point3D pt1);
		//Set method for pt2
		void setPt2(Point3D pt2);
		
		//Comparator function to sort pt1 in an ascending order
		static bool comparePt1Ascend(Line3D* a, Line3D* b);
		//Comparator function to sort pt1 in an ascending order
		static bool comparePt2Ascend(Line3D* a, Line3D* b);
		//Comparator function to sort length in an
		//ascending order
		static bool compareLengthAscend(Line3D* a, Line3D* b);
		
		//Comparator function to sort pt1 in a descending order
		static bool comparePt1Descend(Line3D* a, Line3D* b);
		//Comparator function to sort pt1 in a descending order
		static bool comparePt2Descend(Line3D* a, Line3D* b);
		//Comparator function to sort length in a
		//descending order
		static bool compareLengthDescend(Line3D* a, Line3D* b);
};

#endif
