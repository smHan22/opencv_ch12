// �ǽ����� 1
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

// �ǽ����� 2
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

// �ǽ����� 3
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
			// i��° �������� j��° ������ �����Ͽ� j+1 ��° ������ ����. ���������� �����Ͽ� �������� �׸����� ��.
			line(src, contours[i][j], contours[i][j + 1], c, 2);
		}
		// contours[i]�� i��° ������, contours[i].size() - 1�� �������� ������ ��. contours[i][0]�� �ش� �������� ù��° ��
		line(src, contours[i][contours[i].size() - 1], contours[i][0], c, 2);
	}

	imshow("src", src);
	waitKey(0);
	return 0;
}

// �ǽ����� 4
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
		cout << i << "��° �ܰ��� ����: " << contours[i].size() << endl;
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
	cout << "���̰� �ִ��� �ܰ���: " << cnt << "���� ���̴�: " << maxlong << endl;
	imshow("src", src);
	waitKey();
	return 0;
}

// �ǽ����� 5
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
			cout << i << "��° ����(�Ķ���): �������� ����" << endl;
		}
		else if (x[i] < (stats.at<int>(i, 0) + stats.at<int>(i, 2)) / 2) {
			drawContours(src, contours, i, Scalar(0, 0, 255), 2);
			cout << i << "��° ����(������): ���������� ����" << endl;
		}
	}
	imshow("src", src);
	waitKey();
	return 0;
}