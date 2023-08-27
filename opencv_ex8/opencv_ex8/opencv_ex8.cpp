/*
// 이미지 회전 

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
    Mat img_color;
    img_color = imread("cat.jpg", IMREAD_COLOR);
    imshow("color", img_color);

    int height = img_color.rows;
    int width = img_color.cols;

    Mat M = getRotationMatrix2D(Point(width / 2.0, height / 2.0), 45, 1);   // 회전 행렬 생성
                                                        // (회전 중심, 회전 각도, 이미지 배율)
    Mat img_rotated;
    warpAffine(img_color, img_rotated, M, Size(width, height));     // 이미지에 회전 행렬 적용

    imshow("rotation", img_rotated);
    waitKey(0);

    return 0;
}

*/

/*
// 이미지 크기 조정

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
    Mat img_color;

    img_color = imread("cat.jpg");
    imshow("original", img_color);

    Mat img_result;

    resize(img_color, img_result, Size(), 2, 2, INTER_CUBIC);   // 크기 조정 이미지 생성
                            // (입력 이미지, 출력 이미지, 이미지 크기, 크기 비율, 보간법)
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
// 이미지 이동

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
    Mat img_color;
    img_color = imread("cat.jpg");
    imshow("original", img_color);

    int height = img_color.rows;
    int width = img_color.cols;

    Mat M(2, 3, CV_64F, Scalar(0.0));                               // 이동 행렬 생성

    M.at<double>(0, 0) = 1;
    M.at<double>(1, 1) = 1;
    M.at<double>(0, 2) = 100;
    M.at<double>(1, 2) = 50;

    Mat img_translation;
    warpAffine(img_color, img_translation, M, Size(width, height)); // 이미지에 이동 행렬 적용

    imshow("translation", img_translation);
    waitKey(0);
}

*/

/*
// 아핀 변환

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

        if (waitKey(1) == 32)                               // 스페이스바 입력 대기 
            break;
    }

    int height = img_color.rows;
    int width = img_color.cols;

    Point2f dst[3];                                         // 변환 후 좌표 위치 
    dst[0] = src[0];
    dst[1] = Point2f(src[1].x, src[1].y + 100);
    dst[2] = src[2];

    Mat M;                                                  // 변환 행렬 생성
    M = getAffineTransform(src, dst);

    Mat img_result;                                         // 변환 행렬 적용
    warpAffine(img_color, img_result, M, Size(width, height));

    imshow("result", img_result);
    waitKey(0);

    return 0;
}

*/

///*
// 퍼스펙티브 변환

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

    Point2f dst[4];                                         // 변환 후 좌표
    dst[0] = Point2f(0, 0);
    dst[1] = Point2f(width, 0);
    dst[2] = Point2f(0, height);
    dst[3] = Point2f(width, height);


    Mat M;                                                  // 변환 행렬 생성
    M = getPerspectiveTransform(src, dst);


    Mat img_result;                                         // 변환 행렬 적용
    warpPerspective(img_original, img_result, M, Size(width, height));


    imshow("result", img_result);
    waitKey(0);

    return 0;
}

//*/