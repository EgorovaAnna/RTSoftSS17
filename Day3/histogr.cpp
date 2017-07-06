#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <opencv/cv.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

using namespace std;
using namespace cv;

class All
{
	Mat mat;
	//Mat hist[3];
	Mat hist;
	//double result[3];
	double result;
public:
	All();
	void compHist(All obr);
	void calc(std::string path);
	void calc(Mat tm);
	bool operator<(All all2);
	//Mat getHist(int n);
	Mat getHist();
	Mat getMat();
	//double getResult(int n);
	double getResult();
};
All::All()
{
	mat = Mat();
	//for(int i = 0; i < 3; i++)
	//{
	//	hist[i] = Mat();
	//	result[i] = 0;
	//}
	hist = Mat();
	result = 0;
}
/*double All::getResult(int n)
{
	return result[n];
}
Mat All::getHist(int n)
{
	return hist[n];
}*/
double All::getResult()
{
	return result;
}
Mat All::getHist()
{
	return hist;
}
Mat All::getMat()
{
	return mat;
}
void All::compHist(All obr)
{
	//for(int i = 0; i < 3; i++)
	//	result[i] = compareHist(hist[i], obr.getHist(i), CV_COMP_BHATTACHARYYA);
	result = compareHist(hist, obr.getHist(), CV_COMP_BHATTACHARYYA);
}
void All::calc(std::string path)
{
	int histSize[] = {256, 256, 256};
	int channels[] = {0, 1, 2};
	float arang[] = {0, 255};
	float brang[] = {0, 255};
	float crang[] = {0, 255};
	const float* ranges[] = {arang, brang, crang};
	//Mat bgrChannels[3]; 
	//int histSize = 256; 
	//float range[] = {0, 255}; 
	//const float* histRange[] = { range }; 
	mat = imread(path, CV_32F);
	//split(mat, bgrChannels); 
	//calcHist(&bgrChannels[0], 1, 0, Mat(), hist[0], 1, &histSize, histRange, true, false); 
	//calcHist(&bgrChannels[1], 1, 0, Mat(), hist[1], 1, &histSize, histRange, true, false); 
	//calcHist(&bgrChannels[2], 1, 0, Mat(), hist[2], 1, &histSize, histRange, true, false);  
	calcHist(&mat, 1, channels, Mat(), hist, 3, histSize, ranges, true, false);
}
void All::calc(Mat tm)
{
	//Mat bgrChannels[3]; 
	//int histSize = 256; 
	//float range[] = {0.0, 256.0}; 
	//const float* histRange[] = { range }; 
	int histSize[] = {256, 256, 256};
	int channels[] = {0, 1, 2};
	float arang[] = {0, 255};
	float brang[] = {0, 255};
	float crang[] = {0, 255};
	const float* ranges[] = {arang, brang, crang};
	mat = tm;
	//split(mat, bgrChannels); 
	//calcHist(&bgrChannels[0], 1, 0, Mat(), hist[0], 1, &histSize, histRange, true, false); 
	//calcHist(&bgrChannels[1], 1, 0, Mat(), hist[1], 1, &histSize, histRange, true, false); 
	//calcHist(&bgrChannels[2], 1, 0, Mat(), hist[2], 1, &histSize, histRange, true, false); 
	calcHist(&mat, 1, channels, Mat(), hist, 3, histSize, ranges, true, false);
}
bool All::operator<(All all2)
{
	//return (result[0]*result[0] + result[1]*result[1] + result[2]*result[2]) < (all2.getResult(0)*all2.getResult(0) + all2.getResult(1)*all2.getResult(1) + all2.getResult(2)*all2.getResult(2));
	return result < all2.getResult();
}

class SortImage
{
public:
	vector<Mat> operator()(std::string path, Mat obr)
	{
		vector<All> all;
		vector<Mat> mats;
		All obraz;
		int i;
		vector<std::string> files = readls(path);
		obraz.calc(obr);
		for(i = 0; i < files.size(); i++)
		{
			all.push_back(All());
			all.back().calc(path + "/" + files[i]);
			all.back().compHist(obraz);
		}
		sort(all.begin(), all.end());
		for(i = 0; i < all.size(); i++)
			mats.push_back(all[i].getMat());
		return mats;
	}
	vector<std::string> readls(std::string path)
	{
		vector<std::string> files;
		ifstream fin;
		string file;
		int i;
		std::string path1 = "ls -A " + path + " > files.txt";
		char cdls[path1.size() + 1];
		for(i = 0; i <= path1.size(); i++)
			cdls[i] = path1[i];
		cdls[i] = 0;
		system(cdls);
		fin.open("files.txt");
		while(!fin.eof())
		{
			fin >> file;
			if (files.empty() || files.back() != file)
				files.push_back(file);
		}
		fin.close();
		system("rm files.txt");
		return files;
	}
};
int main()
{
	int i;
	Mat obr = imread("test/4.jpeg", CV_32F);
	namedWindow( "Display window", WINDOW_AUTOSIZE );
    imshow( "Display window", obr );  
	waitKey(0);
	SortImage a;
	vector<Mat> mat = a("test/", obr);
	namedWindow( "Sorted",  WINDOW_AUTOSIZE);
	for(i = 0; i < mat.size(); i++)
	{
	    imshow( "Sorted", mat[i] );
		waitKey(0);
	}
}