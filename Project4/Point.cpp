#include "Point.h"

Point::Point()
{
	point[0] = 0;
	point[1] = 0;
	point[2] = 0;
	tag = 0;
}
void Point::operator=(int a)
{
	point[0] = a;
	point[1] = a;
	point[2] = a;
}
void Point::whatHouse(int nh)
{
	tag = nh;
}
int Point::operator[](int a)
{
	if (a < 3 && a > -1)
		return point[a];
	else
		return -1;
}
void Point::init(int a[3])
{
	point[0] = a[0];
	point[1] = a[1];
	point[2] = a[2];
}
int Point::getTag()
{
	return tag;
}
