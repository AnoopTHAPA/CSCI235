#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iomanip>

#include "MyTemplates.h"
#include "AdditionalManip.h"
#include "Point2D.h"
#include "Point3D.h"
#include "Line2D.h"

using namespace std;

vector <Point2D*> Point2DVector;
vector <Point3D*> Point3DVector;
vector <Line2D*> Line2DVector;
vector <Line3D*> Line3DVector;

static int filterCriteria = 1;
static int sortingCriteria = 1;
static int sortingOrder = 1;

static string filterOption = "Point2D";
static string sortingOption = "x-ordinate";
static string sortOrderOption = "ASC";


void displayMainMenu();
void readFile();
string removeWhiteSpaces(string aLine);

void process2DPoint(string aLine);
void process3DPoint(string aLine);
void process2DLine(string aLine);
void process3DLine(string aLine);

void sortDatas();
void sortPoint2D();
void sortPoint3D();
void sortLine2D();
void sortLine3D();

void setFilteringCriteria();
void setPoint2DSortingCriteria();
void setPoint3DSortingCriteria();
void setLineSortingCriteria();
void setSortingOrder();

void viewData();

void storeData();
void quit();

int main()
{
	displayMainMenu();
}


//Function to print main menu
void displayMainMenu()
{	
	int optionChosen;
	cout << endl << endl;
	cout << "Student ID" << "\t" << ": 6742014" << endl;
	cout << "Student Name" << "\t" << ": Kenndy" << endl;
	cout << "-----------------------------------" << endl;
	
	cout << "Welcome to Assn3 Program " << endl << endl;
	cout << "1)" << "\t" << "Read in data" << endl;
	cout << "2)" << "\t" << "Specify filtering criteria " << 
	"(current : " << filterOption << ")" << endl;
	cout << "3)" << "\t" << "Specify sorting criteria " << 
	"(current : " << sortingOption << ")" << endl;
	cout << "4)" <<	"\t" << "Specify sorting order " << 
	"(current : " << sortOrderOption << ")" << endl;
	cout << "5)" << "\t" <<	"View data" << endl;
	cout << "6)" << "\t" << "Store data" << endl;
	cout << "7)" << "\t" << "Quit" << endl << endl;
	
	cout << "Please enter your choice : ";
	
	cin >> optionChosen;
	
	cout << endl << endl;
	if(optionChosen == 1) 
	{
		readFile();
		sortDatas();
	}
	else if(optionChosen == 2)
	{
		setFilteringCriteria();
		sortDatas();
	}
	else if(optionChosen == 3)
	{
		if(filterCriteria==1)
		{
			setPoint2DSortingCriteria();
		}
		else if(filterCriteria==2)
		{
			setPoint3DSortingCriteria();
		}
		else if(filterCriteria==3 || filterCriteria ==4)
		{
			setLineSortingCriteria();
		}
		sortDatas();	
	}
	else if(optionChosen == 4)
	{
		setSortingOrder();
		sortDatas();
	}
	else if(optionChosen == 5)
	{
		viewData();
	}
	else if(optionChosen == 6)
	{
		storeData();
	}
	else if(optionChosen == 7)
	{
		quit();
	}
	
	displayMainMenu();
}


//Function to read file 
void readFile()
{
	string filename;
	cout << "Please enter filename : ";
	cin >> filename;
	
	ifstream configFileStream;
	configFileStream.open(filename.c_str());
	
	while(configFileStream.good())
	{
		string aLine;
		getline (configFileStream, aLine);
		
		if(!aLine.empty())
		{	
			if(aLine.find("Point2D") != string::npos)
			{
				aLine = removeWhiteSpaces(aLine);
				process2DPoint(aLine);
			}
			else if(aLine.find("Point3D") != string::npos)
			{
				aLine = removeWhiteSpaces(aLine);
				process3DPoint(aLine);
			}
			else if(aLine.find("Line2D") != string::npos)
			{
				aLine = removeWhiteSpaces(aLine);
				process2DLine(aLine);
			}
			if(aLine.find("Line3D") != string::npos)
			{
				aLine = removeWhiteSpaces(aLine);
				process3DLine(aLine);
			}
		}
	}

	int totalPoint2D = Point2DVector.size();
	int totalPoint3D = Point3DVector.size();
	int totalLine2D = Line2DVector.size();
	int totalLine3D = Line3DVector.size();
	
	int total = totalPoint2D + totalPoint3D + totalLine2D + totalLine3D;
	cout << total << " records read in successfully!" << endl;
}

//Function to remove white spaces from string
string removeWhiteSpaces(string aLine)
{
	aLine.erase(std::remove(aLine.begin(), aLine.end(),' '),aLine.end());
	
	return aLine;
}


//Function to process Point2Ds
void process2DPoint(string aLine)
{
	vector<int> coordinates;
	
	size_t pos = 0;
	
	string delimiter = ",";
	string delimiterOpenBracket = "[";
	string delimiterCloseBracket = "]";
	
	int startPOS = aLine.find(delimiterOpenBracket) + 
	delimiterOpenBracket.length();
	int closeBracketPos = aLine.find(delimiterCloseBracket);
	int length = closeBracketPos - startPOS;
	
	aLine = aLine.substr(startPOS,length);
	
	while((pos = aLine.find(delimiter)) != string::npos)
	{
		coordinates.push_back(stoi(aLine.substr(0,pos)));
		aLine.erase(0, pos + delimiter.length());
	}
	coordinates.push_back(stoi(aLine));
	
	bool duplicate = false;
	Point2D* tmp = new Point2D(coordinates[0], coordinates[1]);
	
	for(int i=0; i < Point2DVector.size(); i++)
	{	
		if(equal(*Point2DVector[i], *tmp))
		{
			duplicate = true;
		}
	}
	
	if(!duplicate)
	{
		Point2DVector.push_back(new Point2D(coordinates[0], 
		coordinates[1]));
	}
	delete tmp;
}

//Function to process Point3Ds
void process3DPoint(string aLine)
{
	vector<int> coordinates;
	
	size_t pos = 0;
	
	string delimiter = ",";
	string delimiterOpenBracket = "[";
	string delimiterCloseBracket = "]";
	
	int startPOS = aLine.find(delimiterOpenBracket) + 
	delimiterOpenBracket.length();
	int closeBracketPos = aLine.find(delimiterCloseBracket);
	int length = closeBracketPos - startPOS;
	
	aLine = aLine.substr(startPOS,length);
	
	while((pos = aLine.find(delimiter)) != string::npos)
	{
		coordinates.push_back(stoi(aLine.substr(0,pos)));
		aLine.erase(0, pos + delimiter.length());
	}
	coordinates.push_back(stoi(aLine));
	
	bool duplicate = false;
	Point3D* tmp = new Point3D(coordinates[0], coordinates[1],
	coordinates[2]);
	
	for(int i=0; i < Point3DVector.size(); i++)
	{	
		if(equal(*Point3DVector[i], *tmp))
		{
			duplicate = true;
		}
	}
	
	if(!duplicate)
	{
		Point3DVector.push_back(new Point3D(coordinates[0], 
		coordinates[1],coordinates[2]));
	}
	
	delete tmp;	
}

//Function to process Line2Ds
void process2DLine(string aLine)
{
	vector<int> coordinates1;
	vector<int> coordinates2;
	vector<string> points;
	size_t pos = 0;
	
	string delimiter = ",";
	string delimiter2 = "],";
	string delimiterOpenBracket = "[";
	string delimiterCloseBracket = "]";
	pos = aLine.find(delimiter);
	aLine = aLine.substr(pos+delimiter.length(), aLine.length()-pos);

	
	while((pos = aLine.find(delimiter2)) != string::npos)
	{
		points.push_back(aLine.substr(0,pos));
		aLine.erase(0, pos + delimiter2.length());
	}
	points.push_back(aLine);	
	points[0] += "]";
	
	//Finding x, y of pt 1
	int startPOS = points[0].find(delimiterOpenBracket) + 
	delimiterOpenBracket.length();
	int closeBracketPos = points[0].find(delimiterCloseBracket);
	int length = closeBracketPos - startPOS;
	
	points[0] = points[0].substr(startPOS,length);
	
	while((pos = points[0].find(delimiter)) != string::npos)
	{
		coordinates1.push_back(stoi(points[0].substr(0,pos)));
		points[0].erase(0, pos + delimiter.length());
	}
	coordinates1.push_back(stoi(points[0]));
	
	//Finding x, y of pt2
	startPOS = points[1].find(delimiterOpenBracket) + 
	delimiterOpenBracket.length();
	closeBracketPos = points[1].find(delimiterCloseBracket);
	length = closeBracketPos - startPOS;
	
	points[1] = points[1].substr(startPOS,length);
	
	while((pos = points[1].find(delimiter)) != string::npos)
	{
		coordinates2.push_back(stoi(points[1].substr(0,pos)));
		points[1].erase(0, pos + delimiter.length());
	}
	coordinates2.push_back(stoi(points[1]));
	
	Point2D pt1;
	Point2D pt2;
	pt1.setX(coordinates1[0]);
	pt1.setY(coordinates1[1]);
	
	pt2.setX(coordinates2[0]);
	pt2.setY(coordinates2[1]);
	
	bool duplicate = false;
	Line2D* tmp = new Line2D(pt1,pt2);
	
	for(int i=0; i < Line2DVector.size(); i++)
	{
		if(equal(*Line2DVector[i], *tmp))
		{
			duplicate = true;
		}
	}
	
	if(!duplicate)
	{
		Line2DVector.push_back(new Line2D(pt1,pt2));
	}
	
	delete tmp;
}

//Function to process Line3Ds
void process3DLine(string aLine)
{
	vector<int> coordinates1;
	vector<int> coordinates2;
	vector<string> points;
	size_t pos = 0;
	
	string delimiter = ",";
	string delimiter2 = "],";
	string delimiterOpenBracket = "[";
	string delimiterCloseBracket = "]";
	pos = aLine.find(delimiter);
	aLine = aLine.substr(pos+delimiter.length(), aLine.length()-pos);

	
	while((pos = aLine.find(delimiter2)) != string::npos)
	{
		points.push_back(aLine.substr(0,pos));
		aLine.erase(0, pos + delimiter2.length());
	}
	points.push_back(aLine);	
	points[0] += "]";
	
	//Finding x, y, z of pt 1
	int startPOS = points[0].find(delimiterOpenBracket) + 
	delimiterOpenBracket.length();
	int closeBracketPos = points[0].find(delimiterCloseBracket);
	int length = closeBracketPos - startPOS;
	
	points[0] = points[0].substr(startPOS,length);
	
	while((pos = points[0].find(delimiter)) != string::npos)
	{
		coordinates1.push_back(stoi(points[0].substr(0,pos)));
		points[0].erase(0, pos + delimiter.length());
	}
	coordinates1.push_back(stoi(points[0]));
	
	//Finding x, y, z of pt2
	startPOS = points[1].find(delimiterOpenBracket) + 
	delimiterOpenBracket.length();
	closeBracketPos = points[1].find(delimiterCloseBracket);
	length = closeBracketPos - startPOS;
	
	points[1] = points[1].substr(startPOS,length);
	
	while((pos = points[1].find(delimiter)) != string::npos)
	{
		coordinates2.push_back(stoi(points[1].substr(0,pos)));
		points[1].erase(0, pos + delimiter.length());
	}
	coordinates2.push_back(stoi(points[1]));
	
	Point3D pt1;
	Point3D pt2;
	pt1.setX(coordinates1[0]);
	pt1.setY(coordinates1[1]);
	pt1.setZ(coordinates1[2]);
	
	pt2.setX(coordinates2[0]);
	pt2.setY(coordinates2[1]);
	pt2.setZ(coordinates2[2]);
	
	bool duplicate = false;
	Line3D* tmp = new Line3D(pt1,pt2);
	
	for(int i=0; i < Line3DVector.size(); i++)
	{
		if(equal(*Line3DVector[i], *tmp))
		{
			duplicate = true;
		}
	}
	
	if(!duplicate)
	{
		Line3DVector.push_back(new Line3D(pt1,pt2));
	}
	
	delete tmp;
}

//Function to determine which sort function to use
void sortDatas()
{
	if(filterCriteria==1)
	{
		sortPoint2D();
	}
	else if(filterCriteria==2)
	{
		sortPoint3D();
	}
	else if(filterCriteria==3)
	{
		sortLine2D();
	}
	else if(filterCriteria==4)
	{
		sortLine3D();
	}
}

//Function to sort Point2Ds
void sortPoint2D()
{
	if(sortingOrder==1)
	{
		if(sortingCriteria==1)
		{
			sort(Point2DVector.begin(), Point2DVector.end(),
			Point2D::compareXAscend);
		}
		else if(sortingCriteria==2)
		{
			sort(Point2DVector.begin(), Point2DVector.end(),
			Point2D::compareYAscend);
		}
		else if(sortingCriteria==3)
		{
			sort(Point2DVector.begin(), Point2DVector.end(),
			Point2D::compareDistFrOriginAscend);
		}
	}
	else if(sortingOrder==2)
	{
		if(sortingCriteria==1)
		{
			sort(Point2DVector.begin(), Point2DVector.end(),
			Point2D::compareXDescend);
		}
		else if(sortingCriteria==2)
		{
			sort(Point2DVector.begin(), Point2DVector.end(),
			Point2D::compareYDescend);
		}
		else if(sortingCriteria==3)
		{
			sort(Point2DVector.begin(), Point2DVector.end(),
			Point2D::compareDistFrOriginDescend);
		}
	}
}

//Function to sort Point3Ds
void sortPoint3D()
{
	if(sortingOrder==1)
	{
		if(sortingCriteria==1)
		{
			sort(Point3DVector.begin(), Point3DVector.end(),
			Point3D::compareXAscend);
		}
		else if(sortingCriteria==2)
		{
			sort(Point3DVector.begin(), Point3DVector.end(),
			Point3D::compareYAscend);
		}
		else if(sortingCriteria==3)
		{
			sort(Point3DVector.begin(), Point3DVector.end(),
			Point3D::compareZAscend);
		}
		else if(sortingCriteria==4)
		{
			sort(Point3DVector.begin(), Point3DVector.end(),
			Point3D::compareDistFrOriginAscend);
		}
	}
	else if(sortingOrder==2)
	{
		if(sortingCriteria==1)
		{
			sort(Point3DVector.begin(), Point3DVector.end(),
			Point3D::compareXDescend);
		}
		else if(sortingCriteria==2)
		{
			sort(Point3DVector.begin(), Point3DVector.end(),
			Point3D::compareYDescend);
		}
		else if(sortingCriteria==3)
		{
			sort(Point3DVector.begin(), Point3DVector.end(),
			Point3D::compareZDescend);
		}
		else if(sortingCriteria==4)
		{
			sort(Point3DVector.begin(), Point3DVector.end(),
			Point3D::compareDistFrOriginDescend);
		}
	}
}

//Function to sort Line2Ds
void sortLine2D()
{
	if(sortingOrder==1)
	{
		if(sortingCriteria==1)
		{
			sort(Line2DVector.begin(), Line2DVector.end(),
			Line2D::comparePt1Ascend);
		}
		else if(sortingCriteria==2)
		{
			sort(Line2DVector.begin(), Line2DVector.end(),
			Line2D::comparePt2Ascend);
		}
		else if(sortingCriteria==3)
		{
			sort(Line2DVector.begin(), Line2DVector.end(),
			Line2D::compareLengthAscend);
		}
	}
	else if(sortingOrder==2)
	{
		if(sortingCriteria==1)
		{
			sort(Line2DVector.begin(), Line2DVector.end(),
			Line2D::comparePt1Descend);
		}
		else if(sortingCriteria==2)
		{
			sort(Line2DVector.begin(), Line2DVector.end(),
			Line2D::comparePt2Descend);
		}
		else if(sortingCriteria==3)
		{
			sort(Line2DVector.begin(), Line2DVector.end(),
			Line2D::compareLengthDescend);
		}
	}
}

//Function to sort Line3Ds
void sortLine3D()
{
	if(sortingOrder==1)
	{
		if(sortingCriteria==1)
		{
			sort(Line3DVector.begin(), Line3DVector.end(),
			Line3D::comparePt1Ascend);
		}
		else if(sortingCriteria==2)
		{
			sort(Line3DVector.begin(), Line3DVector.end(),
			Line3D::comparePt2Ascend);
		}
		else if(sortingCriteria==3)
		{
			sort(Line3DVector.begin(), Line3DVector.end(),
			Line3D::compareLengthAscend);
		}
	}
	else if(sortingOrder==2)
	{
		if(sortingCriteria==1)
		{
			sort(Line3DVector.begin(), Line3DVector.end(),
			Line3D::comparePt1Descend);
		}
		else if(sortingCriteria==2)
		{
			sort(Line3DVector.begin(), Line3DVector.end(),
			Line3D::comparePt2Descend);
		}
		else if(sortingCriteria==3)
		{
			sort(Line3DVector.begin(), Line3DVector.end(),
			Line3D::compareLengthDescend);
		}
	}
}

//Function to set filter criteria
void setFilteringCriteria()
{
	string optionChosen;
	
	cout << "[ Specifying filtering criteria (current : " <<
	filterOption << ") ]" << endl << endl;

	cout << "   a)" << "\t" << "Point2D records" << endl;
	cout << "   b)" << "\t" << "Point3D records" << endl;
	cout << "   c)" << "\t" << "Line2D records" << endl;
	cout << "   d)" << "\t" << "Line3D records" << endl << endl;
	
	cout << "   Please enter your criteria(a-d): ";
	cin >> optionChosen;
	
	if(optionChosen.compare("a")==0)
	{
		filterCriteria = 1;
		filterOption = "Point2D";
		
		sortingCriteria = 1;
		sortingOption = "x-ordinate";
		
		cout << "   Filter criteria succesfully set to 'Point2D'!" <<
		endl << endl;
	}
	else if(optionChosen.compare("b")==0)
	{
		filterCriteria = 2;
		filterOption = "Point3D";
		
		sortingCriteria = 1;
		sortingOption = "x-ordinate";
		
		cout << "   Filter criteria succesfully set to 'Point3D'!" <<
		endl << endl;
	}
	else if(optionChosen.compare("c")==0)
	{
		filterCriteria = 3;
		filterOption = "Line2D";
		
		sortingCriteria = 1;
		sortingOption = "Pt. 1";
		
		cout << "   Filter criteria succesfully set to 'Line2D'!" <<
		endl << endl;
	}
	else if(optionChosen.compare("d")==0)
	{
		filterCriteria = 4;
		filterOption = "Line3D";
		
		sortingCriteria = 1;
		sortingOption = "Pt. 1";
		
		cout << "   Filter criteria succesfully set to 'Line3D'!" <<
		endl << endl;
	}
}

//Function to print sorting criteria for Point2D
void setPoint2DSortingCriteria()
{
	string optionChosen;
	
	cout << "[ Specifying sorting criteria (current : " <<
	sortingOption << ") ]" << endl << endl;
	
	cout << "   a)" << "\t" << "X ordinate value" << endl;
	cout << "   b)" << "\t" << "Y ordinate value" << endl;
	cout << "   c)" << "\t" << "Dist. Fr Origin value" << endl << endl;
	
	cout << "   Please enter your criteria(a-c) : ";
	
	cin >> optionChosen;
	
	if(optionChosen.compare("a")==0)
	{
		sortingCriteria = 1;
		sortingOption = "x-ordinate";
		
		cout << "   Sorting criteria succesfully set to 'x-ordinate'!" <<
		endl << endl;
	}
	else if(optionChosen.compare("b")==0)
	{
		sortingCriteria = 2;
		sortingOption = "y-ordinate";
		
		cout << "   Sorting criteria succesfully set to 'y-ordinate'!" <<
		endl << endl;
	}
	else if(optionChosen.compare("c")==0)
	{
		sortingCriteria = 3;
		sortingOption = "Origin distance";
		
		cout << "   Sorting criteria succesfully set to 'Dist. Fr Origin" 
		<< " value'!" << endl << endl;
	}
}

//Function to print sorting criteria for Point3D
void setPoint3DSortingCriteria()
{
	string optionChosen;
	
	cout << "[ Specifying sorting criteria (current : " <<
	sortingOption << ") ]" << endl << endl;
	
	cout << "   a)" << "\t" << "X ordinate value" << endl;
	cout << "   b)" << "\t" << "Y ordinate value" << endl;
	cout << "   c)" << "\t" << "Z ordinate value" << endl;
	cout << "   d)" << "\t" << "Dist. Fr Origin value" << endl << endl;
	
	cout << "   Please enter your criteria(a-d) : ";
	
	cin >> optionChosen;
	
	if(optionChosen.compare("a")==0)
	{
		sortingCriteria = 1;
		sortingOption = "x-ordinate";
		
		cout << "   Sorting criteria succesfully set to 'x-ordinate'!" <<
		endl << endl;
	}
	else if(optionChosen.compare("b")==0)
	{
		sortingCriteria = 2;
		sortingOption = "y-ordinate";
		
		cout << "   Sorting criteria succesfully set to 'y-ordinate'!" <<
		endl << endl;
	}
	else if(optionChosen.compare("c")==0)
	{
		sortingCriteria = 3;
		sortingOption = "z-ordinate";
		
		cout << "   Sorting criteria succesfully set to 'z-ordinate'!" <<
		endl << endl;
	}
	else if(optionChosen.compare("d")==0)
	{
		sortingCriteria = 4;
		sortingOption = "Origin distance";
		
		cout << "   Sorting criteria succesfully set to 'Dist. Fr Origin"
		<< " value'!" << endl << endl;
	}
}

//Function to print sorting criteria for Line2D and Line3D
void setLineSortingCriteria()
{
	string optionChosen;
	
	cout << "[ Specifying sorting criteria (current : " <<
	sortingOption << ") ]" << endl << endl;
	
	cout << "   a)" << "\t" << "Pt. 1's (x, y) values" << endl;
	cout << "   b)" << "\t" << "Pt. 2's (x, y) values" << endl;
	cout << "   c)" << "\t" << "Length value" << endl << endl;
	
	cout << "   Please enter your criteria(a-c) : ";
	
	cin >> optionChosen;
	
	if(optionChosen.compare("a")==0)
	{
		sortingCriteria = 1;
		sortingOption = "Pt. 1";
		
		cout << "   Sorting criteria succesfully set to 'Pt.1's x, y" 
		<< "values'!" << endl << endl;
	}
	else if(optionChosen.compare("b")==0)
	{
		sortingCriteria = 2;
		sortingOption = "Pt. 2";
		
		cout << "   Sorting criteria succesfully set to 'Pt.2's x, y" 
		<< "values'!" << endl << endl;
	}
	else if(optionChosen.compare("c")==0)
	{
		sortingCriteria = 3;
		sortingOption = "Length value";
		
		cout << "   Sorting criteria succesfully set to 'Length'" << endl 
		<< endl;
	}
	else if(optionChosen.compare("d")==0)
	{
		sortingCriteria = 4;
		sortingOption = "Origin distance";
		
		cout << "   Sorting criteria succesfully set to 'Dist. Fr Origin" 
		<< " value'!" << endl << endl;
	}
}

//Function to print sorting order menu
void setSortingOrder()
{
	string optionChosen;
	
	cout << "[ Specifying sorting order (current : " <<
	sortOrderOption << ") ]" << endl << endl;
	
	cout << "   a)" << "\t" << "ASC (Ascending order)" << endl;
	cout << "   b)" << "\t" << "DSC (Descending order)" << endl;
	
	cout << "   Please enter your criteria(a-b) : ";
	
	cin >> optionChosen;
	
	if(optionChosen.compare("a")==0)
	{
		sortOrderOption = "ASC";
		sortingOrder = 1;
		
		cout << "   Sorting order succesfully set to 'ASC'!" << endl 
		<< endl;
	}
	else if(optionChosen.compare("b")==0)
	{
		sortOrderOption = "DSC";
		sortingOrder = 2;
		
		cout << "   Sorting order succesfully set to 'DSC'!" << endl 
		<< endl;
	}
}

//Function to print data of specified filter criteria
void viewData()
{
	if(filterCriteria==1)
	{
		cout << spacing4 << "X" << spacing5 << "Y"
		<< spacing4 << "Dist. Fr Origin" << endl;
		cout << "--------------------------" << endl;
		for(int i=0; i < Point2DVector.size(); i++)
		{
			cout << *Point2DVector[i];
		}
	}
	else if(filterCriteria==2)
	{
		cout << spacing4 << "X" << spacing5 << "Y"
		<< spacing5 << "Z" << spacing4 << "Dist. Fr Origin" << endl;
		cout << "-------------------------------------" << endl;
		for(int i=0; i < Point3DVector.size(); i++)
		{
			cout << *Point3DVector[i];
		}
	}
	else if(filterCriteria==3)
	{
		cout << " " << "P1-X  " << "P1-Y" << spacing5 << "P2-X  " <<
		"P2-Y" << spacing4 << "Length" << endl;
		cout << "-------------------------------------" << endl;
		for(int i=0; i < Line2DVector.size(); i++)
		{
			cout << *Line2DVector[i];
		}
	}
	else if(filterCriteria==4)
	{
		cout << " " << "P1-X  " << "P1-Y  " << "P1-Z" << spacing5 <<
		"P2-X  " << "P2-Y  " << "P2-Z" << spacing4 << "Length" << endl;
		cout << "----------------------------------------------" << endl;
		for(int i=0; i < Line3DVector.size(); i++)
		{
			cout << *Line3DVector[i];
		}
	}
}

//Function to store data of specified criteria
void storeData()
{
	string filename;
	cout << "Please enter file name : ";
	cin >> filename;
	cout << endl;
	
	ofstream outputFile;
	outputFile.open(filename);
	
	if(filterCriteria==1)
	{
		outputFile << spacing4 << "X" << spacing5 << "Y"
		<< spacing4 << "Dist. Fr Origin" << endl;
		outputFile << "--------------------------" << endl;
		for(int i=0; i < Point2DVector.size(); i++)
		{
			outputFile << *Point2DVector[i];
		}
		
		cout << endl << Point2DVector.size() << " records output " <<
		"successfully!";
	}
	else if(filterCriteria==2)
	{
		outputFile << spacing4 << "X" << spacing5 << "Y"
		<< spacing5 << "Z" << spacing4 << "Dist. Fr Origin" << endl;
		outputFile << "-------------------------------------" << endl;
		for(int i=0; i < Point3DVector.size(); i++)
		{
			outputFile << *Point3DVector[i];
		}
		
		cout << endl << Point3DVector.size() << " records output " <<
		"successfully!";
	}
	else if(filterCriteria==3)
	{
		outputFile << " " << "P1-X  " << "P1-Y" << spacing5 << "P2-X  " <<
		"P2-Y" << spacing4 << "Length" << endl;
		outputFile << "-------------------------------------" << endl;
		for(int i=0; i < Line2DVector.size(); i++)
		{
			outputFile << *Line2DVector[i];
		}
		cout << endl << Line2DVector.size() << " records output " <<
		"successfully!";
	}
	else if(filterCriteria==4)
	{
		outputFile << " " << "P1-X  " << "P1-Y  " << "P1-Z" << spacing5 <<
		"P2-X  " << "P2-Y  " << "P2-Z" << spacing4 << "Length" << endl;
		outputFile << "----------------------------------------------" <<
		endl;
		for(int i=0; i < Line3DVector.size(); i++)
		{
			outputFile << *Line3DVector[i];
		}
		cout << endl << Line3DVector.size() << " records output " <<
		"successfully!";
	}
	
	outputFile.close();
	
}

//Function to quit program
void quit()
{
	for(int i=0; i < Point2DVector.size(); i++)
	{
		delete Point2DVector[i];
	}
	for(int i=0; i < Point3DVector.size(); i++)
	{
		delete Point3DVector[i];
	}
	for(int i=0; i < Line2DVector.size(); i++)
	{
		delete Line2DVector[i];
	}
	for(int i=0; i < Line3DVector.size(); i++)
	{
		delete Line3DVector[i];
	}
	cout << "Exiting program" << endl;
	exit(0);
}
