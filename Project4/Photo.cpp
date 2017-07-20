
#include "Photo.h"

Photo::Photo()
{
	myPos.add(0, 0);
	azimut = 0;
	pi = 3.1415926535897;
}
void Photo::addHouse(House h)
{
	houses.push_back(h);
}
void Photo::calcPos(Position tp)
{
	int xy[2];
	xy[1] = calcY(tp);
	xy[0] = calcX(tp, xy[1]) - 100;
	addHouse(House(tp, xy));
}
Position Photo::xOnHouseLine(Position tp)
{
	if (houses[0].getPosInt(0) != size[0]/2 && abs(houses[0].getPosInt(0) - size[0]/2) > abs(houses[1].getPosInt(0) - size[0]/2))
	{
		Position hAz(xOnAzimut(houses[0].getPos()), yOnAzimut(houses[0].getPos())); 
		Position tpOnHouseLine((tp[1] - hAz[1] + hAz[0]*tan(pi - azimut) - tp[0]*1/tan(azimut))/(tan(pi - azimut) - 1/tan(azimut)), 1/tan(azimut)*((tp[1] - hAz[1] + hAz[0]*tan(pi - azimut) - tp[0]*1/tan(azimut))/(tan(pi - azimut) - 1/tan(azimut)) - tp[0]) + tp[1]);
		return Position(size[0]/2 + (calcDelta(hAz, tpOnHouseLine))*(size[0]/2 - houses[0].getPosInt(0))/(calcDelta(houses[0].getPos(), hAz)), houses[0].getPosInt(1));
	}
	if (houses[1].getPosInt(0) != size[0]/2)
	{
		Position hAz(xOnAzimut(houses[1].getPos()), yOnAzimut(houses[1].getPos())); 
		Position tpOnHouseLine((tp[1] - hAz[1] + hAz[0]*tan(pi - azimut) - tp[0]*1/tan(azimut))/(tan(pi - azimut) - 1/tan(azimut)), 1/tan(azimut)*((tp[1] - hAz[1] + hAz[0]*tan(pi - azimut) - tp[0]*1/tan(azimut))/(tan(pi - azimut) - 1/tan(azimut)) - tp[0]) + tp[1]);
		return Position(size[0]/2 + (calcDelta(hAz, tpOnHouseLine))*(size[0]/2 - houses[1].getPosInt(0))/(calcDelta(houses[1].getPos(), hAz)), houses[1].getPosInt(1));
	}
	return Position(size[0]/2, 0);
}
int Photo::calcX(Position tp, int yLine)
{
	int gor = (gorizont[0][1] + gorizont[1][1])/2;
	return floor((yLine - xOnHouseLine(tp)[1])*(size[0]/2 - xOnHouseLine(tp)[0])/(gor - xOnHouseLine(tp)[1]) + xOnHouseLine(tp)[0]);
}
int Photo::calcY(Position tp)
{
	int gor = (gorizont[0][1] + gorizont[1][1])/2;
	double y00 = calcDelta(Position(xOnAzimut(houses[0].getPos()), yOnAzimut(houses[0].getPos()))), y01 = houses[0].getPosInt(1), y10 = calcDelta(Position(xOnAzimut(houses[1].getPos()), yOnAzimut(houses[1].getPos()))), y11 = houses[1].getPosInt(1);
	return floor((gor*(1 - exp(log(1 - y01/gor)*calcDelta(Position(xOnAzimut(tp), yOnAzimut(tp)))/y00)) + gor*(1 - exp(log(1 - y11/gor)*calcDelta(Position(xOnAzimut(tp), yOnAzimut(tp)))/y10)))/2);
}
double Photo::xOnAzimut(Position tp)
{
	return (myPos[1] - tp[1] + tp[0]*tan(pi - azimut) - myPos[0]*tan(pi/2 - azimut))/(tan(pi - azimut) - tan(pi/2 - azimut));
}
double Photo::yOnAzimut(Position tp)
{
	return 1/tan(azimut)*(xOnAzimut(tp) - myPos[0]) + myPos[1];
} 
double Photo::calcDelta(Position tp)
{
	return pow(pow(myPos[0] - tp[0], 2) + pow(myPos[1] - tp[1], 2), 0.5);
}
double Photo::calcDelta(Position tp1, Position tp2)
{
	return pow(pow(tp1[0] - tp2[0], 2) + pow(tp1[1] - tp2[1], 2), 0.5);
}
void Photo::loadPhoto(string fl)
{
	ifstream fin(fl.c_str());
	int a = 0;
	string buf;
	fin >> buf;
	while (!(isdigit(buf[0])&&isdigit(buf[1])))
		fin >> buf;
	size[0] = 1000*(int)(buf[0] - '0') + 100*(int)(buf[1] - '0') + 10*(int)(buf[2] - '0') + (int)(buf[3] - '0');
	fin >> size[1];
	photo = new Image(size);
	photo -> loadIm(fin);
}
void Photo::loadFile(string fl)
{
	ifstream fin(fl.c_str());
	double x1, y1, xy[2];
	int i, xyI[2];
	Position tp;
	x1 = size[0];
	y1 = size[1];
	fin >> xy[0] >> xy[1];
	myPos.add(xy[1], xy[0]);
	fin >> azimut;
	fin >> gorizont[0][0] >> gorizont[0][1] >> gorizont[1][0] >> gorizont[1][1];
	for(i = 0; i < 2; i++)
	{
		fin >> xy[0] >> xy[1];
		tp.add(xy[1], xy[0]);
		fin >> xyI[0] >> xyI[1];
		if((xyI[0] <= x1)&&(xyI[1] <= y1))
			addHouse(House(tp, xyI));
	}
	fin >> xy[0] >> xy[1];
	tp.add(xy[1], xy[0]);
	calcPos(tp);
}
void Photo::show()
{
	int l;
	for(l = 0; l < houses.size(); l++)
	{
		houses[l].draw(*photo, l + 1);
		houses[l].paint(*photo, l + 1);
	}
	photo -> drawLine( gorizont[0][0], gorizont[0][1] + 1, gorizont[1][0], gorizont[1][1] + 1, l+2);
	photo -> drawLine( gorizont[0][0], gorizont[0][1] + 2, gorizont[1][0], gorizont[1][1] + 2, l+2);
	photo -> drawLine( gorizont[0][0], gorizont[0][1] + 3, gorizont[1][0], gorizont[1][1] + 3, l+2);
	photo -> drawLine( gorizont[0][0], gorizont[0][1] + 4, gorizont[1][0], gorizont[1][1] + 4, l+2);
	photo -> showFile("photoShow.pnm");	
}


