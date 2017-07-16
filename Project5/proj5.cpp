#include <iostream>
#include <string>
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/bgsegm.hpp>

using namespace cv;

class BoundingBox
{
	Ptr<BackgroundSubtractor> pMOG2;
	Mat fgMaskMOG2, grayframe;
	Rect rec;
public:
	BoundingBox();
	void operator()(Mat &frame);
};
BoundingBox::BoundingBox()
{
	pMOG2 = createBackgroundSubtractorMOG2();
}
void BoundingBox::operator()(Mat &frame)
{
	cvtColor(frame, grayframe, COLOR_BGR2GRAY);
	GaussianBlur(grayframe, grayframe, Size(15,15), 3, 3);
	pMOG2 -> apply(grayframe, fgMaskMOG2);
	rec = boundingRect(fgMaskMOG2);
	rectangle(frame, rec, cv::Scalar(250, 250, 250), 2);
}
int main()
{
	Mat frame;
	int keyboard;
	BoundingBox bb;
	namedWindow("Frame");
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
		bb(frame);
		imshow("Frame", frame);
        keyboard = waitKey( 30 );
    }
}