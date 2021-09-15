//Kenndy 6742014


#include "Cross.h"
#include "Coordinate.h"
#include <algorithm>

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

	//Operator overload to insert 12 coordinates
	istream &operator>>(istream &in, Cross& aCross)
	{
		
		for(int i=0; i < 12 ; i++)
		{
			int xValue;
			int yValue;
			cout << "Please enter x-ordinate of pt." << i+1 << " : ";
			in >> aCross.crossCoords[i].x;

			cout << "Please enter y-ordinate of pt." << i+1 << " : ";
			in >> aCross.crossCoords[i].y;	
			
			cout << endl;
		}
	
		return in;
	}

	//Constructor
	Cross::Cross(string name, bool containsWarpSpace) :
	ShapeTwoD(name,containsWarpSpace)
	{
		ShapeTwoD::configDone = false;	
	}

	//Copy Constructor
	Cross::Cross(const Cross &s1) 
	{
		string name = s1.name;
		bool warpSpace = s1.containsWarpSpace;
		
		ShapeTwoD::setName(name);
		ShapeTwoD::setContainsWarpSpace(warpSpace);
		for(int i=0; i < 12 ; i++)
		{
			crossCoords[i].x = s1.crossCoords[i].x;
			crossCoords[i].y = s1.crossCoords[i].y;
		}
	}
	
	//Copy Assignment
	Cross &Cross::operator =(const Cross &s1)
	{
		if(this != &s1)
		{
			name  = s1.name;
			containsWarpSpace = containsWarpSpace;
			
			for(int i=0; i < 12 ; i++)
			{
				crossCoords[i].x = s1.crossCoords[i].x;
				crossCoords[i].y = s1.crossCoords[i].y;
			}
		}
		return *this;
	}

	//to_String function to return vertices, perimeter, and on shape
	string Cross::toString()
	{
		
		string shapeInfo;
		shapeInfo += ShapeTwoD::toString();
		
		shapeInfo += "Vertices  : ";
		shapeInfo += "\n";
		
		for(int i=0; i < 12 ;i++)
		{
			shapeInfo += "Point[" + to_string(i) + "]" + ": (" +
					to_string(crossCoords[i].x) + " , " + 
						to_string(crossCoords[i].y) + ")" + "\n";
		}
		
		shapeInfo += "Points on perimiter : ";
		for(int j=0; j < onShape.size(); j++)
		{
			shapeInfo += "(" + to_string(onShape[j].x) + ", " +
						to_string(onShape[j].y) + ")";
			shapeInfo = (j == onShape.size()-1) ? shapeInfo+= "\n" :
						shapeInfo += ",";
		}
			
		shapeInfo += "\n";
		
		shapeInfo += "Points within shape : ";
		for(int j=0; j < inShape.size(); j++)
		{
			shapeInfo += "(" + to_string(inShape[j].x) + ", " +
						to_string(inShape[j].y) + ")";
			shapeInfo = (j == inShape.size()-1) ? shapeInfo+= "\n" :
						shapeInfo += ",";
		}
		shapeInfo += "\n\n";
		return shapeInfo;
	}

	//Function to compute area
	double Cross::computeArea()
	{
		//Calls initializeCoords to get minX,minY,maxX,maxY
		initializeCoords();
		
		
		//Computes all area of 5 rectangles
		double area1 = fiveShape[0]->computeArea();
		double area2 = fiveShape[1]->computeArea();
		double area3 = fiveShape[2]->computeArea();
		double area4 = fiveShape[3]->computeArea();
		double area5 = fiveShape[4]->computeArea();

		return area1 + area2 + area3 + area4 + area5;
	}
	
	//Function to set area
	void Cross::setShapeArea()
	{
		ShapeTwoD::area = computeArea();
	}
	
	//Function to get minX,minY,maxX,maxY
	void Cross::initializeCoords()
	{
		minX = crossCoords[0].x;
		minY = crossCoords[0].y;
		
		maxX = crossCoords[0].x;
		maxY = crossCoords[0].y;
		
		for(int i=0 ; i < 12; i++)
		{
			if(crossCoords[i].x <= minX)
			{
				minX = crossCoords[i].x;
			}
			else if(crossCoords[i].x > maxX)
			{
				maxX = crossCoords[i].x;
			}
			
			if(crossCoords[i].y <= minY)
			{
				minY = crossCoords[i].y;
			}
			else if(crossCoords[i].y > maxY)
			{
				maxY = crossCoords[i].y;
			}
		}
		//Calls populate coords
		populateCoords();
	}
	
	//Populates vector bottomCoords, topCoords, leftCoords, 
	//and rightCoords
	void Cross::populateCoords()
	{
		//Populate bottom, top, left, and right coords
		for(int i=0; i < 12; i++)
		{
			if(crossCoords[i].y == minY)
			{
				coordinate tmp;
				tmp.x = crossCoords[i].x;
				tmp.y = crossCoords[i].y;
				bottomCoords.push_back(tmp);
			}
			else if(crossCoords[i].y == maxY)
			{
				coordinate tmp;
				tmp.x = crossCoords[i].x;
				tmp.y = crossCoords[i].y;
				topCoords.push_back(tmp);
			}
			else if(crossCoords[i].x == minX)
			{
				coordinate tmp;
				tmp.x = crossCoords[i].x;
				tmp.y = crossCoords[i].y;
				leftCoords.push_back(tmp);
			}
			if(crossCoords[i].x == maxX)
			{
				coordinate tmp;
				tmp.x = crossCoords[i].x;
				tmp.y = crossCoords[i].y;
				rightCoords.push_back(tmp);
			}
		}
		//Sort vector to make sure it stores
		//ascending x and ascending y
		sort(bottomCoords.begin(),bottomCoords.end(),compareCoordinate);
		sort(topCoords.begin(),topCoords.end(),compareCoordinate);
		sort(leftCoords.begin(),leftCoords.end(),compareCoordinate);
		sort(rightCoords.begin(),rightCoords.end(),compareCoordinate);
		
		//Calls function to populate corner vector
		populateCornerCoords();
		
		//Calls function to divide into 5 rectangles
		divideInto5Rectangle();
	}
	
	//Comparator function
	bool Cross::compareCoordinate(coordinate a, coordinate b)
	{
		if(a.x < b.x)
		{
			return true;
		}
		else if(a.x == b.x)
		{
			if(a.y < b.y)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	
	//Populates cornerCoords vector
	void Cross::populateCornerCoords()
	{
		coordinate botLeftCorner, botRightCorner, topLeftCorner ,
					topRightCorner;
		
		botLeftCorner.x = bottomCoords[0].x;
		botLeftCorner.y = leftCoords[0].y;
		
		botRightCorner.x = bottomCoords[1].x;
		botRightCorner.y = rightCoords[0].y;
		
		topLeftCorner.x = topCoords[0].x;
		topLeftCorner.y = leftCoords[1].y;
		
		topRightCorner.x = topCoords[1].x;
		topRightCorner.y = rightCoords[1].y;
		
		cornerCoords.push_back(botLeftCorner);
		cornerCoords.push_back(botRightCorner);
		cornerCoords.push_back(topLeftCorner);
		cornerCoords.push_back(topRightCorner);
	}
	
	//Function divides cross into 5 rectangles(bottom, top, left, right
	//and middle)
	void Cross::divideInto5Rectangle()
	{
		Rec1x = bottomCoords[0].x;
		Rec1y = cornerCoords[1].y;
		
		fiveShape.push_back(new Rectangle("Rectangle1",false));
		fiveShape[0] -> insertCoords(bottomCoords[0].x, bottomCoords[0].y,
		bottomCoords[1].x, bottomCoords[1].y, cornerCoords[1].x,
		cornerCoords[1].y, Rec1x, Rec1y);
		
		Rec2x = cornerCoords[0].x;
		Rec2y = leftCoords[1].y;
		
		fiveShape.push_back(new Rectangle("Rectangle2",false));
		fiveShape[1] -> insertCoords(leftCoords[0].x, leftCoords[0].y,
		leftCoords[1].x, leftCoords[1].y, cornerCoords[0].x, 
		cornerCoords[0].y, Rec2x, Rec2y);
		
		Rec3x = topCoords[1].x;
		Rec3y = cornerCoords[2].y;
		
		fiveShape.push_back(new Rectangle("Rectangle3",false));
		fiveShape[2] -> insertCoords(topCoords[0].x, topCoords[0].y, 
		topCoords[1].x, topCoords[1].y, cornerCoords[2].x, 
		cornerCoords[2].y, Rec3x, Rec3y);
		
		Rec4x = cornerCoords[3].x;
		Rec4y = rightCoords[0].y; 
		
		fiveShape.push_back(new Rectangle("Rectangle4",false));
		fiveShape[3] -> insertCoords(rightCoords[0].x, rightCoords[0].y,
		rightCoords[1].x, rightCoords[1].y, cornerCoords[3].x, 
		cornerCoords[3].y, Rec4x, Rec4y);


		fiveShape.push_back(new Rectangle("Rectangle5",false));
		fiveShape[4] -> insertCoords(Rec1x, Rec1y, Rec2x, Rec2y, Rec3x, 
		Rec3y, Rec4x, Rec4y);
	}
	
	//Function to initialize perimeter and on shape 
	//on cross
	void Cross::getInAndOnShape()
	{
		//For loop to call getInAndOnShape() of each rectangle
		for(int i=0 ; i < 5 ; i++)
		{
			fiveShape[i]-> getInAndOnShape();
		}
		
		for(int i = minX ; i <= maxX ; i++)
		{
			for(int j = minY ; j <= maxY ; j++)
			{
				if(isPointOnShape(i,j))
				{
					coordinate tmp;
					tmp.x = i;
					tmp.y = j;
					onShape.push_back(tmp);
				}
			}
		}
		for(int i = minX ; i <= maxX ; i++)
		{
			for(int j = minY ; j <= maxY ; j++)
			{
				if(isPointInShape(i,j))
				{
					coordinate tmp;
					tmp.x = i;
					tmp.y = j;
					inShape.push_back(tmp);
				}
			}
		}
	}
	
	//Function to determine if a set of x,y 
	//is inside shape
	bool Cross::isPointInShape(int x, int y)
	{
		//If the x and y entered are in the corner
		//return false
		if(x==cornerCoords[0].x && y == cornerCoords[0].y)
		{
			return false;
		}
		
		if(x==cornerCoords[1].x && y == cornerCoords[1].y)
		{
			return false;
		}
		
		if(x==cornerCoords[2].x && y == cornerCoords[2].y)
		{
			return false;
		}
		
		if(x==cornerCoords[3].x && y == cornerCoords[3].y)
		{
			return false;
		}
		
		
		//Checks to see if x,y are inside the area of
		//rectangle 1/2/3/4 or 5, if they are return true
		for(int i = 0; i < 5 ; i++)
		{
			int inShapeSize = fiveShape[i] -> getInShapeSize();
			
			for(int j = 0;j < inShapeSize; j++)
			{
				int x2 = fiveShape[i] -> getInShapeContent(j,true);
				int y2 = fiveShape[i] -> getInShapeContent(j,false);
				
				if(x == x2 && y == y2)
				{
					return true;
				}
			}	
		}
		
		//Checks to see if x,y are in perimeter of rectangle 1 to 5
		//if they are check if they have duplicates, if they have 
		//duplicates return true
		for(int i = 0; i < 5 ; i++)
		{	
			int onShapeSize = fiveShape[i] -> getOnShapeSize();
			
			//Loops through the onShape inside square i
			for(int j=0 ; j < onShapeSize ; j++ ) 
			{
				int x2 = fiveShape[i]->getOnShapeContent(j,true);
				int y2 = fiveShape[i]->getOnShapeContent(j,false);
				
				//Checks to see if x and y are in onShape
				if(x == x2 && y==y2)
				{
					int counter = i+1;
					
					//Loops through square 2 to 4 
					//(Depends on i is, if is 1
					//then check with 2,3,4,5 however if i is 2
					//check with 3,4,5 and so on)
					for(int k = counter ; k < 5 ; k++)
					{
						int size = fiveShape[k] -> getOnShapeSize();
						//Loops through the onShape of square k
						for(int h=0; h < size ; h++)
						{
							int x3 = fiveShape[k]->getOnShapeContent(h, 
									true);
							int y3 = fiveShape[k]->getOnShapeContent(h, 
									false);
							
							//Checks if x,y are duplicates 
							//with other rectangle's onShape()
							if(x==x3 && y == y3)
							{
								return true;
							}
							
							//Checks to see if x,y are duplicates
							//with rectangle 1-4 corners
							for(int w = 0 ; w < 4 ;w++)
							{
								int xCorner = fiveShape[k] -> 
								getRecCoordsContent(w,true);
								int yCorner = fiveShape[k] -> 
								getRecCoordsContent(w,false);
						
								if(x==xCorner && y==yCorner)
								{
									return true;
								}
							}
						}
					}
					return false;
				}
			}
		}
		return false;
	}

	//Function to check if x,y are on perimeter of cross
	bool Cross::isPointOnShape(int x, int y)
	{
		//If the x and y entered are in the corner
		//return false
		if(x==cornerCoords[0].x && y == cornerCoords[0].y)
		{
			return false;
		}
		
		if(x==cornerCoords[1].x && y == cornerCoords[1].y)
		{
			return false;
		}
		
		if(x==cornerCoords[2].x && y == cornerCoords[2].y)
		{
			return false;
		}
		
		if(x==cornerCoords[3].x && y == cornerCoords[3].y)
		{
			return false;
		}
		
		//Checks if rectangle 5 bottom left corner's y
		//is lower than corner 1's y
		if(Rec1y < cornerCoords[0].y)
		{
			if(x==Rec1x && y == Rec1y)
			{
				return true;
			}
		}
		
		//Checks if rectangle 5 top left corner's x
		//is smaller than corner 3's x
		if(Rec2x < cornerCoords[2].x)
		{
			if(x==Rec2x && y == Rec2y)
			{
				return true;
			}
		}
		
		//Checks if rectangle 5 top right corner's y
		//is bigger than corner 4's y
		if(Rec3y > cornerCoords[3].y)
		{
			if(x==Rec3x && y == Rec3y)
			{
				return true;
			}
		}
		
		//Checks if rectangle 5 bot right corner's x
		//is bigger than corner 2's x
		if(Rec4x > cornerCoords[1].x)
		{
			if(x==Rec4x && y == Rec4y)
			{
				return true;
			}
		}
		
		//Checks if x,y are inside rectangle 1-4's onShape()
		//if they are check if they're duplicates, if they are duplicates
		//return false, else return true
		for(int i = 0; i < 4 ; i++)
		{	
			int onShapeSize = fiveShape[i] -> getOnShapeSize();
			
			//Loops through the onShape inside square i
			for(int j=0 ; j < onShapeSize ; j++ ) 
			{
				int x2 = fiveShape[i]->getOnShapeContent(j,true);
				int y2 = fiveShape[i]->getOnShapeContent(j,false);
				
				//Checks to see if x and y are in onShape
				if(x == x2 && y==y2)
				{
					int counter = i+1;
					
					//Loops through square 2 to 4 
					//(Depends on i is, if is 1
					//then check with 2,3,4,5 however if i is 2
					//check with 3,4,5 and so on)
					for(int k = counter ; k < 5 ; k++)
					{
						int size = fiveShape[k] -> getOnShapeSize();
						//Loops through the onShape of square k
						for(int h=0; h < size ; h++)
						{
							int x3 = fiveShape[k]->getOnShapeContent(h, 
									true);
							int y3 = fiveShape[k]->getOnShapeContent(h, 
									false);
							if(x==x3 && y == y3)
							{
								return false;
							}
						}
						//Checks if x,y are corners of 
						//rectangle 1 to 5
						for(int w = 0 ; w < 5 ;w++)
						{
							int xCorner = fiveShape[k] -> 
							getRecCoordsContent(w,true);
							int yCorner = fiveShape[k] -> 
							getRecCoordsContent(w,false);
							
							if(x==xCorner && y==yCorner)
							{
								return false;
							}
						}
					}
					return true;
				}
			}
		}
		
		
		return false;
	}
	
	//Virtual Desctructor
	Cross::~Cross()
	{
		for(int i=0; i < fiveShape.size() ; i++)
		{
			delete fiveShape[i];
		}
	}
