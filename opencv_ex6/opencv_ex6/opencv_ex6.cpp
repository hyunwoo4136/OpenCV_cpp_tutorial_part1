/*
// 랜덤색 사용

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    int width = 640;
    int height = 480;

    Mat img(height, width, CV_8UC3);

    RNG rng(-1);

    int img_h = img.rows;
    int img_w = img.cols;

    for (int y = 0; y < img_h; y++) 
    {
        uchar* pointer_input = img.ptr<uchar>(y);
        for (int x = 0; x < img_w; x++) 
        {
            pointer_input[x * 3 + 0] = rng.uniform(0, 256);
            pointer_input[x * 3 + 1] = rng.uniform(0, 256);
            pointer_input[x * 3 + 2] = rng.uniform(0, 256);
        }
    }

    imshow("drawing", img);
    waitKey(0);
}

*/

/*
// 사각형 그리기

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
    int width = 640;
    int height = 480;

    Mat img(height, width, CV_8UC3, Scalar(0, 0, 0));

    rectangle(img, Point(50, 50), Point(450, 450), Scalar(0, 0, 255), 3);

    rectangle(img, Point(150, 200), Point(250, 300), Scalar(0, 255, 0), -1);

    rectangle(img, Rect(300, 150, 50, 1000), Scalar(255, 0, 255), -1);

    imshow("result", img);
    waitKey(0);

    return 0;
}

*/

/*
// 원 그리기

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
    int width = 640;
    int height = 480;

    Mat img(height, width, CV_8UC3, Scalar(0, 0, 0));

    circle(img, Point(320, 240), 10, Scalar(0, 255, 0), -1);

    circle(img, Point(320, 240), 100, Scalar(0, 0, 255), 1);

    imshow("result", img);
    waitKey(0);
}

*/

/*
// 선분 그리기

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
    int width = 640;
    int height = 480;

    Mat img(height, width, CV_8UC3, Scalar(0, 0, 0));

    line(img, Point(width - 1, 0), Point(0, height - 1), Scalar(0, 255, 0), 3);
    line(img, Point(0, 0), Point(width - 1, height - 1), Scalar(0, 0, 255), 3);

    imshow("result", img);
    waitKey(0);

    return 0;
}

*/

/*
// 타원 그리기

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
    int width = 640;
    int height = 480;

    Mat img(height, width, CV_8UC3, Scalar(0, 0, 0));

    Point center(int(width / 2), int(height / 2));

    ellipse(img, center, Size(10, 200), 0, 0, 360, Scalar(0, 255, 0), 3);

    ellipse(img, center, Size(10, 200), 45, 0, 360, Scalar(0, 0, 255), 3);

    ellipse(img, center, Size(10, 200), -45, 0, 360, Scalar(255, 0, 0), 3);

    imshow("result", img);
    waitKey(0);

    return 0;
}

*/

/*
// 원호 그리기

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
    int width = 640;
    int height = 480;

    Mat img(height, width, CV_8UC3, Scalar(0, 0, 0));

    Point center(int(width / 2), int(height / 2));

    ellipse(img, center, Size(100, 100), 0, 0, 90, Scalar(0, 0, 255), 3);

    imshow("result", img);
    waitKey(0);

    return 0;
}

*/

/*
// 폴리곤 그리기

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    int width = 640;
    int height = 640;

    Mat img(height, width, CV_8UC3, Scalar(0, 0, 0));

    Scalar red(0, 0, 255);
    Scalar green(0, 255, 0);
    Scalar yellow(0, 255, 255);

    int thickness = 2;

    vector<Point> contour;
    contour.push_back(Point(315, 50));
    contour.push_back(Point(570, 240));
    contour.push_back(Point(475, 550));
    contour.push_back(Point(150, 550));
    contour.push_back(Point(50, 240));

    const Point* pts1 = (const cv::Point*)Mat(contour).data;
    int npts1 = Mat(contour).rows;

    polylines(img, &pts1, &npts1, 1, false, red, thickness);

    contour.clear();
    contour.push_back(Point(315, 160));
    contour.push_back(Point(150, 280));
    contour.push_back(Point(210, 480));
    contour.push_back(Point(420, 480));
    contour.push_back(Point(480, 280));

    const Point* pts2 = (const cv::Point*)Mat(contour).data;
    int npts2 = Mat(contour).rows;

    polylines(img, &pts2, &npts2, 1, true, green, thickness);

    contour.clear();
    contour.push_back(Point(320, 240));
    contour.push_back(Point(410, 315));
    contour.push_back(Point(380, 415));
    contour.push_back(Point(265, 415));
    contour.push_back(Point(240, 315));

    const Point* pts3 = (const cv::Point*)Mat(contour).data;
    int npts3 = Mat(contour).rows;

    fillPoly(img, &pts3, &npts3, 1, yellow);

    imshow("result", img);
    waitKey(0);

    return 0;
}

*/

///*
// 글자 그리기

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
    int img_w = 640;
    int img_h = 480;

    Mat img(img_h, img_w, CV_8UC3, Scalar(0, 0, 0));

    Scalar red(0, 0, 255);
    Scalar green(0, 255, 0);
    Scalar white(255, 255, 255);
    Scalar yellow(0, 255, 255);

    int center_x = int(img_w / 2.0);
    int center_y = int(img_h / 2.0);

    int thickness = 2;
    Point location(center_x - 200, center_y - 100);
    int font = FONT_HERSHEY_SCRIPT_SIMPLEX;
    double fontScale = 3.5;
    putText(img, "OpenCV", location, font, fontScale, yellow, thickness);

    location = Point(center_x - 150, center_y + 20);
    font = FONT_ITALIC;
    fontScale = 2;
    putText(img, "Tutorial", location, font, fontScale, red, thickness);

    location = Point(center_x - 250, center_y + 100);
    font = FONT_HERSHEY_SIMPLEX;
    fontScale = 1.5;
    putText(img, "webnautes.tistory.com", location, font, fontScale, white, thickness);

    location = Point(center_x - 130, center_y + 150);
    font = FONT_HERSHEY_COMPLEX;
    fontScale = 1.2;
    putText(img, "webnautes", location, font, fontScale, green, thickness);

    imshow("drawing", img);
    waitKey(0);

    return 0;
}

//*/