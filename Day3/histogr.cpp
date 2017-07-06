#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cv.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

using namespace std;
using namespace cv;

class All
{
	Mat mat;
	Mat hist;
	double result;
public:
	All();
	void compHist(All obr);
	void calc(std::string path);
	void calc(Mat tm);
	bool operator<(All all2);
	Mat getHist();
	Mat getMat();
	double getResult();
};
All::All()
{
	mat = Mat();
	hist = Mat();
	result = 0;
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
	result = compareHist(hist, obr.getHist(), CV_COMP_BHATTACHARYYA);
}
void All::calc(std::string path)
{
	int histSize[] = {16, 16, 16};
	const int channels[] = {0, 1, 2};
	float arang[] = {0, 256};
	float brang[] = {0, 256};
	float crang[] = {0, 256};
	const float* ranges[] = {arang, brang, crang};
	mat = imread(path, CV_8U);
	calcHist(&mat, 1, &channels[0], Mat(), hist, 3, &histSize[0], ranges, true, false);
}
void All::calc(Mat tm)
{
	int histSize[] = {16, 16, 16};
	const int channels[] = {0, 1, 2};
	float arang[] = {0, 256};
	float brang[] = {0, 256};
	float crang[] = {0, 256};
	const float* ranges[] = {arang, brang, crang};
	mat = tm;
	calcHist(&mat, 1, &channels[0], Mat(), hist, 3, &histSize[0], ranges, true, false);
}
bool All::operator<(All all2)
{
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
		for(i = 0; i <= files.size(); i++)
		{
			cout << files[i] << endl;
			all.push_back(All());
			all.back().calc(path + "/" + files[i]);
			all.back().compHist(obraz);
		}
		std::sort(all.begin(), all.end());
		for(i = 0; i <= all.size(); i++)
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
			files.push_back(file);
		}
		fin.close();
		system("rm files.txt");
		return files;
	}
};
int main()
{
	Mat obr = imread("test/1.jpeg", CV_8U);
	namedWindow( "Display window", WINDOW_AUTOSIZE );
    imshow( "Display window", obr );  
	SortImage a;
	vector<Mat> mat = a("test/", obr);
	namedWindow( "Histogram", 1 );
    imshow( "Histogram", mat[0] );
}