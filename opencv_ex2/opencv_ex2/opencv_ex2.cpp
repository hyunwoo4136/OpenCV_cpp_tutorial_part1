/*
// Mat 객체: 이미지 데이터를 공유해 하나의 객체를 처리하면 나머지 객체에도 영향이 미침(Python 넘파이는 X)

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	Mat img_color;

	img_color = imread("cat on laptop.jpg", IMREAD_GRAYSCALE);

	Mat img_sub1(img_color, Rect(400, 120, 350, 200));			// 직사각형 영역 지정(x, y, x 범위, y 범위) 

	Mat img_sub2 = img_color(Range(100, 150), Range::all());	// 영역 지정(y 시작, y 끝, x 시작, x 끝)

	threshold(img_sub1, img_sub1, 127, 255, THRESH_BINARY);		// 이미지 이진화

	imshow("img_color", img_color);
	imshow("img_sub1", img_sub1);
	imshow("img_sub2", img_sub2);

	waitKey(0);
}

*/

/*
// 이미지 복사

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	Mat img_color;

	img_color = imread("cat on laptop.jpg", IMREAD_GRAYSCALE);

	Mat img_copyed1 = img_color.clone();						// 이미지 객체 복사 1

	Mat img_copyed2;
	img_color.copyTo(img_copyed2);								// 이미지 객체 복사 2

	threshold(img_color, img_color, 127, 255, THRESH_BINARY);	// 이미지 이진화

	imshow("img_color", img_color);
	imshow("img_sub1", img_copyed1);
	imshow("img_sub2", img_copyed2);

	waitKey(0);
}

*/

/*
// 픽셀 접근 

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat img_color = imread("apple.jpg", IMREAD_COLOR);

	int height = img_color.rows;								// 이미지 행, 열 크기
	int width = img_color.cols;

	Mat img_gray(height, width, CV_8UC1);

	for (int y = 0; y < height; y++)							// grayscale로 변환
	{
		uchar* pointer_input = img_color.ptr<uchar>(y);			// y 좌표를 이용해 포인터 계산
		uchar* pointer_output = img_gray.ptr<uchar>(y);

		for (int x = 0; x < width; x++)
		{
				uchar b = pointer_input[x * 3 + 0];				// 컬러 이미지의 bgr 채널 read
				uchar g = pointer_input[x * 3 + 1];				// b, g, r 3 채널
				uchar r = pointer_input[x * 3 + 2];

				pointer_output[x] = r * 0.2126 + g * 0.7152 + b * 0.0722;
		}
	}

	Mat img_result;

	cvtColor(img_gray, img_result, COLOR_GRAY2BGR);

	for (int y = 100; y < 150; y++)								// 일정 영역 색 변경
	{
		uchar* pointer_input = img_result.ptr<uchar>(y);

		for (int x = 150; x < 200; x++) 
		{
			pointer_input[x * 3 + 0] = 0;
			pointer_input[x * 3 + 1] = 255;						// 초록색으로 변경
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
// 이미지 채널 분리 및 합치기

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat img_color;

	img_color = imread("color.png", IMREAD_COLOR);

	Mat img_channels[3];										// 컬러 이미지 채널별 분리
	split(img_color, img_channels);

	vector<Mat> channels;										// b, r 순서를 바꿔 이미지 채널 생성
	channels.push_back(img_channels[2]);
	channels.push_back(img_channels[1]);
	channels.push_back(img_channels[0]);

	Mat img_result;
	merge(channels, img_result);								// 이미지 채널 조합

	imshow("Color", img_result);
	imshow("B", img_channels[0]);
	imshow("G", img_channels[1]);
	imshow("R", img_channels[2]);

	waitKey(0);
	return 0;
}

//*/