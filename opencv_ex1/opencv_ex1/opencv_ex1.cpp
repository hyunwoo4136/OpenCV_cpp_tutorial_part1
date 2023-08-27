///*
// 이미지 다루기

#include <opencv2/opencv.hpp>					// opencv 헤더 파일
#include <iostream>	

using namespace cv;
using namespace std;

int main()
{
	Mat img_color;								// Mat 객체 선언

	img_color = imread("cat on laptop.jpg", IMREAD_COLOR);	// 이미지 저장

	if (img_color.empty())						// 이미지를 불러올 수 없을 때
	{
		cout << "이미지 파일을 읽을 수 없습니다." << endl;
		return -1;
	}

	namedWindow("Color");						// 출력창 생성

	imshow("Color", img_color);					// 창에 이미지 출력

	waitKey(0);									// 키보드 입력 대기

	Mat img_gray;								// Mat 객체 선언

	cvtColor(img_color, img_gray, COLOR_BGR2GRAY);	// 이미지 변환

	imshow("Grayscale", img_gray);				// 창에 이미지 출력

	waitKey(0);									// 키보드 입력 대기

	destroyAllWindows();						// 출력창 종료
}

//*/

/*
// 동영상 다루기 1

#include <opencv2/opencv.hpp>					// opencv 헤더 파일
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat img_frame;								// Mat 객체 선언

	VideoCapture cap(0);						// VideoCapture 객체 선언

	if (!cap.isOpened())						// 카메라 연결 체크
	{
		cout << "카메라를 열 수 없습니다." << endl;
		return -1;
	}

	bool ret = cap.read(img_frame);				// 카메라에서 이미지 캡쳐

	if (!ret)									// 캡쳐 실패 시
	{
		cout << "캡쳐 실패" << endl;
		return -1;
	}

	int codec = VideoWriter::fourcc('M', 'J', 'P', 'G');	// 동영상 파일 코덱 설정

	double fps=30.0;							// 프레임 레이트

	VideoWriter writer("output.avi", codec, fps, img_frame.size());	// VideoCapture 객체 선언

	if (!writer.isOpened())						// 객체 초기화 실패 시
	{
		cout << "동영상 파일을 준비할 수 없습니다." << endl;
		return -1;
	}

	while (1)
	{
		bool ret = cap.read(img_frame);			// 카메라에서 이미지 캡쳐

		if (!ret)								// 캡쳐 실패 시
		{
			cout << "탭쳐 실패" << endl;
			break;
		}

		writer.write(img_frame);				// 캡쳐한 이미지를 동영상으로 저장

		imshow("Color", img_frame);				// 창에 이미지 출력

		int key = waitKey(1);					// 1ms 동안 키보드 입력 대기

		if (key == 27)							// esc 키 입력 대기
			break;
	}

	cap.release();								// 카메라 연결 종료
	writer.release();							// 저장 완료
	return 0;
}

*/

/*
// 동영상 다루기 2

#include <opencv2/opencv.hpp>					// opencv 헤더 파일
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat img_frame;								// Mat 객체 선언

	VideoCapture cap("output.avi");				// VideoCapture 객체 선언

	if (!cap.isOpened())						// 카메라 연결 체크
	{
		cout << "카메라를 열 수 없습니다." << endl;
		return -1;
	}

	while (1)
	{
		bool ret = cap.read(img_frame);			// 카메라에서 이미지 캡쳐

		if (!ret)								// 캡쳐 실패 시
		{
			cout << "동영상 파일 읽기 완료" << endl;
			break;
		}

		imshow("Color", img_frame);				// 창에 이미지 출력

		int key = waitKey(25);					// 25ms 동안 키보드 입력 대기

		if (key == 27)							// esc 키 입력 대기
			break;
	}

	cap.release();								// 카메라 연결 종료
	return 0;
}

*/