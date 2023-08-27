/*
// Mat ��ü: �̹��� �����͸� ������ �ϳ��� ��ü�� ó���ϸ� ������ ��ü���� ������ ��ħ(Python �����̴� X)

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	Mat img_color;

	img_color = imread("cat on laptop.jpg", IMREAD_GRAYSCALE);

	Mat img_sub1(img_color, Rect(400, 120, 350, 200));			// ���簢�� ���� ����(x, y, x ����, y ����) 

	Mat img_sub2 = img_color(Range(100, 150), Range::all());	// ���� ����(y ����, y ��, x ����, x ��)

	threshold(img_sub1, img_sub1, 127, 255, THRESH_BINARY);		// �̹��� ����ȭ

	imshow("img_color", img_color);
	imshow("img_sub1", img_sub1);
	imshow("img_sub2", img_sub2);

	waitKey(0);
}

*/

/*
// �̹��� ����

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	Mat img_color;

	img_color = imread("cat on laptop.jpg", IMREAD_GRAYSCALE);

	Mat img_copyed1 = img_color.clone();						// �̹��� ��ü ���� 1

	Mat img_copyed2;
	img_color.copyTo(img_copyed2);								// �̹��� ��ü ���� 2

	threshold(img_color, img_color, 127, 255, THRESH_BINARY);	// �̹��� ����ȭ

	imshow("img_color", img_color);
	imshow("img_sub1", img_copyed1);
	imshow("img_sub2", img_copyed2);

	waitKey(0);
}

*/

/*
// �ȼ� ���� 

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat img_color = imread("apple.jpg", IMREAD_COLOR);

	int height = img_color.rows;								// �̹��� ��, �� ũ��
	int width = img_color.cols;

	Mat img_gray(height, width, CV_8UC1);

	for (int y = 0; y < height; y++)							// grayscale�� ��ȯ
	{
		uchar* pointer_input = img_color.ptr<uchar>(y);			// y ��ǥ�� �̿��� ������ ���
		uchar* pointer_output = img_gray.ptr<uchar>(y);

		for (int x = 0; x < width; x++)
		{
				uchar b = pointer_input[x * 3 + 0];				// �÷� �̹����� bgr ä�� read
				uchar g = pointer_input[x * 3 + 1];				// b, g, r 3 ä��
				uchar r = pointer_input[x * 3 + 2];

				pointer_output[x] = r * 0.2126 + g * 0.7152 + b * 0.0722;
		}
	}

	Mat img_result;

	cvtColor(img_gray, img_result, COLOR_GRAY2BGR);

	for (int y = 100; y < 150; y++)								// ���� ���� �� ����
	{
		uchar* pointer_input = img_result.ptr<uchar>(y);

		for (int x = 150; x < 200; x++) 
		{
			pointer_input[x * 3 + 0] = 0;
			pointer_input[x * 3 + 1] = 255;						// �ʷϻ����� ����
			pointer_input[x * 3 + 2] = 0;
		}
	}


	imshow("color", img_color);
	imshow("result", img_result);

	waitKey(0);


	return 0;
}

*/

///*
// �̹��� ä�� �и� �� ��ġ��

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat img_color;

	img_color = imread("color.png", IMREAD_COLOR);

	Mat img_channels[3];										// �÷� �̹��� ä�κ� �и�
	split(img_color, img_channels);

	vector<Mat> channels;										// b, r ������ �ٲ� �̹��� ä�� ����
	channels.push_back(img_channels[2]);
	channels.push_back(img_channels[1]);
	channels.push_back(img_channels[0]);

	Mat img_result;
	merge(channels, img_result);								// �̹��� ä�� ����

	imshow("Color", img_result);
	imshow("B", img_channels[0]);
	imshow("G", img_channels[1]);
	imshow("R", img_channels[2]);

	waitKey(0);
	return 0;
}

//*/