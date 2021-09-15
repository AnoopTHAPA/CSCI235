#ifndef LINE2D_H
#define LINE2D_H

#include <iostream>
#include <string>
#include "Point2D.h"

using namespace std;

class Line2D
{
	//Operator overload to print info of Line2D
	friend ostream &operator <<(ostream&, Line2D&);
	private:
		Point2D pt1;
		Point2D pt2;
	protected:
		double length;
		//Function to calculate and set the length
		void setLength();
	public:
		//Default Constructor
		Line2D();
		//Constructor
		Line2D(Point2D pt1, Point2D pt2);
		//Operator overload to check if duplicate
		bool operator==(Line2D a);
		//Get method for pt1
		Point2D getPt1();
		//Get method for pt2
		Point2D getPt2();
		//Get method for length
		double getScalarValue();
		//Set method for pt1
		void setPt1(Point2D pt1);
		//Set method for pt2
		void setPt2(Point2D pt2);
		
		//Comparator function to sort pt1 in an ascending order
		static bool comparePt1Ascend(Line2D* a, Line2D* b);
		//Comparator function to sort pt1 in an ascending order
		static bool comparePt2Ascend(Line2D* a, Line2D* b);
		//Comparator function to sort length in an
		//ascending order
		static bool compareLengthAscend(Line2D* a, Line2D* b);
		
		//Comparator function to sort pt1 in a descending order
		static bool comparePt1Descend(Line2D* a, Line2D* b);
		//Comparator function to sort pt1 in a descending order
		static bool comparePt2Descend(Line2D* a, Line2D* b);
		//Comparator function to sort length in a
		//descending order
		static bool compareLengthDescend(Line2D* a, Line2D* b);
		

};

#endif
