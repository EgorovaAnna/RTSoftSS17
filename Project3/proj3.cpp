#include <iostream>
#include <string>
#include <cmath>
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/bgsegm.hpp>
#include "opencv2/stitching.hpp"

using namespace cv;

class Gluing
{
	Ptr<Stitcher> stitcher;
	bool try_use_gpu;
	Stitcher::Mode mode;
	int x;
	int y;
	int step;
public:
	Gluing();
	void compXY(int botton, int wall1, int wall2);
	void init(std::vector<Mat> &f);
	void operator()(std::vector<Mat> &f, Mat &frames, int button);
};
Gluing::Gluing()
{
	try_use_gpu = false;
	mode = Stitcher::PANORAMA;
	stitcher = Stitcher::create(mode, try_use_gpu);
	x = 0, y = 0, step = 1;
}
void Gluing::init(std::vector<Mat> &f)
{
	stitcher -> estimateTransform(f);
	step = max(f[0].cols/100, 1);
}
void Gluing::operator()(std::vector<Mat> &f, Mat &frames, int button)
{
	stitcher -> composePanorama(f, frames);
	compXY(button, frames.cols - f[0].cols, frames.rows - f[0].rows);
	frames = frames(Rect(x, y, f[0].cols, f[0].rows));
}
void Gluing::compXY(int botton, int wall1, int wall2)
{
	if (botton == 81)
		x = max(0, x - step);
	if (botton == 83)
		x = min(wall1, x + step);
	if (botton == 82)
		y = max(0, y - step);
	if (botton == 84)
		y = min(wall2, y + step);
}

int main()
{
	Mat frames;
	std::vector<Mat> frame; 
	int keyboard = 0;
	Gluing glu;
	frame.push_back(Mat());
	frame.push_back(Mat());
	namedWindow("Frames");
	VideoCapture cap1("video0-1.avi");
	VideoCapture cap2("video1-1.avi");
    if(!cap1.isOpened() || !cap2.isOpened())
	{
        std::cout << "Unable to open video file" << '\n';
        exit(EXIT_FAILURE);
    }
    while((char)keyboard != 27)
	{
        if(!cap1.read(frame[0]) || !cap2.read(frame[1])) 
		{
           exit(EXIT_FAILURE);
        }
		if(keyboard == 0)
		{
			glu.init(frame);
		}
		glu(frame, frames, keyboard);
		imshow("Frames", frames);
        keyboard = waitKey(20);
    }
}