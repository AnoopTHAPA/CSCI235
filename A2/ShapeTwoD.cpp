//Kenndy 6742014

#include "ShapeTwoD.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

	//Operator overload to determine if area is smaller
	bool ShapeTwoD::operator<(ShapeTwoD* a)
	{
		if(area <= a->area)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
	//Operator overload to determine if area is bigger
	bool ShapeTwoD::operator>(ShapeTwoD* a)
	{
		if(area >= a->area)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
	//Operator overload to determine if containsWarpSpace is true
	bool ShapeTwoD::operator==(bool a)
	{
		if(containsWarpSpace == a)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
	//Default Constructor
	ShapeTwoD::ShapeTwoD()
	{

	}
	
	//Constructor
	ShapeTwoD::ShapeTwoD(string name, bool containsWarpSpace)
	{
		this->name = name;
		this->containsWarpSpace = containsWarpSpace;

	}
	
	//Function to get variable configDone
	bool ShapeTwoD::getConfigDone()
	{
		return configDone;
	}
	
	//Function to set variable configDone
	void ShapeTwoD::setConfig(bool a)
	{
		configDone = a;
	}
	
	//Function to get shape name
	string ShapeTwoD::getName()
	{
		return name;
	}

	//Function to get containsWarpSpace
	bool ShapeTwoD::getContainsWarpSpace()
	{
		return containsWarpSpace;
	}

	//to_String() function to get name, containsWarpSpace, and area
	string ShapeTwoD::toString()
	{
		string s;
		stringstream sStream;
		sStream.setf(ios::fixed);
		sStream.precision(2);
		sStream << area;

		s = sStream.str();	
		string warp = (containsWarpSpace == true) ? "WS" : "NS";
		string shapeInfo = "Shape name : " + name + "\n" + "Special Type : "
							 + warp + "\n" + "Area : " + 
							s + " units square" +  "\n";
		return shapeInfo;
	}

	//Function to compute arae
	double ShapeTwoD::computeArea()
	{
		return 0;
	}

	//Function to get coordinates inShape and onShape
	void ShapeTwoD::getInAndOnShape()
	{
		isPointInShape(0,0);
		isPointOnShape(0,0);
	}
	
	//Function to determine if coordinate is on shape
	bool ShapeTwoD::isPointInShape(int x, int y)
	{
		return false;
	}
	
	//Function to determine if coordinate is on perimeter
	bool ShapeTwoD::isPointOnShape(int x, int y)
	{
		return false;
	}

	//Function to set shape area
	void ShapeTwoD::setShapeArea()
	{
		area = computeArea();
	}
	
	//Function to set shape name
	void ShapeTwoD::setName(string name)
	{
		this-> name = name;
	}

	//Function to set containsWarpSpace
	void ShapeTwoD::setContainsWarpSpace(bool containsWarpSpace)
	{
		this-> containsWarpSpace = containsWarpSpace;
	}
	
	//Virtual destructor
	ShapeTwoD::~ShapeTwoD()
	{
	
	}

