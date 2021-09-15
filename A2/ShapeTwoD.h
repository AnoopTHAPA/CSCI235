//Kenndy 6742014

#ifndef SHAPETWOD_H
#define SHAPETWOD_H

#include <iostream>
#include <string>

using namespace std;

class ShapeTwoD
{
	protected:
		string name;
		bool containsWarpSpace;
		double area;
		
		//Variable to determine if area, onShape, and inShape
		//has been initialized
		bool configDone; 
	public:
		//Operator overload to compare area (returns true if smaller)
		bool operator<(ShapeTwoD* a);
		
		//Operator overload to compare area (returns true if bigger)
		bool operator>(ShapeTwoD* a);
		
		//Operator overload to determine warp space (returns true if 
		//containsWarpSpace is true)
		bool operator==(bool a);
		ShapeTwoD();
		ShapeTwoD(string name, bool containsWarpSpace);
		
		
		bool getConfigDone();
		void setConfig(bool a);
		string getName();
		bool getContainsWarpSpace();
		

		virtual string toString();
		virtual double computeArea();
		
		virtual void getInAndOnShape();
		virtual bool isPointInShape(int x, int y);
		virtual bool isPointOnShape(int x, int y);

		virtual void setShapeArea();
		void setName(string name);
		void setContainsWarpSpace(bool containsWarpSpace);	
		
		virtual ~ShapeTwoD();
};

#endif
