#include "House.h"
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;

class Photo
{
	Image *photo;
	Position myPos;
	double azimut;
	double pi;
	int gorizont[2][2];
	int size[2];
	vector<House> houses;
public:
	Photo();
	void addHouse(House h);
	void loadPhoto(string fl);
	void loadFile(string fl);
	void calcPos(Position tp);
	Position xOnHouseLine(Position tp);
	int calcX(Position tp, int yLine);
	int calcY(Position tp);
	int sign(double x);
	double xOnAzimut(Position tp);
	double yOnAzimut(Position tp);
	double calcDelta(Position tp);
	double calcDelta(Position tp1, Position tp2);
	void show();
};
