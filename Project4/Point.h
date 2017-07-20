#ifndef Point_h
#define Point_h

#include <iostream>
using namespace std;

class Point
{
	int point[3];
	int tag;
public:
	Point();
	void operator=(int a);
	int operator[](int a);
	void init(int a[3]);
	int getTag();
	void whatHouse(int nh);
};
#endif