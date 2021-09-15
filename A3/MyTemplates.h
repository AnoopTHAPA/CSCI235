#ifndef MYTEMPLATE_H
#define MYTEMPLATE_H

#include <iostream>
#include <string>

#include "Point2D.h"
#include "Point3D.h"
#include "Line2D.h"
#include "Line3D.h"

using namespace std;

template <typename T> 
double scalar_difference(T a, T b)
{
	double aTmp = a.getScalarValue();
	double bTmp = b.getScalarValue();
	return abs(aTmp-bTmp);
}

template <typename T> 
bool equal(T a, T b)
{
	return a==b;
}


#endif
