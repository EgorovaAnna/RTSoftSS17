#ifndef Image_h
#define Image_h

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include "Point.h"

class Image
{
	Point **image;
	int sizeI[2];
public:
	Image(int *tsize);
	int getX();
	int getY();
	int getTag(int x, int y);
	void loadIm(std::ifstream &fin);
	void paintAll(int color);
	void drawPoint(int x1, int x2, int color, int nh);
	void drawPoint(int x, int y, int color);
	void drawLine(int x1, int x2, int y1, int y2, int nh);
	void showFile(std::string fl);
	void paint();
};

#endif
