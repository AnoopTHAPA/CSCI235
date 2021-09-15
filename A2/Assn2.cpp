//Kenndy 6742014

#include "Coordinate.h"
#include "ShapeTwoD.h"
#include "Square.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Cross.h"

#include <algorithm>
#include <vector>
#include <iostream>
#include <string>


using namespace std;

vector <ShapeTwoD*> shapeList;

ShapeTwoD* shapeWow [4];
int numberOfWS = 0;

void printMenu();
void processChoice(int x);
void createShape();
string formatString(string x);
void computeArea();
void printInfo();
void sortOptions();
void sortAscend();
void sortDescend();
void sortType();
bool compareAscend(ShapeTwoD* ptr1, ShapeTwoD* ptr2);
bool compareDescend(ShapeTwoD* ptr1, ShapeTwoD* ptr2);
bool compareType(ShapeTwoD* ptr1, ShapeTwoD* ptr2);
void quit();

int main() 
{
	printMenu();
	cout << endl;
	return 0;
}

//Main menu function
void printMenu()
{
	int numberChosen;
	cout<< endl;
	cout << "Student ID" << "\t" << " : 6742014" << endl;
	cout << "Student Name" << "\t" << " : Kenndy" << endl;
	cout << "-------------------------------------------" << endl;

	cout << "Welcome to Assn2 Program!" << endl << endl;
	cout << "1)" << "\t" << "Input sensor data" << endl;
	cout << "2)" << "\t" << "Compute area(for all records)" << endl;
	cout << "3)" << "\t" << "Print shapes report" << endl;
	cout << "4)" << "\t" << "Sort shape data" << endl;
	cout << "5)" << "\t" << "Quit" << endl;
	cout << endl;
	cout << "Please enter your choice : ";
	cin >> numberChosen;
	
	cout << endl << endl;
	processChoice(numberChosen);

	printMenu();
}

//Function to process the choice inserted by user
//different functions will be called dependending on the input
void processChoice(int x)
{
	if(x==1)
	{
		createShape();
	}
	else if(x==2)
	{
		computeArea();
	}
	else if(x==3)
	{
		printInfo();
	}
	else if(x==4)
	{
		sortOptions();
	}
	else if(x==5)
	{
		quit();
	}
}

//Function to create shape based on user input
void createShape() 
{
	string shapeName;
	string specialType;

	cout << "[ Input sensor data ] " << endl;	
	cout << "Please enter name of shape : ";
	cin >> shapeName;

	cout << "Please enter special type : ";
	cin >> specialType;

	shapeName = formatString(shapeName);
	specialType = formatString(specialType);
	
	bool warpSpace;

	if(specialType.compare("WS")==0)
	{
		warpSpace = true;
		numberOfWS++;
	}
	else if(specialType.compare("NS")==0)
	{
		warpSpace = false;
	}
	else 
	{
		cout << "Please enter the appropriate special type! " << endl;
		printMenu();
	}
	
	
	if(shapeName.compare("SQUARE")==0)
	{
		Square* square = new Square("Square",warpSpace);
		cin >> *square;
		shapeList.push_back(new Square(*square));
		delete square;
		
		cout << "Record successfully stored. Going back to main menu .. " 
		<<  endl;
	}
	else if(shapeName.compare("RECTANGLE")==0)
	{
		Rectangle* rectangle = new Rectangle("Rectangle",warpSpace);
		cin >> *rectangle;
		shapeList.push_back(new Rectangle(*rectangle));
		delete rectangle;
		
		cout << "Record successfully stored. Going back to main menu .. " 
		<<  endl;
	}
	else if(shapeName.compare("CIRCLE")==0)
	{
		Circle* circle = new Circle("Circle",warpSpace);
		cin >> *circle;
		shapeList.push_back(new Circle(*circle));
		delete circle;
		
		cout << "Record successfully stored. Going back to main menu .. " 
		<<  endl;
	}
	else if(shapeName.compare("CROSS")==0)
	{
		Cross* cross = new Cross("Cross",warpSpace);
		cin >> *cross;
		shapeList.push_back(new Cross(*cross));
		delete cross;
		
		cout << "Record successfully stored. Going back to main menu .. " 
		<<  endl;
	}
	else
	{
		cout << "Please enter the appropriate shape! " << endl;
	}
	
	
}

//Function to format user input
//(delete all whitespaces and turn strings to capital letters)
string formatString(string x)
{
	x.erase(std::remove(x.begin(), x.end(),' '),x.end());

	for(int i=0; i< x.size(); i++)
	{
		x.at(i) = toupper(x.at(i));
	}
	return x;
}

//Function to call computeArea() in their respective shape
void computeArea()
{
	for(int i=0; i < shapeList.size() ; i++)
	{
		bool tmp = shapeList[i] -> getConfigDone();
		if(!tmp)
		{
			shapeList[i] -> setShapeArea();
			shapeList[i] -> getInAndOnShape();
			shapeList[i] -> setConfig(true);
		}
	}	
	cout << "Computation completed! ( " << 
			shapeList.size() << " records were updated )" << endl;	
}

//Function to call toString() in their respective shape
void printInfo()
{
	for(int i=0; i < shapeList.size() ; i++)
	{
		cout << "Shape [" << i << "]" << endl;
		string tmp = shapeList[i]-> toString();
		cout << tmp;
	}	
}

//Function to display sorting options
void sortOptions()
{
	string chosen;
	cout << endl;
	cout << "\t" << "a)" << "\t" << "Sort by area (ascending)" << endl;
	cout << "\t" << "b)" << "\t" << "Sort by area (descending)" << endl;
	cout << "\t" << "c)" << "\t" << "Sort by special type and area" << 
			endl << endl;
	
	cout << "Please select sort option('q' to go to main menu) : ";

	cin >> chosen;
	
	chosen = formatString(chosen);
	cout << endl << endl;
	
	if(chosen.compare("A")==0)
	{
		sortAscend();
	}
	else if(chosen.compare("B")==0)
	{
		sortDescend();
	}
	else if(chosen.compare("C")==0)
	{
		sortType();
	}
	
	
}

//Function to sort shape ascending by area
void sortAscend()
{	
	sort(shapeList.begin(), shapeList.end(),compareAscend);
	printInfo();
}

//Function to sort shape descending by area
void sortDescend()
{
	sort(shapeList.begin(), shapeList.end(),compareDescend);
	printInfo();
}

//Function to sort shape by special type and area
void sortType()
{	
	sort(shapeList.begin(), shapeList.end(),compareType);
	sort(shapeList.begin(), shapeList.begin()+
			(numberOfWS),compareDescend);
	sort(shapeList.begin() + (numberOfWS), shapeList.end()
			,compareDescend);
	printInfo();
}

//Comparator function for sorting ascendingly
bool compareAscend(ShapeTwoD* ptr1, ShapeTwoD* ptr2)
{
	return *ptr1 < ptr2;
}

//Comparator function for sorting descendingly
bool compareDescend(ShapeTwoD* ptr1, ShapeTwoD* ptr2)
{
	return *ptr1 > ptr2;
}

//Comparator function for sorting by type
bool compareType(ShapeTwoD* ptr1, ShapeTwoD* ptr2)
{
	return (*ptr1 == 1);
}

//Function to delete all dynamically created objects and
//exit program
void quit()
{
	for(int i=0; i < shapeList.size() ; i++)
	{	
		delete shapeList[i];
	}
	
	exit(0);
}
