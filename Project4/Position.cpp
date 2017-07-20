#include "Position.h"


void Position::add(double tlon, double tlat)
{
	lattitude = tlat;
	longitude = tlon;
}
double Position::operator[](int bin)
{
	if (bin == 1) 
		return lattitude;
	if (bin == 0)
		return longitude;
	else
		return -1;
}
bool Position::operator==(Position p2)
{
	if((lattitude == p2[1])&&(longitude == p2[0]))
		return true;
	else
		return false;
}
Position::Position()
{
	lattitude = 0;
	longitude = 0;
}
Position::Position(double tlon, double tlat)
{
	lattitude = tlat;
	longitude = tlon;
}