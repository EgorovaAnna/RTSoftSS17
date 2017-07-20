#ifndef Position_h
#define Position_h

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>


class Position
{
	double lattitude;
	double longitude;
public:
	void add(double tlat, double tlon);
	double operator[](int bin);
	bool operator==(Position p2);
	int isInMap(Position posmin, Position posmax);
	Position(double tlat, double tlon);
	Position();
};

#endif



