/*
// 전역 임계값 사용 이진화

#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;
using namespace std;


static void on_trackbar( int, void* )							// 트랙바 콜백 함수
{
}

int main()
{
	Mat img_color;
	img_color = imread("red ball.png", IMREAD_COLOR);
	if (img_color.empty())
	{
		cout << "이미지 파일을 읽을 수 없습니다." << endl;
		return -1;
	}

	Mat img_gray;
	cvtColor(img_color, img_gray, COLOR_BGR2GRAY);
	imshow("Grayscale", img_gray);

	namedWindow("Binary");
	createTrackbar("threshold", "Binary", 0, 255, on_trackbar);	// 트랙바 생성 및 초기화
	setTrackbarPos("threshold", "Binary", 127);

	while(1)
	{
		int thresh = getTrackbarPos("threshold", "Binary");		// 트랙바 위치 read

		Mat img_binary;
		threshold(img_gray, img_binary, thresh, 255, THRESH_BINARY_INV);	// 이미지 이진화

		imshow("Binary", img_binary);

		if (waitKey(1) == 27)
			break;
	}
}

*/

///*
// 적응형 이진화

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
		cout << "이미지 파일을 읽을 수 없습니다." << endl;
		return -1;
	}

	Mat img_gray;
	cvtColor(img_color, img_gray, COLOR_BGR2GRAY);

	Mat img_binary;
	adaptiveThreshold(img_gray, img_binary, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 5, 4);	// 적응형 이진화
											// (img, img, 최대 임계값, 계산 방법, 타입, 영역 사이즈, 평균에서 차감할 값)
	imshow("Grayscale", img_gray);
	imshow("Binary", img_binary);
	waitKey(0);
}

//*/