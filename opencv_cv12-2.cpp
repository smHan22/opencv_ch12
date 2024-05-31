// 실습과제 1
#include <iostream>
using namespace std;
#include <opencv2/opencv.hpp>
using namespace cv;
int main(void)
{
	Mat src = imread("polygon.bmp");
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }

	Mat dst, binary;
	cvtColor(src, dst, COLOR_BGR2GRAY);
	threshold(dst, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
	vector<vector<Point>> contours;
	findContours(binary, contours, RETR_TREE, CHAIN_APPROX_NONE);

	for (int i = 1; i < contours.size(); i++) {
		Scalar c(rand() & 255, rand() & 255, rand() & 255);
		drawContours(src, contours, i, c, 2);
	}

	imshow("src", src);
	waitKey(0);
	return 0;
}

// 실습과제 2
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

void labeling_basic() {
	uchar data[] = {
		0, 0, 1, 1, 0, 0, 0, 0,
		1, 1, 1, 1, 0, 0, 1, 0,
		1, 1, 1, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 1, 1, 0,
		0, 0, 0, 1, 1, 1, 1, 0,
		0, 0, 0, 1, 0, 0, 1, 0,
		0, 0, 1, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
	};
	Mat src = Mat(8, 8, CV_8UC1, data) * 255;

	Mat labels;

	int cnt = connectedComponents(src, labels);

	cout << "src:\n" << src << endl;
	cout << "labels:\n" << labels << endl;
	cout << "number of labesl: " << cnt << endl;
}

// 실습과제 3
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
	Mat src = imread("labelex.png");
	if (src.empty()) {
		cerr << "failed" << endl;
		return -1;
	}

	Mat gray, binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 100, 255, THRESH_BINARY_INV);

	vector<vector<Point>> contours;
	findContours(binary, contours, RETR_TREE, CHAIN_APPROX_NONE);

	Scalar c(0, 0, 255);
	for (int i = 0; i < contours.size(); i++) {
		for (int j = 0; j < contours[i].size() - 1; j++) {
			// i번째 윤곽선의 j번째 점에서 시작하여 j+1 번째 점까지 연결. 순차적으로 연결하여 윤곽선을 그리려고 함.
			line(src, contours[i][j], contours[i][j + 1], c, 2);
		}
		// contours[i]는 i번째 윤곽선, contours[i].size() - 1은 윤곽선의 마지막 점. contours[i][0]은 해당 윤곽선의 첫번째 점
		line(src, contours[i][contours[i].size() - 1], contours[i][0], c, 2);
	}

	imshow("src", src);
	waitKey(0);
	return 0;
}

// 실습과제 4
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
	Mat src = imread("labelex.png");
	if (src.empty()) {
		cerr << "failed" << endl;
		return -1;
	}
	Mat gray, binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 100, 255, THRESH_BINARY_INV);

	vector<vector<Point>> contours;
	findContours(binary, contours, RETR_TREE, CHAIN_APPROX_NONE);

	for (int i = 0; i < contours.size(); i++) {
		cout << i << "번째 외곽선 길이: " << contours[i].size() << endl;
	}
	int cnt = 0;
	int maxlong = contours[0].size();
	for (int i = 0; i < contours.size(); i++) {
		if (contours[i].size() > maxlong) {
			maxlong = contours[i].size();
			cnt = i;
		}
	}
	drawContours(src, contours, cnt, Scalar(0, 0, 255), 2);
	cout << "길이가 최대인 외곽선: " << cnt << "번 길이는: " << maxlong << endl;
	imshow("src", src);
	waitKey();
	return 0;
}

// 실습과제 5
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main() {
	Mat src = imread("char_c.png");
	if (src.empty()) { cerr << "failed" << endl; return -1; }

	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	Mat bin;
	threshold(gray, bin, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);

	vector<vector<Point>> contours;
	findContours(bin, contours, RETR_LIST, CHAIN_APPROX_NONE);

	Mat labels, stats, centroids;
	int cnt = connectedComponentsWithStats(bin, labels, stats, centroids);

	vector<int> x;;
	for (int i = 0; i < cnt; i++) {
		x.push_back(centroids.at<double>(i, 0));
	}
	for (int i = 0; i < contours.size(); i++) {
		if (x[i] > (stats.at<int>(i, 0) + stats.at<int>(i, 2)) / 2) {
			drawContours(src, contours, i, Scalar(255, 0, 0), 2);
			cout << i << "번째 문자(파란색): 왼쪽으로 열림" << endl;
		}
		else if (x[i] < (stats.at<int>(i, 0) + stats.at<int>(i, 2)) / 2) {
			drawContours(src, contours, i, Scalar(0, 0, 255), 2);
			cout << i << "번째 문자(빨간색): 오른쪽으로 열림" << endl;
		}
	}
	imshow("src", src);
	waitKey();
	return 0;
}
