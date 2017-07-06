#include <iostream>
#include <string>
#include <vector>
#include <fstream>
//#include <dir.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

using namespace std;
using namespace cv;

class SortImage
{
public:
	vector<Mat> operator()(std::string path, int accuracy)
	//void operator()(string path, int accuracy)
	{
		vector<Mat> mats;
		vector<Mat> hists;
		char dir[100], chd[path.size() + 1];
		int i;
		int histSize[] = {16, 16, 16};
		const int channels[] = {0, 1, 2};
		float arang[] = {0, 256};
		float brang[] = {0, 256};
		float crang[] = {0, 256};
		const float* ranges[] = {arang, brang, crang};
		vector<std::string> files = readls(path);
		//getcurdir(0, dir);
		for(i = 0; i <= path.size(); i++)
			chd[i] = path[i];
		chd[i] = 0;
		//chwdir(chd);
		for(i = 0; i <= files.size(); i++)
		{
			cout << files[i] << endl;
			mats.push_back(Mat());
			hists.push_back(Mat());
			mats.back() = imread(path + files[i], CV_8U);
			//calcHist(&mats[i], 1, &channels[0], Mat(), hists[i], 3, histSize, ranges, true, false);
		}
		//chwdir(dir);
		return hists;
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
	SortImage a;
	vector<Mat> hi = a("test/", 11);
	//namedWindow( "Histogram", 1 );
    //imshow( "Histogram", hi[0] );
}