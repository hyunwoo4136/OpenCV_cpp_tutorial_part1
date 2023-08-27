/*
// 블렌딩

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    Mat img1, img2;

    double alpha = 0.0;
    double beta = 1.0;

    while (alpha <= 1.0) 
    {
        img1 = imread("beach.png", IMREAD_COLOR);
        img2 = imread("cat.png", IMREAD_COLOR);

        Mat dst;
        addWeighted(img1, alpha, img2, beta, 0, dst);       // 블랜딩

        cout << alpha << " " << beta << endl;

        imshow("dst", dst);
        waitKey(0);

        alpha = alpha + 0.1;
        beta = beta - 0.1;
    }

    return 0;
}

*/

///*
// 차영상

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
    Mat img_background, img_object;
    img_background = imread("background.png", IMREAD_GRAYSCALE);
    img_object = imread("object.png", IMREAD_GRAYSCALE);

    Mat img_sub;
    subtract(img_object, img_background, img_sub);          // 차영상 생성

    Mat img_binary;
    threshold(img_sub, img_binary, 50, 255, THRESH_BINARY);

    imshow("background", img_background);
    imshow("object", img_object);
    imshow("sub", img_sub);
    imshow("binary", img_binary);
    waitKey(0);

    return 0;
}

//*/

/*
// 이미지 비트 연산

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
    Mat img_logo, img_background;
    img_logo = imread("logo.png", IMREAD_COLOR);
    img_background = imread("sky.png", IMREAD_COLOR);

    Mat img_gray;                                           // 로고 이미지 grayscale 변환
    cvtColor(img_logo, img_gray, COLOR_BGR2GRAY);

    Mat img_mask;                                           // 로고 이미지 이진화
    threshold(img_gray, img_mask, 200, 255, THRESH_BINARY);

    Mat img_mask_inv;                                       // 이진화된 로고 이미지 반전
    bitwise_not(img_mask, img_mask_inv);

    int height = img_logo.rows;
    int width = img_logo.cols;

    Mat img_roi(img_background, Rect(0, 0, width, height)); 

    Mat img1, img2;                                         
    bitwise_and(img_logo, img_logo, img1, img_mask_inv);    // 로고 이미지에서 배경 제거
    bitwise_and(img_roi, img_roi, img2, img_mask);          // 배경 이미지에서 로고 영역 제거

    Mat dst;
    add(img1, img2, dst);                                   // 두 이미지 합성

    dst.copyTo(img_background(Rect(0, 0, width, height)));  // 배경 이미지에 합성 이미지 카피

    imshow("background", img_background);
    // imshow("logo", img_logo);
    // imshow("img_mask_inv", img_mask_inv);
    // imshow("img_mask", img_mask);
    // imshow("img1", img1);
    // imshow("img2", img2);
    // imshow("dst", dst);
    waitKey(0);
}

*/

/*
// 관심 영역 설정

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
    Mat img_color;
    img_color = imread("green.png", IMREAD_COLOR);

    int height = img_color.rows;
    int width = img_color.cols;

    int center_x = (int)width * 0.5;
    int center_y = (int)height * 0.5;

    Mat img_roi;                                            // 관심 영역 이미지 생성
    img_roi = img_color(Rect(center_x - 100, center_y - 100, 200, 200)).clone();

    Mat img_gray;
    cvtColor(img_roi, img_gray, COLOR_BGR2GRAY);
    Mat img_edge;
    Canny(img_gray, img_edge, 100, 300);

    cvtColor(img_edge, img_edge, COLOR_GRAY2BGR);

    img_edge.copyTo(img_color(Rect(center_x - 100, center_y - 100, 200, 200)));

    imshow("COLOR", img_color);
    imshow("ROI", img_roi);
    waitKey(0);

    destroyAllWindows();
}

*/