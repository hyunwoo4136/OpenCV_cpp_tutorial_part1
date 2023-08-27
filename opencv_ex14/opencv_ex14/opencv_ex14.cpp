/*
// HSV �������� �̿��� �� ����

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    Mat img_frame;

    VideoCapture cap(0);
    if (!cap.isOpened())
    {
        cout << "ī�޶� �� �� �����ϴ�." << endl;
        return -1;
    }

    while (1)
    {
        bool ret = cap.read(img_frame);
        if (!ret)
        {
            cout << "ĸ�� ����" << endl;
            break;
        }

        Mat img_hsv;                                                    // HSV�� ��ȯ
        cvtColor(img_frame, img_hsv, COLOR_BGR2HSV);

        Mat img_mask;                                                   // ����ũ �̹��� ����
        Vec3b lower_blue = Vec3b(120 - 20, 70, 0);                      // (hue, saturation, value)
        Vec3b upper_blue = Vec3b(120 + 20, 255, 255);
        inRange(img_hsv, lower_blue, upper_blue, img_mask);             // �Ӱ谪 ������ �ȼ������� ��� �̹����� ����
                                                                        // (�Է� �̹���, �ּ� �Ӱ谪, �ִ� �Ӱ谪, ��� �̹���)

        Mat img_result;                                                 // ����� ������ ��� ����
        bitwise_and(img_frame, img_frame, img_result, img_mask);

        imshow("Color", img_frame);
        imshow("Result", img_result);

        int key = waitKey(1);
        if (key == 27)
            break;
    }

    cap.release();
    return 0;
}

*/

/*
// �󺧸�

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    Mat img_color = imread("test.jpg", IMREAD_COLOR);
    Mat img_gray;
    cvtColor(img_color, img_gray, COLOR_BGR2GRAY);
    imshow("result", img_gray);
    waitKey(0);

    Mat img_edge;                                                       // ���� ����
    Canny(img_gray, img_edge, 50, 150);
    imshow("result", img_edge);
    waitKey(0);

    bitwise_not(img_edge, img_edge);                                    // ����� ������� ��ȯ
    imshow("result", img_edge);
    waitKey(0);

    vector<vector<Point>> contours;                                     // ������ ����
    findContours(img_edge.clone(), contours, RETR_LIST, CHAIN_APPROX_SIMPLE);
    drawContours(img_edge, contours, -1, Scalar(0, 0, 0), 1);
    imshow("result", img_edge);
    waitKey(0);

    Mat labels, stats, centroids;                                       // �󺧸�
    int nlabels = connectedComponentsWithStats(img_edge, labels, stats, centroids); // �� �� ��ȯ
                                                    // (�Է� �̹���, ��� �̹���, ��� ��ü ����, ��� ��ü �߽�)
    for (int i = 0; i < nlabels; i++)
    {
        if (i < 2)                                                      // ��� ����
            continue;

        int area = stats.at<int>(i, CC_STAT_AREA);                      // ��� ���� ����
        int center_x = centroids.at<double>(i, 0);                      // ��� �߽� ��ǥ
        int center_y = centroids.at<double>(i, 1);
        int left = stats.at<int>(i, CC_STAT_LEFT);                      // ��� ��ġ
        int top = stats.at<int>(i, CC_STAT_TOP);
        int width = stats.at<int>(i, CC_STAT_WIDTH);
        int height = stats.at<int>(i, CC_STAT_HEIGHT);

        if (area > 50) 
        {
            rectangle(img_color, Point(left, top), Point(left + width, top + height), Scalar(0, 0, 255), 1);    // ��� �ܰ��� �簢�� �׸���

            circle(img_color, Point(center_x, center_y), 5, (255, 0, 0), 1);    // ��� �߽ɿ� �� �׸���

            putText(img_color, std::to_string(i), Point(left + 20, top + 20), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 3);   // �� ��ȣ ǥ��
        }
    }

    imshow("result", img_color);
    waitKey(0);
}

*/

///*
// ��� ����

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    Mat img_frame;

    VideoCapture cap(0);

    Ptr<BackgroundSubtractorMOG2> foregroundBackground = createBackgroundSubtractorMOG2(500, 100, false);   // ��� ���� ��ü ����
                                                                        // (�����丮 ����, �л� �Ӱ� ��, �׸��� ǥ��)
    while (1)
    {
        bool ret = cap.read(img_frame);
        if (!ret)
        {
            cout << "ĸ�� ����" << endl;
            break;
        }

        GaussianBlur(img_frame, img_frame, Size(5, 5), 0);              // ����þ� �� ó��

        Mat img_mask;                                                   // ��� ���̴� ����ũ �̹��� ����
        foregroundBackground->apply(img_frame, img_mask, 0);

        Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));  // closing �������� ����
        morphologyEx(img_mask, img_mask, MORPH_CLOSE, kernel); 

        imshow("mask", img_mask);
        imshow("Color", img_frame);

        int key = waitKey(30);
        if (key == 27)
            break;
    }

    cap.release();
    return 0;
}

//*/