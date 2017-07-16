#include <iostream>
#include <string>
#include <cmath>
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/bgsegm.hpp>

using namespace cv;

class Plan
{
	Rect human;
	int humanSq;
	int length;
	int width;
	int lengthOnFrame;
	int widthOnFrameStart;
	int widthOnFrameEnd;
public:
	Mat plan;
	Plan(int x, int y, int x1f, int x2f, int yf);
	void countPosition(int xOnFrame, int yOnFrame);
	void drawPosition(int xOnFrame, int yOnFrame);
};
Plan::Plan(int x, int y, int x1f, int x2f, int yf)
{
	length = y;
	width = x;
	lengthOnFrame = yf;
	widthOnFrameStart = x1f;
	widthOnFrameEnd = x2f;
	plan = Mat::zeros(width, length, CV_32F);
	humanSq = floor((double)x*50/widthOnFrameStart);
	human = Rect(0, 0, humanSq, humanSq);
}
void Plan::countPosition(int xOnFrame, int yOnFrame)
{
	double y = 2*length*asin(yOnFrame/lengthOnFrame)/3.14 + humanSq;
	double currentWidth = (double)yOnFrame*(widthOnFrameEnd - widthOnFrameStart)/lengthOnFrame + widthOnFrameEnd;
	double x = (xOnFrame - (widthOnFrameStart - currentWidth)/2)*width/currentWidth;
	human = Rect(floor(x), floor(y), humanSq, humanSq);
}
void Plan::drawPosition(int xOnFrame, int yOnFrame)
{
	countPosition(xOnFrame, yOnFrame);
	rectangle(plan, human, cv::Scalar(250, 250, 250), 2);
}

class BoundingBox
{
	Ptr<BackgroundSubtractor> pMOG2;
	Mat fgMaskMOG2, grayframe;
	Rect rec;
public:
	BoundingBox();
	void operator()(Mat &frame, Plan &plan);
	void showOnPlan(Plan &plan);
};
BoundingBox::BoundingBox()
{
	pMOG2 = createBackgroundSubtractorMOG2();
}
void BoundingBox::operator()(Mat &frame, Plan &plan)
{
	cvtColor(frame, grayframe, COLOR_BGR2GRAY);
	GaussianBlur(grayframe, grayframe, Size(15,15), 3, 3);
	pMOG2 -> apply(grayframe, fgMaskMOG2);
	rec = boundingRect(fgMaskMOG2);
	rectangle(frame, rec, cv::Scalar(250, 250, 250), 2);
	showOnPlan(plan);
}
void BoundingBox::showOnPlan(Plan &plan)
{
	plan.drawPosition(rec.tl().x, rec.tl().y);
}

int main()
{
	Mat frame;
	int x, y, x1f, x2f, yf, keyboard;
	Plan plan(x, y, x1f, x2f, yf);
	BoundingBox bb;
	namedWindow("Frame");
	namedWindow("Plan");
	std::string videoFilename = "Video_001.avi";
	VideoCapture capture("Video_001.avi");
    if(!capture.isOpened()){
        std::cout << "Unable to open video file: " << videoFilename << '\n';
        exit(EXIT_FAILURE);
    }
    while((char)keyboard != 27)
	{
        if(!capture.read(frame)) 
		{
           exit(EXIT_FAILURE);
        }
		bb(frame, plan);
		imshow("Frame", frame);
		imshow("Plan", plan.plan);
        keyboard = waitKey( 30 );
    }
}