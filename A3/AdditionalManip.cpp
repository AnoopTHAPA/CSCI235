#include <iostream>
#include <string>

#include "AdditionalManip.h"
using namespace std;

ostream& spacing3(ostream& os)
{
	return (os<< "   ");
}

ostream& spacing4(ostream& os)
{
	return (os<< "    ");
}

ostream& spacing5(ostream& os)
{
	return (os<< "     ");
}

ostream& coordinateFormat(ostream& os)
{
	os.width(4);
	return os;
}
