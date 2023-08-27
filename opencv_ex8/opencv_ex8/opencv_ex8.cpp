/*
// �̹��� ȸ�� 

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
    Mat img_color;
    img_color = imread("cat.jpg", IMREAD_COLOR);
    imshow("color", img_color);

    int height = img_color.rows;
    int width = img_color.cols;

    Mat M = getRotationMatrix2D(Point(width / 2.0, height / 2.0), 45, 1);   // ȸ�� ��� ����
                                                        // (ȸ�� �߽�, ȸ�� ����, �̹��� ����)
    Mat img_rotated;
    warpAffine(img_color, img_rotated, M, Size(width, height));     // �̹����� ȸ�� ��� ����

    imshow("rotation", img_rotated);
    waitKey(0);

    return 0;
}

*/

/*
// �̹��� ũ�� ����

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
    Mat img_color;

    img_color = imread("cat.jpg");
    imshow("original", img_color);

    Mat img_result;

    resize(img_color, img_result, Size(), 2, 2, INTER_CUBIC);   // ũ�� ���� �̹��� ����
                            // (�Է� �̹���, ��� �̹���, �̹��� ũ��, ũ�� ����, ������)
    imshow("x2 INTER_CUBIC", img_result);   

    int width = img_color.cols;
    int height = img_color.rows;

    resize(img_color, img_result, Size(3 * width, 3 * height), INTER_LINEAR);
    imshow("x3 INTER_LINEAR", img_result);

    resize(img_color, img_result, Size(), 0.5, 0.5, INTER_AREA);
    imshow("x0.5 INTER_AREA", img_result);

    waitKey(0);

    return 0;
}

*/

/*
// �̹��� �̵�

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
    Mat img_color;
    img_color = imread("cat.jpg");
    imshow("original", img_color);

    int height = img_color.rows;
    int width = img_color.cols;

    Mat M(2, 3, CV_64F, Scalar(0.0));                               // �̵� ��� ����

    M.at<double>(0, 0) = 1;
    M.at<double>(1, 1) = 1;
    M.at<double>(0, 2) = 100;
    M.at<double>(1, 2) = 50;

    Mat img_translation;
    warpAffine(img_color, img_translation, M, Size(width, height)); // �̹����� �̵� ��� ����

    imshow("translation", img_translation);
    waitKey(0);
}

*/

/*
// ���� ��ȯ

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Point2f src[3];
int idx = 0;
Mat img_color;

void mouse_callback(int event, int x, int y, int flags, void* userdata)
{
    if (event == EVENT_LBUTTONDOWN)
    {
        src[idx] = Point2f(x, y);
        idx++;

        cout << "(" << x << ", " << y << ")" << endl;

        circle(img_color, Point(x, y), 3, Scalar(0, 0, 255), -1);
    }
}

int main()
{
    namedWindow("source");
    setMouseCallback("source", mouse_callback);

    img_color = imread("test.png");

    while (1) 
    {
        imshow("source", img_color);

        if (waitKey(1) == 32)                               // �����̽��� �Է� ��� 
            break;
    }

    int height = img_color.rows;
    int width = img_color.cols;

    Point2f dst[3];                                         // ��ȯ �� ��ǥ ��ġ 
    dst[0] = src[0];
    dst[1] = Point2f(src[1].x, src[1].y + 100);
    dst[2] = src[2];

    Mat M;                                                  // ��ȯ ��� ����
    M = getAffineTransform(src, dst);

    Mat img_result;                                         // ��ȯ ��� ����
    warpAffine(img_color, img_result, M, Size(width, height));

    imshow("result", img_result);
    waitKey(0);

    return 0;
}

*/

///*
// �۽���Ƽ�� ��ȯ

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Point2f src[4];
int idx = 0;
Mat img_color;

void mouse_callback(int event, int x, int y, int flags, void* userdata)
{
    if (event == EVENT_LBUTTONDOWN)
    {
        src[idx] = Point2f(x, y);
        idx++;

        cout << "(" << x << ", " << y << ")" << endl;

        circle(img_color, Point(x, y), 10, Scalar(0, 0, 255), -1);
    }
}

int main()
{
    namedWindow("source");
    setMouseCallback("source", mouse_callback);

    img_color = imread("road.jpg");
    Mat img_original;
    img_original = img_color.clone();

    while (1) 
    {
        imshow("source", img_color);

        if (waitKey(1) == 32)
            break;
    }

    int height = img_color.rows;
    int width = img_color.cols;

    Point2f dst[4];                                         // ��ȯ �� ��ǥ
    dst[0] = Point2f(0, 0);
    dst[1] = Point2f(width, 0);
    dst[2] = Point2f(0, height);
    dst[3] = Point2f(width, height);


    Mat M;                                                  // ��ȯ ��� ����
    M = getPerspectiveTransform(src, dst);


    Mat img_result;                                         // ��ȯ ��� ����
    warpPerspective(img_original, img_result, M, Size(width, height));


    imshow("result", img_result);
    waitKey(0);

    return 0;
}

//*/