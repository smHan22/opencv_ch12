/*컴퓨터 비전 ch 11-2*/
/*실습과제 1*/
/*
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main() {
	Mat img1 = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	Mat img2 = getStructuringElement(MORPH_CROSS, Size(3, 3), Point(-1, -1));
	Mat img3 = getStructuringElement(MORPH_ELLIPSE, Size(5, 3), Point(-1, -1));

	cout << "MORPH_RECT" << "\n" << img1 << endl;
	cout << "MORPH_CROSS" << "\n" << img2 << endl;
	cout << "MORPH_ELLIPSE" << "\n" << img3 << endl;
}*/

// 실습과제 2
/*
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main() {
	Mat src = imread("letterj.png", IMREAD_GRAYSCALE);
	if (src.empty()) { cerr << "failed" << endl; return -1; }

	Mat dst;
	threshold(src, dst, 100, 255, THRESH_BINARY);

	Mat erode1;
	morphologyEx(dst, erode1, MORPH_OPEN, Mat());
	morphologyEx(erode1, erode1, MORPH_CLOSE, Mat());

	imshow("src", src);
	imshow("bin", dst);
	imshow("erode", erode1);
	waitKey();
	return 0;
}*/

// 실습과제 3
/*
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main() {
	Mat src = imread("letter2.png", IMREAD_GRAYSCALE);
	if (src.empty()) { cerr << "failed" << endl; return -1; }

	Mat dst, edge;
	threshold(src, dst, 100, 255, THRESH_BINARY);
	morphologyEx(dst, edge, MORPH_GRADIENT, Mat());

	imshow("src", src);
	imshow("bin", dst);
	imshow("edge", edge);
	waitKey();
	return 0;
}*/

// 실습과제 4
/*
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main() {
	Mat src = imread("car.jpg");
	if (src.empty()) { cerr << "failed" << endl; return -1; }
	
	imshow("image", src);
	
	Mat gray, blurr, dx;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	blur(gray, blurr, Size(5, 5));
	Sobel(blurr, dx, CV_32FC1, 1, 0);
	dx.convertTo(dx, CV_8UC1);
	imshow("x축방향 소벨", dx);

	Mat bin;
	threshold(dx, bin, 100, 255, THRESH_BINARY);
	imshow("이진화 영상", bin);
	
	Mat close;
	morphologyEx(bin, close, MORPH_CLOSE, Mat(Size(21, 5), CV_8UC1));
	
	imshow("닫힘 연산", close);
	waitKey();
	return 0;	
}*/