#include "weatherProgram.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <utility>
#include <algorithm>
#include <math.h>

using namespace std;

bool configDone=false;

float xStartGrid;
float xEndGrid;
float yStartGrid;
float yEndGrid;
	
string **grid;
int **cities;
int **clouds;
int **pressure;

int xSize;
int ySize;

int xOffset;
int yOffset;

string citiesList[30];
int numOfCoordinates[30];
int numOfCities;

city *cityArray;


//Main Menu display that prints out 
//option for users to select
void displayMainMenu() 
{
	cout << endl;
	cout << "Student ID" << "\t" << " : 6742014" << endl;
	cout << "Student Name" << "\t" << " : Kenndy" << endl;
	cout << "------------------------------------" <<  
			endl;
	cout << "Welcome to Weather Information Processing System" 
		     << endl << endl;
	cout << "1)" << "\t" << "Read in and process a " <<
	        "configuration file" << endl;
	cout << "2)" << "\t" << "Display city map" << endl; 
	cout << "3)" << "\t" << "Display cloud coverage map " <<
	 	    "(cloudiness index)" << endl;        
	cout << "4)" << "\t" << "Display cloud coverage map " <<
	        "(LMH symbols)" << endl;        
	cout << "5)" << "\t" << "Display atmospheric pressure map "
	         << "(pressure index)" << endl; 
	cout << "6)" << "\t" << "Display atmospheric pressure map "
	         << "(LMH symbols)" << endl; 	
	cout << "7)" << "\t" << "Show weather forecast" 
	         << " summary report" << endl;
	cout << "8)" << "\t" << "Quit" << endl << endl;
	
	int choiceSelected;
	
	cout << "Please enter your choice : " ;   
	cin >> choiceSelected;
	cout << endl;  
	
	if(choiceSelected == 1) 
	{
		readConfigFile();
		displayMainMenu();
	} 
	else if(choiceSelected == 2)
	{
		//This is here to prevent users
		//from choosing option 2-7 before entering config file
		if (configDone!=1)
		{
			cout << "Please enter config file beforehand" << endl;
			displayMainMenu();
		}
		insertCityIntoGrids();
	}
	else if(choiceSelected == 3)
	{
		if (configDone!=1)
		{
			cout << "Please enter config file beforehand" << endl;
			displayMainMenu();
		}
		insertCloudIntoGridsCloudinessIndex();
	}
	else if(choiceSelected == 4)
	{		
		if (configDone!=1)
		{
			cout << "Please enter config file beforehand" << endl;
			displayMainMenu();
		}
		insertCloudIntoGridsCloudinessLMH();
	}
	else if(choiceSelected == 5)
	{		
		if (configDone!=1)
		{
			cout << "Please enter config file beforehand" << endl;
			displayMainMenu();
		}
		insertPressureIntoGridsPressureIndex();
	}
	else if(choiceSelected == 6)
	{		
		if (configDone!=1)
		{
			cout << "Please enter config file beforehand" << endl;
			displayMainMenu();
		}
		insertPressureIntoGridsPressureLMH();
	}
	else if(choiceSelected == 7)
	{		
		if (configDone!=1)
		{
			cout << "Please enter config file beforehand" << endl;
			displayMainMenu();
		}
		displayWeatherSummary();
	}
	else if(choiceSelected == 8) 
	{
		quit();
	}	
	//If user enters an input that is not between
	//1-8, this will show
	else
	{
		cout << "Invalid Option" << endl;
		displayMainMenu();
	}  
	
	cout << endl;
	cin.ignore();
	cout << "Press <enter> to go back to main menu ... " << endl;
	cin.get();
	displayMainMenu();     
}

//This function reads the config file
//for gridX range, gridY range, city file name, 
//cloud file name, and pressure file name
void readConfigFile() 
{
	string delimiter1 = "=";
	string delimiter2 = "-";
	
	//Declares an array to store all the txt file names
	string txtFileNames[3];
	
	//Declares a variable later used to 
	//navigate the txtFileNames array
	int txtArrayPosition = 0;
	
	string configFileName;
	cout << "[ Read in and process a configuration file ]" <<
	        endl;
	cout << "Please enter config filename : ";
	cin >> configFileName;
	
	ifstream configFileStream;
	
	configFileStream.open(configFileName.c_str());
	
	while(configFileStream.good())
	{
		string aLine;
		getline (configFileStream,aLine);
		
		if(!aLine.empty())
		{
			if(aLine.at(0)!='/')
			{
				//Stores Gridx_idxRange=0-8
				//into startX =0 and endX =8
				if(aLine.find("GridX") != string::npos)
				{
					size_t pos =0;
					while((pos = aLine.find(delimiter1)) !=
						string::npos)
					{
						int afterDelimiter = pos + delimiter1.length();
						string coordinatePlaceholder = aLine.substr(afterDelimiter,aLine.length()-afterDelimiter);
						aLine.erase(0,afterDelimiter);
					}
					pos = 0;
					while((pos = aLine.find(delimiter2)) != 
						string::npos)
					{
						xStartGrid = stoi(aLine.substr(0,pos));
						aLine.erase(0,pos+delimiter2.length());
					}
					xEndGrid = stoi(aLine);
				}
				//Stores Gridy_idxRange=0-8
				//into startY =0 and endY=8
				else if(aLine.find("GridY") != string::npos)
				{
					size_t pos =0;
					while((pos = aLine.find(delimiter1)) !=
						string::npos)
					{
						int afterDelimiter = pos + delimiter1.length();
						string coordinatePlaceholder = aLine.substr(afterDelimiter,aLine.length()-afterDelimiter);
						aLine.erase(0,afterDelimiter);
					}
					pos = 0;
					while((pos = aLine.find(delimiter2)) != 
						string::npos)
					{
						yStartGrid = stoi(aLine.substr(0,pos));
						aLine.erase(0,pos+delimiter2.length());
					}
					yEndGrid = stoi(aLine);
				}
				//Stores txt files in the array
				//at first iteration store at txtArrayPosition
				//then at txtArrayPosition+1
				else if(aLine.find(".txt") != string::npos)
				{
					txtFileNames[txtArrayPosition] = aLine;
					txtArrayPosition++;
				}
			}
		}
	}	
	
	//Declare the x size and y size
	//eg 0-8 means 9 size
	xSize = (int)((xEndGrid+0.5) - (xStartGrid-0.5));
	ySize = (int)((yEndGrid+0.5) - (yStartGrid-0.5));
	
	//Value to offset x and y coordinate 
	xOffset = 2- (int)xStartGrid;
	yOffset = 2- (int)yStartGrid;
	
	cout << "Reading in GridX_IdxRange : " << xStartGrid << "-" << xEndGrid << "...done!" << endl;
	cout << "Reading in GridY_IdxRange : " << yStartGrid << "-" << yEndGrid << "...done!" << endl;
	cout << endl;
	//Initialize 2D grid
	initialize2DGridArray();
	
	cout << "Storing data from input file : " << endl;
	
	//Makes and initializes array
	//for storing city, cloud, and pressure value
	make2DCityArray(txtFileNames[0]);
	initialize2DCloudArray(txtFileNames[1]);
	initialize2DPressureArray(txtFileNames[2]);
	
	configFileStream.close();
	configDone = true;
}


//Makes the grid array and initializes it
void initialize2DGridArray() 
{
	grid = new string*[ySize+3];
	for(int i=0; i < ySize+3 ; i++)
	{
		grid[i] = new string[xSize+3];
	}
	
	//Filling in array
	for(int y=0; y < ySize+3 ; y++)
	{
		for(int x=0; x< xSize+3 ; x++)
		{
			if(y==0)
			{
				if(x!=0 && x!=1 && x!=xSize+2) 
				{
					grid[y][x] = to_string(x-2);
				}
			}
			else if(y==1||y==ySize+2) 
			{
				if(x!=0) 
				{
					grid[y][x] = "#";
				}
			}
			else 
			{
				if(x==0)
				{
					grid[y][x] = to_string(y-2);
				}
				else if(x==1||x==xSize+2)
				{
					grid[y][x] = "#";
				}
			}
		}
	}	
}

//Makes 2D city array for storing city as a struct city
void make2DCityArray(string cityFileName) 
{
	
	//Make 2D Cities location array
	cities = new int*[ySize];
	for(int i=0; i < ySize ; i++) 
	{
		cities[i] = new int[xSize];
	}
	
	ifstream cityFileStream;
	cityFileStream.open(cityFileName.c_str());

	numOfCities = 0;
	//Reads the cityfile.txt
	while(cityFileStream.good())
	{
		string aLine;
		getline(cityFileStream,aLine);
		string cityId;

		string delimiter = "-";
		size_t pos = 0;
		
		//Gets city id 
		while((pos = aLine.find(delimiter)) != string::npos)
		{
			cityId = aLine.substr(0,pos);	
			aLine.erase(0,pos + delimiter.length());
		}
		
		//Loops through 30 times (the size of citiesList[])
		//citiesList[] is an array that stores distinct cityIds
		for(int i=0;i<30;i++)
		{
			//If ifstream reads an empty char or whitespace
			//exit loop
			if(cityId == ""||cityId == " "){
				
				i=31;
			}
			//If the current value of citiesList[i] is empty
			//meaning the current cityId is unique
			//store in citiesList
			else if(citiesList[i].compare("")==0)
			{	
				citiesList[i] = cityId;
				//numOfCoordinates[] is an array that stores
				//the number of coordinates (i.e the number of grids)
				//a city has
				numOfCoordinates[i] = 1; 
				
				//A variable that tell us
				//the total number of cities we are gonna process
				numOfCities++;
				i = 31; 
			}
			//If the current value of cityId is a dupe
			//(meaning its already inside citiesList[])
			//we add the number of coordinate that city has
			//by 1 and exit loop
			else if(citiesList[i].compare(cityId)==0)
			{
				
				numOfCoordinates[i]+=1;
				i = 31;
			}
		}			
	}
	
	//Creates a city struct array 
	cityArray = new city [numOfCities];
	
	//Initializes the cityId, and creates the
	//xCoordinate and yCoordinate array to store x,y values for the city
	//xyCoordinateArrayPosition serves as a counter to those arrays
	//and numberOfCoordinates store the amount of grid a city has
	for(int i=0;i<numOfCities;i++) 
	{
		cityArray [i].cityId = citiesList[i];
		int size = numOfCoordinates[i]; 
		cityArray [i].xCoordinate = new int[size];
		cityArray [i].yCoordinate = new int[size];
		cityArray [i].numberOfCoordinates = numOfCoordinates[i];
		cityArray [i].xyCoordinateArrayPosition = 0;
	}
	
	cityFileStream.close();
	
	//Initalizes the xCoordinate and yCoordinate
	initialize2DCityArray(cityFileName);
}

//Used to store x and y to xCoordinate[] and
//yCoordinate[] for each city
void initialize2DCityArray(string cityFileName) 
{

	ifstream cityArrayStream;
	cityArrayStream.open(cityFileName.c_str());
	
	string coordinate;
	string id;
	string size;
	
	int x;
	int y;
	while(cityArrayStream.good()) 
	{
		string aLine;
		getline (cityArrayStream,aLine);
	
		size_t pos =0;
		
		string delimiter = "-";
		
		//If aLine isnt empty
		//seperate the line into x value, y value and cityId
		if(!aLine.empty())
		{
			while((pos = aLine.find(delimiter))!= string::npos)
			{
				coordinate = aLine.substr(0,pos);
				aLine.erase(0,pos+delimiter.length());
				pos =0;
			
				while((pos = aLine.find(delimiter))!=string::npos)
				{
					id = aLine.substr(0,pos);
					aLine.erase(0,pos+delimiter.length());
				}		
			}
			size = aLine;
		
			string delimiter2 = "[";
			string delimiter3 = "]";
			string delimiter4 = ", ";
		
			string coordinate2;
			string coordinate3;
		
	 		size_t pos2 = 0;

	 		while((pos2 = coordinate.find(delimiter2)) != string::npos)
	 		{
	 			coordinate2 = coordinate.erase(0,pos2+1);
	 			pos2=0;
	 		}
	 		while((pos2 = coordinate2.find(delimiter3)) != string::npos)
	 		{
	 			coordinate3 = coordinate2.substr(0,pos2);
	 			coordinate2.erase(0,pos2+delimiter3.length());
	 		}
	 		
	 		while((pos2 = coordinate3.find(delimiter4)) != string::npos)
	 		{
	 			x = stoi(coordinate3.substr(0,pos2));
	 			coordinate3.erase(0,pos2+delimiter4.length());
	 		}	 
	 		y = stoi(coordinate3);
		}
		
		//Loops through all city
		for(int i =0;i<numOfCities;i++) 
		{
			//If city id matches then store x and y coordinate
			//into xCoordinate[] and yCoordinate[]
			if(cityArray[i].cityId.compare(id)==0)
			{
				cityArray[i].citySize=size;
				//xyCoordinateArrayPosition serves as a counter
				//to know which position to store into
				int pos = cityArray[i].xyCoordinateArrayPosition;
				cityArray[i].xCoordinate[pos] = x;
				cityArray[i].yCoordinate[pos] = y;
				
				//Increment xyCoordinateArrayPosition by 1
				//for next use
				cityArray[i].xyCoordinateArrayPosition+=1;
			}
		}
	}

	cout << cityFileName << "...done!" << endl;
	cityArrayStream.close();
	
}

//Insert city into grids
void insertCityIntoGrids()
{
	//These are the real x and y values
	//since the first 2 x and y value on grids are reserved
	//for blank spaces and #
	int xAfterOffset;
	int yAfterOffset;
	
	for(int i=0;i<numOfCities;i++)
	{
		for(int j=0;j<numOfCoordinates[i];j++)
		{
			xAfterOffset = cityArray[i].xCoordinate[j] + xOffset;
			yAfterOffset = cityArray[i].yCoordinate[j] + yOffset;
			
			grid[yAfterOffset][xAfterOffset] = cityArray[i].cityId;
		}
	}
	displayGrid();
}

//Initialized 2D cloud array
void initialize2DCloudArray(string cloudFileName)
{
	//Creates the 2D cloud array
	clouds = new int*[ySize];
	for(int i=0; i < ySize ; i++)
	{
		clouds[i] = new int[xSize];
	}
	
	ifstream cloudFileStream;
	cloudFileStream.open(cloudFileName.c_str());
	
	//Seperates the cloud txt format into
	//x value, y value and cloud value
	while(cloudFileStream.good())
	{
		string aLine;
		getline(cloudFileStream,aLine);
		
		size_t pos =0;
		
		int x;
		int y;
		
		string delimiter = "-";
		string coordinate;
		int cloudValue;
		
		if(!aLine.empty())
		{
			while((pos = aLine.find(delimiter))!= string::npos)
			{
				coordinate = aLine.substr(0,pos);
				aLine.erase(0,pos+delimiter.length());
			}
			cloudValue = stoi(aLine);
					
			string delimiter2 = "[";
			string delimiter3 = "]";
			string delimiter4 = ", ";
		
			string coordinate2;
			string coordinate3;
		
	 		size_t pos2 = 0;

	 		while((pos2 = coordinate.find(delimiter2)) != string::npos)
	 		{
	 			coordinate2 = coordinate.erase(0,pos2+1);
	 			pos2=0;
	 		}
	 		while((pos2 = coordinate2.find(delimiter3)) != string::npos)
	 		{
	 			coordinate3 = coordinate2.substr(0,pos2);
	 			coordinate2.erase(0,pos2+delimiter3.length());
	 		}
	 		
	 		while((pos2 = coordinate3.find(delimiter4)) != string::npos)
	 		{
	 			x = stoi(coordinate3.substr(0,pos2));
	 			coordinate3.erase(0,pos2+delimiter4.length());
	 		}	 
	 		y = stoi(coordinate3);
		
			//Stores the cloud value
			//on the cloud array
	 		clouds[y][x] = cloudValue;
		}
	}
	cout << cloudFileName << "...done!" << endl;
}

//Insert cloud values into grid with cloudiness index
void insertCloudIntoGridsCloudinessIndex()
{
	for(int y=ySize-1; y >= 0; y--)
	{
		for(int x=0; x < xSize; x++)
		{
			int cloudValue = clouds[y][x];
			string cloudiness;
			
			if(cloudValue>=0 && cloudValue<10)
			{
				cloudiness="0";
			}
			else if(cloudValue>=10 && cloudValue<20)
			{
				cloudiness="1";
			}
			else if(cloudValue>=20 && cloudValue<30)
			{
				cloudiness="2";
			}
			else if(cloudValue>=30 && cloudValue<40)
			{
				cloudiness="3";
			}
			else if(cloudValue>=40 &&cloudValue<50)
			{
				cloudiness="4";
			}
			else if(cloudValue>=50 && cloudValue<60)
			{
				cloudiness="5";
			}
			else if(cloudValue>=60 && cloudValue<70)
			{
				cloudiness="6";
			}
			else if(cloudValue>=70 && cloudValue<80)
			{
				cloudiness="7";
			}
			else if(cloudValue>=80 && cloudValue<90)
			{
				cloudiness="8";
			}
			else if(cloudValue>=90 && cloudValue<100)
			{
				cloudiness="9";
			}
			
			//Offsets x and y to account for grid array
			int realX = x + xOffset;
			int realY = y + yOffset;
			grid[realY][realX] = cloudiness;
		}
	}
	displayGrid();
}

//Insert clouds into grid with LMH symbols
void insertCloudIntoGridsCloudinessLMH()
{
	for(int y=ySize-1; y >= 0; y--)
	{
		for(int x=0; x < xSize; x++)
		{
			int cloudValue = clouds[y][x];
			string LMH;
			
			if(cloudValue>=0 && cloudValue<35)
			{
				LMH="L";
			}
			else if(cloudValue>=35 && cloudValue<65)
			{
				LMH="M";
			}
			else if(cloudValue>=65 && cloudValue<100)
			{
				LMH="H";
			}	
			
			//Offsets x and y to account for grid array		
			int realX = x + xOffset;
			int realY = y + yOffset;
			grid[realY][realX] = LMH;
		}
	}
	displayGrid();
}

//Initializes pressure array
void initialize2DPressureArray(string pressureFileName)
{
	//Creates 2D pressure array
	pressure = new int*[ySize];
	for(int i=0; i < ySize ; i++)
	{
		pressure[i] = new int[xSize];
	}
	
	ifstream pressureFileStream;
	pressureFileStream.open(pressureFileName.c_str());
	
	while(pressureFileStream.good())
	{
		string aLine;
		getline(pressureFileStream,aLine);
		
		size_t pos =0;
		
		int x;
		int y;
		
		string delimiter = "-";
		string coordinate;
		int pressureValue;
		
		if(!aLine.empty())
		{
			while((pos = aLine.find(delimiter))!= string::npos)
			{
				coordinate = aLine.substr(0,pos);
				aLine.erase(0,pos+delimiter.length());
			}
			pressureValue = stoi(aLine);
					
			string delimiter2 = "[";
			string delimiter3 = "]";
			string delimiter4 = ", ";
		
			string coordinate2;
			string coordinate3;
		
	 		size_t pos2 = 0;

	 		while((pos2 = coordinate.find(delimiter2)) != string::npos)
	 		{
	 			coordinate2 = coordinate.erase(0,pos2+1);
	 			pos2=0;
	 		}
	 		while((pos2 = coordinate2.find(delimiter3)) != string::npos)
	 		{
	 			coordinate3 = coordinate2.substr(0,pos2);
	 			coordinate2.erase(0,pos2+delimiter3.length());
	 		}
	 		
	 		while((pos2 = coordinate3.find(delimiter4)) != string::npos)
	 		{
	 			x = stoi(coordinate3.substr(0,pos2));
	 			coordinate3.erase(0,pos2+delimiter4.length());
	 		}	 
	 		y = stoi(coordinate3);
	
			//Stores pressure value in the 
			//corresponding x and y on pressure array
	 		pressure[y][x] = pressureValue;
		}
	}
	cout << pressureFileName << "...done!" << endl;
}

//Insert pressure value into grid with pressure index
void insertPressureIntoGridsPressureIndex()
{
	for(int y=ySize-1; y >= 0; y--)
	{
		for(int x=0; x < xSize; x++)
		{
			int pressureValue = pressure[y][x];
			string pressureIndex;
			
			if(pressureValue>=0 && pressureValue<10)
			{
				pressureIndex="0";
			}
			else if(pressureValue>=10 && pressureValue<20)
			{
				pressureIndex="1";
			}
			else if(pressureValue>=20 && pressureValue<30)
			{
				pressureIndex="2";
			}
			else if(pressureValue>=30 && pressureValue<40)
			{
				pressureIndex="3";
			}
			else if(pressureValue>=40 && pressureValue<50)
			{
				pressureIndex="4";
			}
			else if(pressureValue>=50 && pressureValue<60)
			{
				pressureIndex="5";
			}
			else if(pressureValue>=60 && pressureValue<70)
			{
				pressureIndex="6";
			}
			else if(pressureValue>=70 && pressureValue<80)
			{
				pressureIndex="7";
			}
			else if(pressureValue>=80 && pressureValue<90)
			{
				pressureIndex="8";
			}
			else if(pressureValue>=90 && pressureValue<100)
			{
				pressureIndex="9";
			}
			
			//Offsets x and y to account for grid array
			int realX = x + xOffset;
			int realY = y + yOffset;
				
			grid[realY][realX] = pressureIndex;
		}
	}
	displayGrid();
}


//Inserts pressure value into grid with LMH symbols
void insertPressureIntoGridsPressureLMH()
{
	for(int y=ySize-1; y >= 0; y--)
	{
		for(int x=0; x < xSize; x++)
		{
			int pressureValue = pressure[y][x];
			string pressureLMH;
			
			if(pressureValue>=0 && pressureValue<35)
			{
				pressureLMH="L";
			}
			else if(pressureValue>=35 && pressureValue<65)
			{
				pressureLMH="M";
			}
			else if(pressureValue>=65 && pressureValue<100)
			{
				pressureLMH="H";
			}	
			
			//Offsets x and y to account for grid array
			int realX = x + xOffset;
			int realY = y + yOffset;
			grid[realY][realX] = pressureLMH;
		}
	}
	displayGrid();
}

//Display grid 
void displayGrid() 
{
	cout << endl;
	
	for(int y= ySize+2; y >= 0; y--) 
	{
		for(int x=0; x < xSize+3; x++)
		{	
			cout << setw(3) << grid[y][x];
		}
		cout << endl;
	}
	
	//Reset the values inside grid
	//(in this context, values refers to city id, clouds, or pressure)
	initialize2DGridArray();
}

//Initialize the highest x,y as well as
//the lowest x, and y of each city to 
//find their edge
void city::initializeGridValues() 
{
	
	totalSurroundingGrids = 0;
	int maxX;
	int minX;
	int maxY;
	int minY;
	
	//Initialize maxX, minX, maxY, minY
	for(int i=0; i < numberOfCoordinates; i++) 
	{
		if(i==0)
		{
			maxX = xCoordinate[i];
			minX = xCoordinate[i];
			maxY = yCoordinate[i];
			minY = yCoordinate[i];
		}
		else
		{
			if(xCoordinate[i] >= maxX)
				maxX = xCoordinate[i];
			else if(xCoordinate[i] <= minX)
				minX = xCoordinate[i];
			
			if(yCoordinate[i] >= maxY)
				maxY = yCoordinate[i];
			else if(yCoordinate[i] <= minY)
				minY = yCoordinate[i];
		}
	}
	
	//Finds grid values of the city
	findGridValues();
	
	//Finds the grid values of the grids below the city
	findBottomGrids(minY);
	
	//Finds the grid values of the grids on top of the city
	findTopGrids(maxY);
	
	//Finds the grid values of the grids left of the city
	findLeftGrids(minX);
	
	//Finds the grid values of the grids right the city
	findRightGrids(maxX);
	
	//Finds the grid values of the grids diagonal to the city
	findDiagonalGrids(maxX,minX,maxY,minY);
}


void city::findGridValues()
{
	for(int i=0;i<numberOfCoordinates;i++)
	{
		int x = xCoordinate[i];
		int y = yCoordinate[i];
		
		//adds total cloud value inside city to totalCloudValue
		totalCloudValue += clouds[y][x];
		
		//adds total pressure value inside city to totalPressureValue
		totalPressureValue += pressure[y][x];
	}
}

//Finds cloud and pressure value for grids below city
void city::findBottomGrids(int minY)
{
	cout << "cityId " << cityId << "," << minY << endl;
	for(int i=0; i<numberOfCoordinates; i++)
	{
		if(yCoordinate[i]==minY)
		{
			int xBottomGrid = xCoordinate[i];
			int yBottomGrid = yCoordinate[i]-1;
			
			//Checks to see if the grid is within x,y scope
			bool validOrNot = checkGridValidity(xBottomGrid,yBottomGrid);

			if(validOrNot ==1)
			{
				//adds number of valid grid surrounding city by 1
				totalSurroundingGrids += 1;
				
				//adds total cloud value inside city to totalCloudValue
				totalCloudValue += clouds[yBottomGrid][xBottomGrid];
				
				//adds total cloud value inside city to totalPressureValue
				totalPressureValue += pressure[yBottomGrid][xBottomGrid];
			}
		}
	}
}

//Finds cloud and pressure value for grids above city
void city::findTopGrids(int maxY)
{
	for(int i=0; i<numberOfCoordinates; i++)
	{
		if(yCoordinate[i]==maxY)
		{
			int xTopGrid = xCoordinate[i];
			int yTopGrid = yCoordinate[i]+1;
			
			//Checks to see if grid is within x,y scope
			bool validOrNot = checkGridValidity(xTopGrid,yTopGrid);
			
			if(validOrNot ==1)
			{
				//adds number of valid grid surrounding city by 1
				totalSurroundingGrids += 1;
				
				//adds total cloud value inside city to totalCloudValue
				totalCloudValue += clouds[yTopGrid][xTopGrid];
				
				//adds total pressure value inside city to totalPressureValue
				totalPressureValue += pressure[yTopGrid][xTopGrid];
			}
		}
	}
}


//Finds cloud and pressure value for grids left to city
void city::findLeftGrids(int minX)
{
	for(int i=0; i<numberOfCoordinates; i++)
	{
		if(xCoordinate[i]==minX)
		{
			int xLeftGrid = xCoordinate[i]-1;
			int yLeftGrid = yCoordinate[i];
			
			
			//Checks to see if grid is within x,y scope
			bool validOrNot = checkGridValidity(xLeftGrid,yLeftGrid);
			
			if(validOrNot ==1)
			{
				//adds number of valid grid surrounding city by 1
				totalSurroundingGrids += 1;
					
				//adds total cloud value inside city to totalCloudValue
				totalCloudValue += clouds[yLeftGrid][xLeftGrid];
				
				//adds total pressure value inside city to totalPressureValue
				totalPressureValue += pressure[yLeftGrid][xLeftGrid];
			}
		}
	}
}

//Finds cloud and pressure value for grids right of the city
void city::findRightGrids(int maxX)
{
	for(int i=0; i<numberOfCoordinates; i++)
	{
		if(xCoordinate[i]==maxX)
		{
			int xRightGrid = xCoordinate[i]+1;
			int yRightGrid = yCoordinate[i];
			
			
			//Checks if grid is within x,y scope
			bool validOrNot = checkGridValidity(xRightGrid,yRightGrid);
			
			if(validOrNot ==1)
			{
				//adds number of valid grid surrounding city by 1
				totalSurroundingGrids += 1;

				//adds total cloud value inside city to totalCloudValue
				totalCloudValue += clouds[yRightGrid][xRightGrid];
				
				//adds total pressure value inside city to totalPressureValue
				totalPressureValue += pressure[yRightGrid][xRightGrid];
			}
		}
	}
}

void city::findDiagonalGrids(int maxX,int minX, int maxY, int minY)
{
	//Top Right
	int xTopRight = maxX + 1;
	int yTopRight = maxY + 1;
	
	//Top Left
	int xTopLeft = minX - 1;
	int yTopLeft = maxY + 1;
	
	//Bottom Right
	int xBottomRight = maxX + 1;
	int yBottomRight = minY - 1;
	
	//Bottom Left
	int xBottomLeft = minX - 1;
	int yBottomLeft = minY - 1;
	
	//Processing Top Right
	if(checkGridValidity(xTopRight,yTopRight)==1)
	{
		totalSurroundingGrids += 1;
		
		totalCloudValue += clouds[yTopRight][xTopRight];
		totalPressureValue += pressure[yTopRight][xTopRight];
	}
	
	//Processing Top Left
	if(checkGridValidity(xTopLeft,yTopLeft)==1)
	{
		totalSurroundingGrids += 1;
		
		totalCloudValue += clouds[yTopLeft][xTopLeft];
		totalPressureValue += pressure[yTopLeft][xTopLeft];
	}
	
	//Processing Bottom Right
	if(checkGridValidity(xBottomRight,yBottomRight)==1)
	{
		totalSurroundingGrids += 1;
		
		totalCloudValue += clouds[yBottomRight][xBottomRight];
		totalPressureValue += pressure[yBottomRight][xBottomRight];
	}
	
	//Processing Bottom Left
	if(checkGridValidity(xBottomLeft,yBottomLeft)==1)
	{
		totalSurroundingGrids += 1;
		
		totalCloudValue += clouds[yBottomLeft][xBottomLeft];
		totalPressureValue += pressure[yBottomLeft][xBottomLeft];
	}
}

//Checks if a grid is within the limits of the x,y scope
bool city::checkGridValidity(int x,int y)
{	
	if(x>=xStartGrid && x<=xEndGrid)
	{
		if(y>=yStartGrid && y<=yEndGrid)
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


//Prints the weather summary report 
void displayWeatherSummary()
{
	cout << endl;
	
	cout << "Weather Forecast Summary Report" << endl;
	cout << "--------------------------------------------" << endl;
	for(int i=0; i<numOfCities;i++)
	{
		cout << "City Name : " << cityArray[i].citySize << endl;
		cout << "City ID : " << cityArray[i].cityId << endl;
		
		cityArray[i].initializeGridValues();
		
		cout << "test" << endl;
		
		float totalCloud = cityArray[i].totalCloudValue;
		float totalPressure = cityArray[i].totalPressureValue;
		
		float occupiedGrids = (float)cityArray[i].numberOfCoordinates + 
		cityArray[i].totalSurroundingGrids;
		
		//Calculate the average cloud and pressure for the city
		float averageCloud =  totalCloud / occupiedGrids;
		float averagePressure = totalPressure / occupiedGrids;
		
		string LMHCloud = LMHforFinalReport(averageCloud);
		string LMHPressure = LMHforFinalReport(averagePressure);
		
		cout << "Total Cloud = " << totalCloud << ", Total Pressure = " <<
		totalPressure << endl;
		cout << fixed << setprecision(2) << "Ave. Cloud Cover (ACC)" << "\t\t" 
			 << ": " << averageCloud << " (" << LMHCloud << ")" << endl;
		cout << fixed << setprecision(2) << "Ave. Pressure (AP)" << "\t\t" 
			 << ": " << averagePressure << " (" << LMHPressure << ")" << endl;
		cout << "Probability of rain (%) " << "\t" << ": ";
		rainProbability(LMHCloud,LMHPressure);
		cout << "-------------------------------------------" << endl << endl;
		
	}
	
}

//Returns LMH symbol for weather summary report
string LMHforFinalReport(float num) {

	if(num>=0 && num<35)
	{
		return "L";
	}
	else if(num>=35 && num<65)
	{
		return "M";
	}
	else if(num>=65 && num<100)
	{
		return "H";
	}
	
}

//Prints probabilty of rain and rain ASCII art
void rainProbability(string cloud, string pressure) {

	if(pressure.compare("L")==0)
	{
		if(cloud.compare("H")==0)
		{
			cout << "90.00" << endl;
			cout << "~~~~" << endl
				 << "~~~~~" << endl
				 << "\\\\\\\\\\" << endl; 
		}
		else if(cloud.compare("M")==0)
		{
			cout << "80.00" << endl;
			cout << "~~~~" << endl
				 << "~~~~~" << endl
				 << " \\\\\\\\" << endl; 
		}
		else if(cloud.compare("L")==0)
		{
			cout << "70.00" << endl;
			cout << "~~~~" << endl
				 << "~~~~~" << endl
				 << "  \\\\\\" << endl; 
		}
	}
	else if(pressure.compare("M")==0)
	{
		if(cloud.compare("H")==0)
		{
			cout << "60.00" << endl;
			cout << "~~~~" << endl
				 << "~~~~~" << endl
				 << "   \\\\" << endl; 
		}
		else if(cloud.compare("M")==0)
		{
			cout << "50.00" << endl;
			cout << "~~~~" << endl
				 << "~~~~~" << endl
				 << "    \\" << endl; 
		}
		else if(cloud.compare("L")==0)
		{
			cout << "50.00" << endl;
			cout << "~~~~" << endl
				 << "~~~~~" << endl
				 << "     " << endl; 
		}	
	}
	else if(pressure.compare("H")==0)
	{
		if(cloud.compare("H")==0)
		{
			cout << "30.00" << endl;
			cout << "~~~" << endl
				 << "~~~~" << endl
				 << "    " << endl; 
		}
		else if(cloud.compare("M")==0)
		{
			cout << "20.00" << endl;
			cout << "~~" << endl
				 << "~~~" << endl
				 << "    " << endl; 
		}
		else if(cloud.compare("L")==0)
		{
			cout << "10.00" << endl;
			cout << "~" << endl
				 << "~~" << endl
				 << "    " << endl; 
		}
	}
}

//Quits program and deletes all dynamically 
//allocated memories
void quit() {

	cout << "Exiting program" << endl << endl;
	
	//Deleting memory allocated to int ** grid
	for(int j=0; j < ySize+4;j++) 
	{
		delete [] grid[j];
	}
	delete [] grid;
	
	
	//Deleting memory allocated to int **cities
	for(int j=0; j < ySize;j++) 
	{
		delete [] cities[j];
	}
	delete [] cities;
	
	//Deleting memory allocated to int *xCoordinate and int *yCoordinate
	for(int j=0;j<numOfCities;j++)
	{
		delete[] cityArray[j].xCoordinate;
		delete[] cityArray[j].yCoordinate;
	}
	//Deleting city *cityArray
	delete [] cityArray;
	
	
	//Deleting memory allocated to int **clouds
	for(int j=0; j < ySize;j++) 
	{
		delete [] clouds[j];
	}
	delete [] clouds;
	
	//Deleting memory allocated to int **pressure
	for(int j=0; j < ySize;j++) 
	{
		delete [] pressure[j];
	}
	delete [] pressure;
	
	exit(0);
}

