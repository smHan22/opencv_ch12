// 실습과제 1

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main() {
    Mat src = imread("beta.png");
    if (src.empty()) { cerr << "failed" << endl; return -1; }

    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);

    Mat bin;
    threshold(gray, bin, 200, 255, THRESH_BINARY_INV | THRESH_OTSU);

    vector<vector<Point>> contours;
    findContours(bin, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

    for (int i = 0; i < contours.size(); i++) {
        Rect rect = boundingRect(contours[i]);
        rectangle(src, rect, Scalar(0, 0, 255), 2);

        RotatedRect minRect = minAreaRect(contours[i]);

        Point2f rect_points[4];
        minRect.points(rect_points);

        for (int j = 0; j < 4; j++) {
            line(src, rect_points[j], rect_points[(j + 1) % 4], Scalar(255, 0, 0), 2);
        }
        Point2f center;
        float radius;
        minEnclosingCircle(contours[i], center, radius);

        circle(src, center, (int)radius, Scalar(0, 255, 255), 2);
    }
    imshow("letter", src);
    waitKey();

    return 0;
}

// 실습과제 2

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main() {
    Mat src = imread("rotateda.bmp");
    if (src.empty()) {
        cerr << "failed" << endl;
        return -1;
    }

    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);

    Mat bin;
    threshold(gray, bin, 200, 255, THRESH_BINARY_INV | THRESH_OTSU);

    vector<vector<Point>> contours;
    findContours(bin, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

    for (int i = 0; i < contours.size(); i++) {
        RotatedRect rect = minAreaRect(contours[i]);        // 회전된 객체 찾음
        float angle = rect.angle;       // Rotated객체의 회전 각도 알아냄
        cout << angle << endl;

        Point2f center = rect.center;
        Mat rot_mat = getRotationMatrix2D(center, angle, 1.0);

        Mat rotated;
        warpAffine(src, rotated, rot_mat, Size(), INTER_LINEAR, BORDER_REPLICATE);

        imshow("src", src);
        imshow("Rotated", rotated);
        waitKey(0);
    }
    return 0;
}

// 실습과제 3

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat src = imread("shapes.png");
    if (src.empty()) {
        cerr << "failed to open image" << endl;
        return -1;
    }
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    Mat bin;
    threshold(gray, bin, 200, 255, THRESH_BINARY_INV | THRESH_OTSU);

    vector<vector<Point>> contours;
    findContours(bin, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    int triangleCount = 0, squareCount = 0, circleCount = 0, pentagonCount = 0, HexagonCount = 0;
    for (int i = 0; i < contours.size(); i++) {
        double peri = arcLength(contours[i], true);
        vector<Point> approx;
        approxPolyDP(contours[i], approx, 0.04 * peri, true);

        if (approx.size() == 3)
            triangleCount++;
        else if (approx.size() == 4)
            squareCount++;
        else if (approx.size() == 5)
            pentagonCount++;
        else if (approx.size() == 6)
            HexagonCount++;
        else {
            double area = contourArea(contours[i]);
            double perimeter = arcLength(contours[i], true);
            double circularity = 4 * CV_PI * area / (perimeter * perimeter);
            if (circularity > 0.85)
                circleCount++;
        }
    }
    cout << "삼각형의 갯수: " << triangleCount << endl;
    cout << "사각형의 갯수: " << squareCount << endl;
    cout << "오각형의 갯수: " << pentagonCount << endl;
    cout << "육각형의 갯수: " << HexagonCount << endl;
    cout << "원의 갯수: " << circleCount << endl;

    Scalar color(0, 0, 255);
    drawContours(src, contours, -1, color, 2);

    imshow("Detected Shapes", src);
    waitKey(0);

    return 0;
}

// 실습과제 4

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main() {
    Mat src = imread("polygon2.bmp");
    if (src.empty()) { cerr << "failed" << endl; return -1; }

    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    Mat bin;
    threshold(gray, bin, 200, 255, THRESH_BINARY_INV | THRESH_OTSU);

    vector<vector<Point>> contours;
    findContours(bin, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

    double circlelen = 0, trianglelen = 0, rectlen = 0;
    double circlearea = 0, trianglearea = 0, rectarea = 0;

    for (int i = 0; i < contours.size(); i++) {
        drawContours(src, contours, -1, Scalar(0, 0, 255), 2);
        double peri = arcLength(contours[i], true);
        vector<Point> approx;
        approxPolyDP(contours[i], approx, 0.04 * peri, true);

        if (approx.size() == 3) {
            trianglelen = arcLength(contours[i], true);
            trianglearea = contourArea(contours[i]);
        }
        else if (approx.size() == 4) {
            rectlen = arcLength(contours[i], true);
            rectarea = contourArea(contours[i]);
        }
        else {
            double area = contourArea(contours[i]);
            double perimeter = arcLength(contours[i], true);
            double circularity = 4. * CV_PI * area / (perimeter * perimeter);
            if (circularity > 0.85) {
                circlelen = perimeter;
                circlearea = area;
            }
        }
    }
    cout << "원의 둘레 길이: " << circlelen << endl;
    cout << "원의 면적: " << circlearea << endl;
    cout << "삼각형의 둘레 길이: " << trianglelen << endl;
    cout << "삼각형의 면적: " << trianglearea << endl;
    cout << "사각형의 둘레 길이: " << rectlen << endl;
    cout << "사각형의 면적: " << rectarea << endl;

    imshow("src", src);
    waitKey();
    return 0;
}

// 실습과제 5

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(void) {
    Mat img = imread("ellipse.png");
    if (img.empty()) { cerr << "Image load failed!" << endl; return -1; }

    Mat tmp, dst;
    cvtColor(img, tmp, COLOR_BGR2GRAY);
    threshold(tmp, tmp, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);

    vector<vector<Point>> contours;
    findContours(tmp, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

    double length_c = arcLength(contours[0], false);  // 외각선 길이
    double cir = contourArea(contours[0], false);      // 외각선 면적
    cout << "원의 둘레 길이 : " << length_c << endl;
    cout << "원의 면적 : " << cir << endl;

    drawContours(img, contours, 0, Scalar(0, 0, 255), 2);

    vector<Point> approx;
    approxPolyDP(contours[0], approx, arcLength(contours[0], false) * 0.02, true);

    dst = img.clone();
    for (int j = 0; j < approx.size(); j++) {
        line(dst, approx[j], approx[(j + 1) % approx.size()], Scalar(255, 0, 0), 2);
    }

    double close_c = arcLength(approx, false);          // 근사화된 외각선 길이
    double close_cir = contourArea(approx, false);      // 근사화된 외각선 면적

    cout << "근사화된 둘레 길이 : " << close_c << endl;
    cout << "근사화된 면적 : " << close_cir << endl;

    imshow("img", img);
    imshow("tmp", tmp);
    imshow("dst", dst);

    waitKey();
    return 0;
}