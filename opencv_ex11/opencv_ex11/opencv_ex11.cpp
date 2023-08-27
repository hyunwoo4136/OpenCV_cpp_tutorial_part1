/*
// 허프 선 변환(두 점을 지나는 무수히 많은 직선의 교차점을 찾아 직선 검출)

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    Mat img_edge, img_result;

    Mat img_src = imread("test.jpg", IMREAD_GRAYSCALE);

    Canny(img_src, img_edge, 50, 150);
    cvtColor(img_edge, img_result, COLOR_GRAY2BGR);

    vector<Vec2f> lines;                                    // 허프 라인 검출 
    HoughLines(img_edge, lines, 1, CV_PI / 180, 150);       // rho, theta 반환 
                                // (입력 이미지, 출력 배열, rho, theta, threshold)

    for (size_t i = 0; i < lines.size(); i++)
    {
        float rho = lines[i][0], theta = lines[i][1];       // rho 및 theta 저장
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);              // 직교 좌표계로 변환
        double x0 = a * rho, y0 = b * rho;

        pt1.x = cvRound(x0 + 1000 * (-b));                  // 직선 길이 지정
        pt1.y = cvRound(y0 + 1000 * (a));
        pt2.x = cvRound(x0 - 1000 * (-b));
        pt2.y = cvRound(y0 - 1000 * (a));

        line(img_result, pt1, pt2, Scalar(0, 0, 255), 3);   // 직선 출력
    }

    imshow("Source", img_src);
    imshow("Standard Hough Line Transform", img_result);

    waitKey();
    return 0;
}

*/

///*
// 확률적 허프 선 변환

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    Mat img_edge, img_result;

    Mat src = imread("test.jpg", IMREAD_GRAYSCALE);

    Canny(src, img_edge, 50, 150);
    cvtColor(img_edge, img_result, COLOR_GRAY2BGR);

    vector<Vec4i> linesP;                                   // 확률적 허프 라인 검출
    HoughLinesP(img_edge, linesP, 1, CV_PI / 180, 50, 50, 5);   // 직선의 시작과 끝점 반환
                // (입력 이미지, 출력 배열, rho, theta, threshold, 최소 선 길이, 선 사이 거리)

    for (size_t i = 0; i < linesP.size(); i++)
    {
        Vec4i l = linesP[i];                                // 직선 출력
        line(img_result, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, LINE_AA);
    }

    imshow("Source", src);
    imshow("Probabilistic Line Transform", img_result);

    waitKey();
    return 0;
}

//*/

/*
// 허프 원 변환(에지의 그레디언트를 이용해 원 검출)

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    Mat img_gray;

    img_gray = imread("test1.jpg", IMREAD_GRAYSCALE);
    medianBlur(img_gray, img_gray, 5);
    Mat img_color;
    cvtColor(img_gray, img_color, COLOR_GRAY2BGR);

    vector<Vec3f> circles;                                  // 허프 원 검출 
    HoughCircles(img_gray, circles, HOUGH_GRADIENT, 1, 20, 50, 35, 0, 0);   // 원 중신 좌표 및 반지름 반환
            // (입력 이미지, 출력 배열, 검출 방식, 해상도, 원 사이 최소 거리, threshold1, threshold2, 최소 반지름, 최대 반지름)

    for (size_t i = 0; i < circles.size(); i++)
    {
        Vec3i c = circles[i];                               // 원 출력
        Point center(c[0], c[1]);
        int radius = c[2];

        circle(img_color, center, radius, Scalar(0, 255, 0), 2);
        circle(img_color, center, 2, Scalar(0, 0, 255), 3);
    }

    imshow("detected circles", img_color);
    waitKey(0);
    destroyAllWindows();

    return 0;
}

*/