#ifndef POINT3D_H
#define POINT3D_H

#include <iostream>
#include <string>

#include "Point2D.h"
class Point3D : public Point2D
{
	//Operator overload to print info of Point2D
	friend ostream &operator <<(ostream&, Point3D&);
	protected:
		int z;
		void setDistFrOrigin();
	public:
		//Default Constructor
		Point3D();
		//Constructor
		Point3D(int x, int y, int z);
		//Operator overload to check if duplicate
		bool operator==(Point3D a);
		//Get method for z
		int getZ();
		//Set method for z
		void setZ(int z);

		//Comparator function to sort x in an ascending order
		static bool compareXAscend(Point3D* a, Point3D* b);
		//Comparator function to sort y in an ascending order
		static bool compareYAscend(Point3D* a, Point3D* b);
		//Comparator function to sort z in an ascending order
		static bool compareZAscend(Point3D* a, Point3D* b);
		//Comparator function to sort distFrOrigin in an
		//ascending order
		static bool compareDistFrOriginAscend(Point3D* a, Point3D* b);
		
		//Comparator function to sort x in a descending order
		static bool compareXDescend(Point3D* a, Point3D* b);
		//Comparator function to sort y in a descending order
		static bool compareYDescend(Point3D* a, Point3D* b);
		//Comparator function to sort z in a descending order
		static bool compareZDescend(Point3D* a, Point3D* b);
		//Comparator function to sort distFrOrigin in a
		//descending order
		static bool compareDistFrOriginDescend(Point3D* a, Point3D* b);
};

#endif

