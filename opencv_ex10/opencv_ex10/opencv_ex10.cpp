/*
// erosion �������� (�� ������Ʈ �ܰ� �ȼ��� 0����)

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
    Mat img_gray;
    img_gray = imread("test.png", IMREAD_GRAYSCALE);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3)); // Ŀ�� ����
    Mat img_result;
    erode(img_gray, img_result, kernel, Point(-1, -1), 1);      // erosion ����
                                //(�Է� �̹���, ��� �̹���, Ŀ��, ��Ŀ ��ǥ, �ݺ� ��)
    imshow("Input", img_gray);
    imshow("Result", img_result);
    waitKey(0);

    return 0;
}

*/

/*
// dilation �������� (�� ������Ʈ �ܰ� �ȼ��� 1��)

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
    Mat img_gray;
    img_gray = imread("test.png", IMREAD_GRAYSCALE);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    Mat img_result;
    dilate(img_gray, img_result, kernel, Point(-1, -1), 1);     // dilation ����

    imshow("Input", img_gray);
    imshow("Result", img_result);
    waitKey(0);

    return 0;
}

*/

/*
// opening �������� (erosion �� dilation, �̹����� �� ������ ����)

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
    Mat img_gray;
    img_gray = imread("test2.png", IMREAD_GRAYSCALE);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    Mat img_result;
    morphologyEx(img_gray, img_result, MORPH_OPEN, kernel);     // opening ����

    imshow("Input", img_gray);
    imshow("Result", img_result);
    waitKey(0);

    return 0;
}

*/

///*
// closing �������� (dilation �� erosion, �̹����� ���� ������ ����)

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
    Mat img_gray;
    img_gray = imread("test3.png", IMREAD_GRAYSCALE);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(11, 11));
    Mat img_result;
    morphologyEx(img_gray, img_result, MORPH_CLOSE, kernel);    // closing ����

    imshow("Input", img_gray);
    imshow("Result", img_result);
    waitKey(0);

    return 0;
}

//*/