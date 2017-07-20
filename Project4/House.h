#ifndef House_h
#define House_h

#include <vector>
#include "Position.h"
#include "Image.h"
using namespace std;

class House
{
	int h;
	vector<Position> corners;
	vector<int*> corInt;
public:
	House(Position tp, int posInt[2]);
	void draw(Image &map, int nh);
	int getPosInt(int bin);
	Position getPos();
	int getLeft();
	int getRight();
	int getUpper();
	int getLower();
	void printAll();
	void paint(Image &map, int nh);
};
#endif