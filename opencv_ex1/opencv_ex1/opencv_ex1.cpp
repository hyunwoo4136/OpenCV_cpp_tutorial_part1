///*
// �̹��� �ٷ��

#include <opencv2/opencv.hpp>					// opencv ��� ����
#include <iostream>	

using namespace cv;
using namespace std;

int main()
{
	Mat img_color;								// Mat ��ü ����

	img_color = imread("cat on laptop.jpg", IMREAD_COLOR);	// �̹��� ����

	if (img_color.empty())						// �̹����� �ҷ��� �� ���� ��
	{
		cout << "�̹��� ������ ���� �� �����ϴ�." << endl;
		return -1;
	}

	namedWindow("Color");						// ���â ����

	imshow("Color", img_color);					// â�� �̹��� ���

	waitKey(0);									// Ű���� �Է� ���

	Mat img_gray;								// Mat ��ü ����

	cvtColor(img_color, img_gray, COLOR_BGR2GRAY);	// �̹��� ��ȯ

	imshow("Grayscale", img_gray);				// â�� �̹��� ���

	waitKey(0);									// Ű���� �Է� ���

	destroyAllWindows();						// ���â ����
}

//*/

/*
// ������ �ٷ�� 1

#include <opencv2/opencv.hpp>					// opencv ��� ����
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat img_frame;								// Mat ��ü ����

	VideoCapture cap(0);						// VideoCapture ��ü ����

	if (!cap.isOpened())						// ī�޶� ���� üũ
	{
		cout << "ī�޶� �� �� �����ϴ�." << endl;
		return -1;
	}

	bool ret = cap.read(img_frame);				// ī�޶󿡼� �̹��� ĸ��

	if (!ret)									// ĸ�� ���� ��
	{
		cout << "ĸ�� ����" << endl;
		return -1;
	}

	int codec = VideoWriter::fourcc('M', 'J', 'P', 'G');	// ������ ���� �ڵ� ����

	double fps=30.0;							// ������ ����Ʈ

	VideoWriter writer("output.avi", codec, fps, img_frame.size());	// VideoCapture ��ü ����

	if (!writer.isOpened())						// ��ü �ʱ�ȭ ���� ��
	{
		cout << "������ ������ �غ��� �� �����ϴ�." << endl;
		return -1;
	}

	while (1)
	{
		bool ret = cap.read(img_frame);			// ī�޶󿡼� �̹��� ĸ��

		if (!ret)								// ĸ�� ���� ��
		{
			cout << "���� ����" << endl;
			break;
		}

		writer.write(img_frame);				// ĸ���� �̹����� ���������� ����

		imshow("Color", img_frame);				// â�� �̹��� ���

		int key = waitKey(1);					// 1ms ���� Ű���� �Է� ���

		if (key == 27)							// esc Ű �Է� ���
			break;
	}

	cap.release();								// ī�޶� ���� ����
	writer.release();							// ���� �Ϸ�
	return 0;
}

*/

/*
// ������ �ٷ�� 2

#include <opencv2/opencv.hpp>					// opencv ��� ����
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat img_frame;								// Mat ��ü ����

	VideoCapture cap("output.avi");				// VideoCapture ��ü ����

	if (!cap.isOpened())						// ī�޶� ���� üũ
	{
		cout << "ī�޶� �� �� �����ϴ�." << endl;
		return -1;
	}

	while (1)
	{
		bool ret = cap.read(img_frame);			// ī�޶󿡼� �̹��� ĸ��

		if (!ret)								// ĸ�� ���� ��
		{
			cout << "������ ���� �б� �Ϸ�" << endl;
			break;
		}

		imshow("Color", img_frame);				// â�� �̹��� ���

		int key = waitKey(25);					// 25ms ���� Ű���� �Է� ���

		if (key == 27)							// esc Ű �Է� ���
			break;
	}

	cap.release();								// ī�޶� ���� ����
	return 0;
}

*/