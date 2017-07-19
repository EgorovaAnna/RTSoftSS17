#include <iostream>
#include <string>
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include "opencv2/stitching.hpp"

using namespace cv;

class Gluing
{
	Ptr<Stitcher> stitcher;
	int walls[4];
	int x; int y;
	int step;
public:
	Gluing();
	void compXY(int botton, int wall1, int wall2);
	void calcWalls(Mat &frames);
	void init(std::vector<Mat> &f);
	void operator()(std::vector<Mat> &f, Mat &frames, int button);
};
Gluing::Gluing()
{
	bool try_use_gpu = false;
	Stitcher::Mode mode = Stitcher::PANORAMA;
	stitcher = Stitcher::create(mode, try_use_gpu);
	x = 0, y = 0, step = 1;
}
void Gluing::init(std::vector<Mat> &f)
{
	stitcher -> estimateTransform(f);
	Mat frames;
	stitcher -> composePanorama(f, frames);
	calcWalls(frames);
	step = max(f[0].cols/50, 1);
}
void Gluing::calcWalls(Mat &frames)
{
	Mat grayframe;
	SparseMat s;
	int a = 0, b = 0, c = 0, d = 0, i, j;
	cvtColor(frames, grayframe, COLOR_BGR2GRAY);
	walls[0] = frames.cols/4;
	walls[1] = 3*frames.cols/4;
	walls[2] = frames.rows/4;
	walls[3] = 3*frames.rows/4;
	while(a == 0 || b == 0 || c == 0 || d == 0)
	{
		a = 1; b = 1, c = 1, d = 1;
		if((s = Mat(grayframe, Rect(walls[0] - 1, walls[2] - 1, walls[1] - walls[0] + 2, walls[3] - walls[2] + 2))).nzcount() == (walls[1] - walls[0] + 2)*(walls[3] - walls[2] + 2))
		{
			walls[0]--;
			walls[2]--;
			walls[1]++;
			walls[3]++;
		}
		if((s = Mat(grayframe, Rect(walls[0] - 1, walls[2], 1, walls[3] - walls[2]))).nzcount() == (walls[3] - walls[2]))
		{
			walls[0]--;
			a--;
		}
		if((s = Mat(grayframe, Rect(walls[0], walls[2] - 1, walls[1] - walls[0], 1))).nzcount() == (walls[1] - walls[0]))
		{
			walls[2]--;
			c--;
		}
		if((s = Mat(grayframe, Rect(walls[1] + 1, walls[2], 1, walls[3] - walls[2]))).nzcount() == (walls[3] - walls[2]))
		{
			walls[1]++;
			b--;
		}
		if((s = Mat(grayframe, Rect(walls[0], walls[3] + 1, walls[1] - walls[0], 1))).nzcount() == (walls[1] - walls[0]))
		{
			walls[3]++;
			d--;
		}
	}
	x = walls[0];
	y = walls[2];
}
void Gluing::operator()(std::vector<Mat> &f, Mat &frames, int button)
{
	stitcher -> composePanorama(f, frames);
	compXY(button, 2*f[0].cols/3, 2*f[0].rows/3);
	frames = frames(Rect(x, y, 2*f[0].cols/3, 2*f[0].rows/3));
}
void Gluing::compXY(int botton, int winsize1, int winsize2)
{
	if (botton == 81)
		x = max(walls[0], x - step);
	if (botton == 83)
		x = min(walls[1] - winsize1, x + step);
	if (botton == 82)
		y = max(walls[2], y - step);
	if (botton == 84)
		y = min(walls[3] - winsize2, y + step);
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