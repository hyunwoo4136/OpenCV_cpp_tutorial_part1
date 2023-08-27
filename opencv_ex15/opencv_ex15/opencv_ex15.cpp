/*
// ������

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    Mat img_color;
    img_color = imread("test.jpg", IMREAD_COLOR);

    Mat img_gray;                                                       // grayscale�� ��ȯ
    cvtColor(img_color, img_gray, COLOR_BGR2GRAY);

    Mat img_binary;                                                     // ����ȭ
    threshold(img_gray, img_binary, 150, 255, THRESH_BINARY_INV);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));         // closing �������� ����
    morphologyEx(img_binary, img_binary, MORPH_CLOSE, kernel);

    vector<vector<Point>> contours;                                     // ������ ����
    findContours(img_binary, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);
                                            // (�Է� �̹���, �ܰ��� ��ǥ, ���� ���, ����Ʈ ���� ���)

    drawContours(img_color, contours, 0, Scalar(0, 0, 255), 3);         // ������ ���
    drawContours(img_color, contours, 1, Scalar(0, 255, 0), 3);         // (�Է� �̹���, ������ ���� �迭, ������ �ε���, ��, �� ����)

    imshow("result", img_color);
    waitKey(0);

    return 0;
}

*/

/*
// ������ ���� ũ��

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    Mat img_color;
    img_color = imread("test.jpg", IMREAD_COLOR);

    Mat img_gray;
    cvtColor(img_color, img_gray, COLOR_BGR2GRAY);

    Mat img_binary;
    threshold(img_gray, img_binary, 150, 255, THRESH_BINARY_INV);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
    morphologyEx(img_binary, img_binary, MORPH_CLOSE, kernel);

    vector<vector<Point>> contours;
    findContours(img_binary, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

    drawContours(img_color, contours, 0, Scalar(0, 0, 255), 3);
    drawContours(img_color, contours, 1, Scalar(0, 255, 0), 3);

    for (size_t i = 0; i < contours.size(); i++)
    {
        double area = contourArea(contours[i]);                         // ������ ���� ũ�� ���

        cout << i << '-' << area << endl;
    }

    imshow("result", img_color);
    waitKey(0);

    return 0;
}

*/

/*
// ������ �ٻ�ȭ

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    Mat img_color;
    img_color = imread("square.png", IMREAD_COLOR);

    Mat img_gray;
    cvtColor(img_color, img_gray, COLOR_BGR2GRAY);

    Mat img_binary;
    threshold(img_gray, img_binary, 150, 255, THRESH_BINARY);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
    morphologyEx(img_binary, img_binary, MORPH_CLOSE, kernel);

    vector<vector<Point>> contours;
    findContours(img_binary, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

    drawContours(img_color, contours, 0, Scalar(0, 0, 255), 3);

    vector<Point> approx;

    for (size_t i = 0; i < contours.size(); i++)
    {
        double epsilon = 0.03 * arcLength(contours[i], true);           // ������ �ѷ� ���� ��ȯ, (�Է� ������, �� ����)
        approxPolyDP(contours[i], approx, epsilon, true);               // ������ �ٻ�, (�Է� ������, ��� ������, �ٻ� ��Ȯ��, �� ����)

        vector<vector<Point>> result;                                   // ������ ���
        result.push_back(approx);
        drawContours(img_color, result, -1, Scalar(0, 255, 0), 3);
    }

    imshow("result", img_color);
    waitKey(0);

    return 0;
}

*/

/*
// ������ �����߽�

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    Mat img_color;
    img_color = imread("test.jpg", IMREAD_COLOR);

    Mat img_gray;
    cvtColor(img_color, img_gray, COLOR_BGR2GRAY);

    Mat img_binary;
    threshold(img_gray, img_binary, 150, 255, THRESH_BINARY_INV);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
    morphologyEx(img_binary, img_binary, MORPH_CLOSE, kernel);

    vector<vector<Point>> contours;
    findContours(img_binary, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

    drawContours(img_color, contours, 0, Scalar(0, 0, 255), 3);
    drawContours(img_color, contours, 1, Scalar(0, 255, 0), 3);

    for (size_t i = 0; i < contours.size(); i++)
    {
        Moments mu;
        mu = moments(contours[i]);                                      // ������ �����߽� ��ȯ

        int cx = static_cast<float>(mu.m10 / (mu.m00 + 1e-5));
        int cy = static_cast<float>(mu.m01 / (mu.m00 + 1e-5));
        circle(img_color, Point(cx, cy), 15, Scalar(0, 255, 255), -1);
    }

    imshow("result", img_color);
    waitKey(0);

    return 0;
}

*/

/*
// ��� �簢��

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    Mat img_color;
    img_color = imread("test.jpg", IMREAD_COLOR);

    Mat img_gray;
    cvtColor(img_color, img_gray, COLOR_BGR2GRAY);

    Mat img_binary;
    threshold(img_gray, img_binary, 150, 255, THRESH_BINARY_INV);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
    morphologyEx(img_binary, img_binary, MORPH_CLOSE, kernel);

    vector<vector<Point>> contours;
    findContours(img_binary, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

    drawContours(img_color, contours, 0, Scalar(0, 0, 255), 3);
    drawContours(img_color, contours, 1, Scalar(0, 255, 0), 3);

    for (size_t i = 0; i < contours.size(); i++)
    {
        Rect rect = boundingRect(contours[i]);                          // ������ ��� �簢�� ��ȯ
        rectangle(img_color, rect, Scalar(255, 255, 0), 3);

        Point2f points[4];                                              // �ּ� ũ���� ��� �簢�� ��ȯ
        RotatedRect box = minAreaRect(contours[i]);
        box.points(points);

        for (int j = 0; j < 4; j++)
            line(img_color, points[j], points[(j + 1) % 4], Scalar(255, 0, 255), 3);
    }

    imshow("result", img_color);
    waitKey(0);

    return 0;
}

*/

/*
// Convex Hull(: �������� ��� ���� �����ϴ� �ٰ���)

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    Mat img_color;
    img_color = imread("hand.png", IMREAD_COLOR);

    Mat img_gray;
    cvtColor(img_color, img_gray, COLOR_BGR2GRAY);

    Mat img_binary;
    threshold(img_gray, img_binary, 150, 255, THRESH_BINARY);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
    morphologyEx(img_binary, img_binary, MORPH_CLOSE, kernel);

    vector<vector<Point>> contours;
    findContours(img_binary, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

    drawContours(img_color, contours, 0, Scalar(255, 0, 0), 3);

    for (size_t i = 0; i < contours.size(); i++)
    {
        vector<Point> hull;                                             // convex hull ����
        convexHull(Mat(contours[i]), hull, true);                       // (�Է� ������, ��� ������, ����)

        vector<vector<Point>> result;
        result.push_back(hull);
        drawContours(img_color, result, -1, Scalar(255, 0, 255), 5);
    }

    imshow("result", img_color);
    waitKey(0);

    return 0;
}

*/

///*
// Convexity Defects(: convec hull���� ����� �����ϰ� �� �κ�)

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    Mat img_color;
    img_color = imread("hand.png", IMREAD_COLOR);

    Mat img_gray;
    cvtColor(img_color, img_gray, COLOR_BGR2GRAY);

    Mat img_binary;
    threshold(img_gray, img_binary, 150, 255, THRESH_BINARY);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
    morphologyEx(img_binary, img_binary, MORPH_CLOSE, kernel);

    vector<vector<Point>> contours;
    findContours(img_binary, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

    drawContours(img_color, contours, 0, Scalar(255, 0, 0), 3);

    for (size_t i = 0; i < contours.size(); i++)
    {
        vector<Point> hull;                                             // convex hull ����
        convexHull(Mat(contours[i]), hull, true);

        vector<vector<Point>> result;
        result.push_back(hull);
        drawContours(img_color, result, -1, Scalar(255, 0, 255), 5);
    }

    for (size_t i = 0; i < contours.size(); i++)
    {
        vector<int> hull;                                               // convex hull ����
        convexHull(Mat(contours[i]), hull, false);

        vector<Vec4i> defects;                                          // convexity defects ����
        convexityDefects(contours[i], hull, defects);                   // (�Է� ������, �Է� convex hull, ��� defects)

        for (int j = 0; j < defects.size(); j++) 
        {
            Point start = contours[i][defects[j][0]];                   // convex hull�� convexity defect�� 10000 �̻� ���������� �� ������ ���
            Point end = contours[i][defects[j][1]];
            Point far = contours[i][defects[j][2]];
            int d = defects[j][3];

            if (d > 10000)
            {
                line(img_color, start, end, Scalar(0, 255, 0), 3);
                circle(img_color, far, 5, Scalar(0, 0, 255), -1);
            }
        }
    }

    imshow("result", img_color);
    waitKey(0);

    return 0;
}

//*/