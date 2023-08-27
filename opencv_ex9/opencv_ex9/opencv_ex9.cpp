/*
// 블러링

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	Mat img;
	img = imread("test.png");

	Mat kernel = Mat(5, 5, CV_32F, Scalar(1 / 25.0));	// 마스크 커널 생성

	Mat dst;											// 마스크 커널로 컨볼루션 연산
	filter2D(img, dst, -1, kernel);

	imshow("Original", img);
	imshow("Result", dst);

	waitKey(0);
}

*/

/*
// 평균 블러링(커널의 평균값 사용)

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	Mat img;
	img = imread("test.png");

	Mat img_blur;								// 평균 블러링 이미지 생성
	blur(img, img_blur, Size(5, 5));

	imshow("Original", img);
	imshow("Result", img_blur);

	waitKey(0);
}

*/

/*
// 가우시안 블러링(커널에 가우시안 가중치 적용, 에지 유지 가능)

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	Mat img;
	img = imread("test.png");

	Mat img_blur;								// 가우시안 블러링 이미지 생성
	GaussianBlur(img, img_blur, Size(5, 5), 0);

	imshow("Original", img);
	imshow("Result", img_blur);

	waitKey(0);
}

*/

/*
// 중간값 블러링(커널 요소의 중간값 사용, 무작위 노이즈 제거, 에지 소멸)

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	Mat img;
	img = imread("median.png");

	Mat img_blur;								// 중간값 블러링 이미지 생성
	medianBlur(img, img_blur, 5);

	imshow("Original", img);
	imshow("Result", img_blur);

	waitKey(0);
}

*/

/*
// 양방향 블러링(에지를 보존하며 노이즈 제거)

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	Mat img;
	img = imread("texture.png");

	Mat img_blur;								// 양방향 블러링 이미지 생성
	bilateralFilter(img, img_blur, 9, 75, 75);

	imshow("Original", img);
	imshow("Result", img_blur);

	waitKey(0);
}

*/

/*
// 소벨 에지 검출([-1, 0, 1; -2, 0, 2; -1, 0, 0] 커널로 수직 방향 에지 검출)

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	Mat img_color;
	img_color = imread("circle.png", IMREAD_COLOR);

	Mat img_gray;
	cvtColor(img_color, img_gray, COLOR_BGR2GRAY);

	Mat img_sobel_x;							// x 방향 소벨 에지 검출
	Sobel(img_gray, img_sobel_x, CV_64F, 1, 0, 3);
	convertScaleAbs(img_sobel_x, img_sobel_x);

	Mat img_sobel_y;							// y 방향 소벨 에지 검출 
	Sobel(img_gray, img_sobel_y, CV_64F, 0, 1, 3);
	convertScaleAbs(img_sobel_y, img_sobel_y);

	Mat img_sobel;								// 양방향 에지 결합
	addWeighted(img_sobel_x, 1, img_sobel_y, 1, 0, img_sobel);


	imshow("Sobel X", img_sobel_x);
	imshow("Sobel Y", img_sobel_y);
	imshow("Sobel", img_sobel);

	waitKey(0);

	return 0;
}

*/

///*
// 캐니 에지 검출(2개의 임계값으로 하나의 픽셀로 구성된 에지 검출)

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat img_color = imread("house.png", IMREAD_COLOR);

	Mat img_gray;
	cvtColor(img_color, img_gray, COLOR_BGR2GRAY);

	Mat img_edge;								// 블러 후 캐니 에지 검출
	blur(img_gray, img_gray, Size(3, 3));
	Canny(img_gray, img_edge, 50, 150, 3);

	imshow("Original", img_gray);
	imshow("Canny Edge", img_edge);
	waitKey(0);

	return 0;
}

//*/