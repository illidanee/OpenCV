#include  <iostream>
#include "opencv2/opencv.hpp"


using namespace std;
using namespace cv;


int main(int argc, char** argv)
{
	//Open camera
	VideoCapture cap(0);
	if (!cap.isOpened())
	{
		cerr << "Can not open a camera or file." << endl;
		return -1;
	}

	Mat edges;
	namedWindow("illidan", 1);

	while (true)
	{
		Mat frame;
		cap >> frame;
		if (frame.empty())
			break;

		//Origin
		imshow("illidan", frame);

		//Ray
		cvtColor(frame, edges, CV_BGR2GRAY);
		//Canny(edges, edges, 0, 30, 3);
		//imshow("edges", edges);

		waitKey(30);
	}

	return 0;
}