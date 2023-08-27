/*
// 컨투어

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    Mat img_color;
    img_color = imread("test.jpg", IMREAD_COLOR);

    Mat img_gray;                                                       // grayscale로 변환
    cvtColor(img_color, img_gray, COLOR_BGR2GRAY);

    Mat img_binary;                                                     // 이진화
    threshold(img_gray, img_binary, 150, 255, THRESH_BINARY_INV);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));         // closing 모폴로지 적용
    morphologyEx(img_binary, img_binary, MORPH_CLOSE, kernel);

    vector<vector<Point>> contours;                                     // 컨투어 검출
    findContours(img_binary, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);
                                            // (입력 이미지, 외곽선 좌표, 저장 방식, 포인트 검출 방식)

    drawContours(img_color, contours, 0, Scalar(0, 0, 255), 3);         // 컨투어 출력
    drawContours(img_color, contours, 1, Scalar(0, 255, 0), 3);         // (입력 이미지, 컨투어 저장 배열, 컨투어 인덱스, 색, 선 굵기)

    imshow("result", img_color);
    waitKey(0);

    return 0;
}

*/

/*
// 컨투어 영역 크기

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
        double area = contourArea(contours[i]);                         // 컨투어 영역 크기 계산

        cout << i << '-' << area << endl;
    }

    imshow("result", img_color);
    waitKey(0);

    return 0;
}

*/

/*
// 컨투어 근사화

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
        double epsilon = 0.03 * arcLength(contours[i], true);           // 컨투어 둘레 길이 반환, (입력 컨투어, 폐곡선 여부)
        approxPolyDP(contours[i], approx, epsilon, true);               // 컨투어 근사, (입력 컨투어, 출력 컨투어, 근사 정확도, 폐곡선 여부)

        vector<vector<Point>> result;                                   // 컨투어 출력
        result.push_back(approx);
        drawContours(img_color, result, -1, Scalar(0, 255, 0), 3);
    }

    imshow("result", img_color);
    waitKey(0);

    return 0;
}

*/

/*
// 컨투어 무게중심

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
        mu = moments(contours[i]);                                      // 컨투어 무게중심 반환

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
// 경계 사각형

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
        Rect rect = boundingRect(contours[i]);                          // 컨투어 경계 사각형 반환
        rectangle(img_color, rect, Scalar(255, 255, 0), 3);

        Point2f points[4];                                              // 최소 크기의 경계 사각형 반환
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
// Convex Hull(: 컨투어의 모든 점을 포함하는 다각형)

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
        vector<Point> hull;                                             // convex hull 검출
        convexHull(Mat(contours[i]), hull, true);                       // (입력 컨투어, 출력 컨투어, 방향)

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
// Convexity Defects(: convec hull에서 컨투어가 오목하게 들어간 부분)

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
        vector<Point> hull;                                             // convex hull 검출
        convexHull(Mat(contours[i]), hull, true);

        vector<vector<Point>> result;
        result.push_back(hull);
        drawContours(img_color, result, -1, Scalar(255, 0, 255), 5);
    }

    for (size_t i = 0; i < contours.size(); i++)
    {
        vector<int> hull;                                               // convex hull 검출
        convexHull(Mat(contours[i]), hull, false);

        vector<Vec4i> defects;                                          // convexity defects 검출
        convexityDefects(contours[i], hull, defects);                   // (입력 컨투어, 입력 convex hull, 출력 defects)

        for (int j = 0; j < defects.size(); j++) 
        {
            Point start = contours[i][defects[j][0]];                   // convex hull과 convexity defect가 10000 이상 떨어져있을 때 컨투어 출력
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