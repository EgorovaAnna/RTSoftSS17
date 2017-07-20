#include "Photo.h"

int main()
{
	Photo mphoto;
	mphoto.loadPhoto("mapPhoto.ppm");
	mphoto.loadFile("mapPhoto.txt");
	mphoto.show();
	return 0;
}