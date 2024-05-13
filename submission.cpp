// 컴퓨터 비전 ch 12-1

// 실습과제 1

#include <iostream>
using namespace std;
#include <opencv2/opencv.hpp>
using namespace cv;
int main()
{
	Mat src = imread("labelex.png", IMREAD_GRAYSCALE);
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }

	Mat bin;
	threshold(src, bin, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);

	Mat labels, stats, centroids;
	int cnt = connectedComponentsWithStats(bin, labels, stats, centroids);

	cvtColor(src, src, COLOR_GRAY2BGR);

	int minSize = INT_MAX;
	int minIdx = -1;
	int maxSize = 0;
	int maxIdx = -1;

	for (int i = 1; i < cnt; i++) {
		if (stats.at<int>(i, 4) < minSize) {
			minSize = stats.at<int>(i, 4);
			minIdx = i;
		}
		if (stats.at<int>(i, 4) > maxSize) {
			maxSize = stats.at<int>(i, 4);
			maxIdx = i;
		}
	}
	cout << "면적이 최대인 객체의 레이블: " << maxIdx << endl;
	if (maxIdx != -1) {
		Point maxCentroid((int)centroids.at<double>(maxIdx, 0), (int)centroids.at<double>(maxIdx, 1));
		cout << "무게중심 (x, y): " << maxCentroid.x << "\t" << maxCentroid.y << endl;
		int* p = stats.ptr<int>(maxIdx);
		rectangle(src, Rect(p[0], p[1], p[2], p[3]), Scalar(0, 0, 255)); // 빨간색 선으로 가장 큰 도형 바운딩 박스 그리기
	}
	cout << "면적이 최소인 객체의 레이블: " << minIdx << endl;
	if (minIdx != -1) {
		Point minCentroid((int)centroids.at<double>(minIdx, 0), (int)centroids.at<double>(minIdx, 1));
		cout << "무게중심 (x, y): " << minCentroid.x << "\t" << minCentroid.y << endl;
		int* p = stats.ptr<int>(minIdx);
		rectangle(src, Rect(p[0], p[1], p[2], p[3]), Scalar(255, 0, 0)); // 파란색 선으로 가장 작은 도형 바운딩 박스 그리기
	}
	imshow("src", src);
	waitKey();
	destroyAllWindows();
	return 0;
}

// 실습과제 2
/*
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main() {
	Mat src = imread("polygon.bmp");
	if (src.empty()) { cerr << "failed" << endl; return -1; }

	Mat gray, bin;
	cvtColor(src, gray, COLOR_BGR2GRAY);

	threshold(gray, bin, 150, 255, THRESH_BINARY_INV);

	Mat  labels, stats, centroids;
	int cnt = connectedComponentsWithStats(bin, labels, stats, centroids);

	cout << "갯수" << cnt << endl;
	cout << "label	x	y	width	height	area	color [B, G, R]" << endl;

	for (int i = 1; i < cnt; i++) {
		if (stats.at<int>(i, 4) < 20) continue;
		rectangle(src, Rect(stats.at<int>(i, 0), stats.at<int>(i, 1), stats.at<int>(i, 2), stats.at<int>(i, 3)), Scalar(0, 255, 255));
		cout << i << "\t" << stats.at<int>(i, 0) << "\t" << stats.at<int>(i, 1) << "\t" << stats.at<int>(i, 2) << "\t" << stats.at<int>(i, 3)
			<< "\t" << stats.at<int>(i, 2) * stats.at<int>(i, 3) << "\t" << src.at<Vec3b>((int)centroids.at<double>(i, 1), (int)centroids.at<double>(i, 0)) << endl;
		putText(src, to_string(i), Point((int)centroids.at<double>(i, 0), (int)centroids.at<double>(i, 1)), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 150, 255));
	}

	imshow("src", src);
	imshow("gray", gray);
	imshow("bin", bin);
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
	Mat src = imread("polygon.bmp");
	if (src.empty()) { cerr << "failed" << endl; return -1; }

	Mat gray, bin;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, bin, 150, 255, THRESH_BINARY_INV);

	Mat labels, stats, centroids;
	int cnt = connectedComponentsWithStats(bin, labels, stats, centroids);

	for (int i = 1; i < cnt; i++) {
		int count = 0;
		int xsum = 0, ysum = 0;
		for (int x = stats.at<int>(i, 0); x < stats.at<int>(i, 0) + stats.at<int>(i, 2); x++) {
			for (int y = stats.at<int>(i, 1); y < stats.at<int>(i, 1) + stats.at<int>(i, 3); y++) {
				if (bin.at<uchar>(y, x) == 255) {
					count++;
					xsum += x;
					ysum += y;
				}
			}
		}
		cout << i << "번 객체의 무게중심: ( " << xsum / count << ", " << ysum / count << ")" << endl;
	}
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

	Mat labels, stats, centroids;
	int cnt = connectedComponentsWithStats(close, labels, stats, centroids);

	// 빨간색으로 바운딩 박스 그리기
	for (int i = 1; i < cnt; ++i) {
		int area = stats.at<int>(i, 4); // CC_STAT_AREA에 해당하는 열
		if (area > 1000) { // 번호판이라고 가정하고 너무 작은 영역은 무시
			int x = stats.at<int>(i, 0); // CC_STAT_LEFT에 해당하는 열
			int y = stats.at<int>(i, 1); // CC_STAT_TOP에 해당하는 열
			int width = stats.at<int>(i, 2); // CC_STAT_WIDTH에 해당하는 열
			int height = stats.at<int>(i, 3); // CC_STAT_HEIGHT에 해당하는 열
			rectangle(src, Point(x, y), Point(x + width, y + height), Scalar(0, 0, 255), 2);
		}
	}

	imshow("Bounding Box", src);
	waitKey();
	return 0;
}*/
