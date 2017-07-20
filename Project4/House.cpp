#include "House.h"

House::House()
{
	h = 0;
}
House::House(Position tp, int posInt[2])
{
	int *coint = new int[2], *coint1 = new int[2], *coint2 = new int[2],*coint3 = new int[2];
	if(posInt[0] >= 0 && posInt[1] >= 0)
	{
		coint[0] = posInt[0];
		coint[1] = posInt[1];
	}
	else
	{
		coint[0] = 0;
		coint[1] = 0;
	}
	corners.push_back(tp);
	corInt.push_back(coint);
	h = 100;
	coint1[0] = posInt[0] + h;
	coint1[1] = posInt[1];
	corInt.push_back(coint1);
	coint2[0] = posInt[0] + h;
	coint2[1] = posInt[1] + h;
	corInt.push_back(coint2);
	coint3[0] = posInt[0];
	coint3[1] = posInt[1] + h;
	corInt.push_back(coint3);
}
int House::getPosInt(int bin)
{
	if(bin == 0)
		return corInt[0][0];
	if(bin == 1)
		return corInt[0][1];
	return 0;
}
Position House::getPos()
{
	return corners[0];
}
void House::printAll()
{
	int i;
	cout << corners[0][0] << " " << corners[0][1] << '\n';
	for(i = 0; i < corInt.size(); i++)
	{
		cout << corInt[i][0] << " " << corInt[i][1] << " " << '\n';
	}
}
void House::draw(Image &map, int nh)
{
	int i;
	for(i = 0; i < corInt.size() - 1; i++)
	{
		map.drawLine(corInt[i][0], corInt[i][1], corInt[i + 1][0], corInt[i + 1][1], nh);
	}
	map.drawLine(corInt[corInt.size() - 1][0], corInt[corInt.size() - 1][1], corInt[0][0], corInt[0][1], nh);
}
int House::getLeft()
{
	int i, j = 0;
	for(i = 0; i < corInt.size(); i++)
		if(corInt[i][0] < corInt[j][0])
			j = i;
	return corInt[j][0];
}
int House::getRight()
{
	int i, j = 0;
	for(i = 0; i < corInt.size(); i++)
		if(corInt[i][0] > corInt[j][0])
			j = i;
	return corInt[j][0];
}
int House::getUpper()
{
	int i, j = 0;
	for(i = 0; i < corInt.size(); i++)
		if(corInt[i][1] > corInt[j][1])
			j = i;
	return corInt[j][1];
}
int House::getLower()
{
	int i, j = 0;
	for(i = 0; i < corInt.size(); i++)
		if(corInt[i][1] < corInt[j][1])
			j = i;
	return corInt[j][1];
}
void House::paint(Image &map, int nh)
{
	int i, j, k, count = 0, x1, x2;
	for(j = getLower(); j <= getUpper(); j++)
	{
		for(i = getLeft(); i <= getRight(); i++)
		{
			if(map.getTag(i, j) == nh)
			{
				if (count == 0)
				{
					x1 = i;
					count++;
				}
				else if ((i != x1 + 1)&&(x2 == 0))
				{
					x2 = i;
					count++;
				}
				if (i == x1 + 1)
				{
					x1++;
				}
			}
		}
		if (count == 2)
			for(k = x1 + 1; k < x2; k++)
				map.drawPoint(k, j, 255);
		count = 0;
		x1 = 0;
		x2 = 0;
	}
}






