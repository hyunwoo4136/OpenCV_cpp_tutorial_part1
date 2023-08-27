/*
// ���� �Ӱ谪 ��� ����ȭ

#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;
using namespace std;


static void on_trackbar( int, void* )							// Ʈ���� �ݹ� �Լ�
{
}

int main()
{
	Mat img_color;
	img_color = imread("red ball.png", IMREAD_COLOR);
	if (img_color.empty())
	{
		cout << "�̹��� ������ ���� �� �����ϴ�." << endl;
		return -1;
	}

	Mat img_gray;
	cvtColor(img_color, img_gray, COLOR_BGR2GRAY);
	imshow("Grayscale", img_gray);

	namedWindow("Binary");
	createTrackbar("threshold", "Binary", 0, 255, on_trackbar);	// Ʈ���� ���� �� �ʱ�ȭ
	setTrackbarPos("threshold", "Binary", 127);

	while(1)
	{
		int thresh = getTrackbarPos("threshold", "Binary");		// Ʈ���� ��ġ read

		Mat img_binary;
		threshold(img_gray, img_binary, thresh, 255, THRESH_BINARY_INV);	// �̹��� ����ȭ

		imshow("Binary", img_binary);

		if (waitKey(1) == 27)
			break;
	}
}

*/

///*
// ������ ����ȭ

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat img_color;
	img_color = imread("copy.png", IMREAD_COLOR);
	if (img_color.empty())
	{
		cout << "�̹��� ������ ���� �� �����ϴ�." << endl;
		return -1;
	}

	Mat img_gray;
	cvtColor(img_color, img_gray, COLOR_BGR2GRAY);

	Mat img_binary;
	adaptiveThreshold(img_gray, img_binary, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 5, 4);	// ������ ����ȭ
											// (img, img, �ִ� �Ӱ谪, ��� ���, Ÿ��, ���� ������, ��տ��� ������ ��)
	imshow("Grayscale", img_gray);
	imshow("Binary", img_binary);
	waitKey(0);
}

//*/