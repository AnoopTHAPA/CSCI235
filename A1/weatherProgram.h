#ifndef WEATHERPROGRAM_H
#define WEATHERPROGRAM_H

#include <iostream>
#include <string>
#include <utility>

using namespace std;

struct city 
{
	int numberOfCoordinates;
	string cityId;
	string citySize;
	int xyCoordinateArrayPosition;
	int *xCoordinate;
	int *yCoordinate;
	

	int totalSurroundingGrids;
	float totalCloudValue;
	float totalPressureValue;
	
	void findGridValues();
	void initializeGridValues();
	void findBottomGrids(int minY);
	void findTopGrids(int maxY);
	void findLeftGrids(int minX);
	void findRightGrids(int maxX);
	
	void findDiagonalGrids(int maxX,int minX,int maxY,int minY);
	bool checkGridValidity(int x,int y);
};

extern string **grid;
extern int **cities;
extern int **clouds;
extern int **pressure;

extern bool configDone;

extern float xStartGrid;
extern float xEndGrid;
extern float yStartGrid;
extern float yEndGrid;

extern int xSize;
extern int ySize;

extern int xOffset;
extern int yOffset;

extern string citiesList[];
extern int numOfCoordinates[];
extern int numOfCities;

extern city *cityArray;

void displayMainMenu();

void readConfigFile();
void initialize2DGridArray();

void make2DCityArray(string cityFileName);
void initialize2DCityArray(string cityFileName);
void insertCityIntoGrids();

void initialize2DCloudArray(string cloudFileName);
void insertCloudIntoGridsCloudinessIndex();
void insertCloudIntoGridsCloudinessLMH();

void initialize2DPressureArray(string pressureFileName);
void insertPressureIntoGridsPressureIndex();
void insertPressureIntoGridsPressureLMH();

string LMHforFinalReport(float num);
void rainProbability(string cloud,string pressure);
void displayWeatherSummary();

void displayGrid();
void quit();

#endif
