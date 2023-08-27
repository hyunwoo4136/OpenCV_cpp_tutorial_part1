/*
// ����

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	Mat img;
	img = imread("test.png");

	Mat kernel = Mat(5, 5, CV_32F, Scalar(1 / 25.0));	// ����ũ Ŀ�� ����

	Mat dst;											// ����ũ Ŀ�η� ������� ����
	filter2D(img, dst, -1, kernel);

	imshow("Original", img);
	imshow("Result", dst);

	waitKey(0);
}

*/

/*
// ��� ����(Ŀ���� ��հ� ���)

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	Mat img;
	img = imread("test.png");

	Mat img_blur;								// ��� ���� �̹��� ����
	blur(img, img_blur, Size(5, 5));

	imshow("Original", img);
	imshow("Result", img_blur);

	waitKey(0);
}

*/

/*
// ����þ� ����(Ŀ�ο� ����þ� ����ġ ����, ���� ���� ����)

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	Mat img;
	img = imread("test.png");

	Mat img_blur;								// ����þ� ���� �̹��� ����
	GaussianBlur(img, img_blur, Size(5, 5), 0);

	imshow("Original", img);
	imshow("Result", img_blur);

	waitKey(0);
}

*/

/*
// �߰��� ����(Ŀ�� ����� �߰��� ���, ������ ������ ����, ���� �Ҹ�)

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	Mat img;
	img = imread("median.png");

	Mat img_blur;								// �߰��� ���� �̹��� ����
	medianBlur(img, img_blur, 5);

	imshow("Original", img);
	imshow("Result", img_blur);

	waitKey(0);
}

*/

/*
// ����� ����(������ �����ϸ� ������ ����)

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	Mat img;
	img = imread("texture.png");

	Mat img_blur;								// ����� ���� �̹��� ����
	bilateralFilter(img, img_blur, 9, 75, 75);

	imshow("Original", img);
	imshow("Result", img_blur);

	waitKey(0);
}

*/

/*
// �Һ� ���� ����([-1, 0, 1; -2, 0, 2; -1, 0, 0] Ŀ�η� ���� ���� ���� ����)

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	Mat img_color;
	img_color = imread("circle.png", IMREAD_COLOR);

	Mat img_gray;
	cvtColor(img_color, img_gray, COLOR_BGR2GRAY);

	Mat img_sobel_x;							// x ���� �Һ� ���� ����
	Sobel(img_gray, img_sobel_x, CV_64F, 1, 0, 3);
	convertScaleAbs(img_sobel_x, img_sobel_x);

	Mat img_sobel_y;							// y ���� �Һ� ���� ���� 
	Sobel(img_gray, img_sobel_y, CV_64F, 0, 1, 3);
	convertScaleAbs(img_sobel_y, img_sobel_y);

	Mat img_sobel;								// ����� ���� ����
	addWeighted(img_sobel_x, 1, img_sobel_y, 1, 0, img_sobel);


	imshow("Sobel X", img_sobel_x);
	imshow("Sobel Y", img_sobel_y);
	imshow("Sobel", img_sobel);

	waitKey(0);

	return 0;
}

*/

///*
// ĳ�� ���� ����(2���� �Ӱ谪���� �ϳ��� �ȼ��� ������ ���� ����)

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat img_color = imread("house.png", IMREAD_COLOR);

	Mat img_gray;
	cvtColor(img_color, img_gray, COLOR_BGR2GRAY);

	Mat img_edge;								// �� �� ĳ�� ���� ����
	blur(img_gray, img_gray, Size(3, 3));
	Canny(img_gray, img_edge, 50, 150, 3);

	imshow("Original", img_gray);
	imshow("Canny Edge", img_edge);
	waitKey(0);

	return 0;
}

//*/