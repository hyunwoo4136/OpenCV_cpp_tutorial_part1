/*
// �� ��� ��ü ����

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

        Mat img_hsv;                                                    // hsv ��ȯ
        cvtColor(img_frame, img_hsv, COLOR_BGR2HSV);

        Mat img_mask;                                                   // �Ķ��� ���� ����ũ �̹���
        Vec3b lower_blue = Vec3b(120 - 20, 70, 0);
        Vec3b upper_blue = Vec3b(120 + 20, 255, 255);
        inRange(img_hsv, lower_blue, upper_blue, img_mask);

        Mat kernel = getStructuringElement(MORPH_RECT, Size(11, 11));   // closing �������� ����
        morphologyEx(img_mask, img_mask, MORPH_CLOSE, kernel);

        Mat img_result;                                                 // ����ũ �̹����� �Ķ��� ����
        bitwise_and(img_frame, img_frame, img_result, img_mask);

        Mat labels, stats, centroids;                                   // �󺧸�
        int nlabels = connectedComponentsWithStats(img_mask, labels, stats, centroids);

        for (int i = 0; i < nlabels; i++)
        {
            if (i < 1)
                continue;

            int area = stats.at<int>(i, CC_STAT_AREA);                  // �� ���� ����
            int center_x = centroids.at<double>(i, 0);
            int center_y = centroids.at<double>(i, 1);
            int left = stats.at<int>(i, CC_STAT_LEFT);
            int top = stats.at<int>(i, CC_STAT_TOP);
            int width = stats.at<int>(i, CC_STAT_WIDTH);
            int height = stats.at<int>(i, CC_STAT_HEIGHT);

            if (area > 10000)                                           // �� ��ȣ ǥ��
            {
                rectangle(img_frame, Point(left, top), Point(left + width, top + height), Scalar(0, 0, 255), 3);

                circle(img_frame, Point(center_x, center_y), 5, (255, 0, 0), 3);

                putText(img_frame, std::to_string(i), Point(left + 20, top + 20), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 3);
            }
        }

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
// meanshift(: ��ǥ ����� ������ ��ǥ ����)

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

bool mouse_is_pressing = false;
int start_x, start_y, end_x, end_y;
int step = 0;

void swap(int* v1, int* v2) 
{
    int temp = *v1;
    *v1 = *v2;
    *v2 = temp;
}

void mouse_callback(int event, int x, int y, int flags, void* userdata) // ���콺�� �簢�� ���� ����
{
    if (event == EVENT_LBUTTONDOWN)
    {
        step = 1;

        mouse_is_pressing = true;
        start_x = x;
        start_y = y;
    }
    else if (event == EVENT_MOUSEMOVE) 
    {
        if (mouse_is_pressing) 
        {
            end_x = x;
            end_y = y;

            step = 2;
        }
    }
    else if (event == EVENT_LBUTTONUP)
    {
        mouse_is_pressing = false;

        end_x = x;
        end_y = y;

        step = 3;
    }
}


int main()
{
    Mat img_color, img_hsv, img_mask, img_ROI;
    Mat objectHistogram;
    Rect track_window;

    int channels[] = { 0 };
    int hsize[] = { 180 };
    float range1[] = { 0, 180 };
    const float* histRange[] = { range1 };

    VideoCapture cap(0);

    if (!cap.isOpened())
    {
        cerr << "video ���� - ī�޶� �Ǵ� ������ �� �� �����ϴ�.\n";
        return -1;
    }

    namedWindow("Color");                                               // ������ ����
    setMouseCallback("Color", mouse_callback);                          // ���콺 �ݹ� �Լ� ����

    while (1)
    {
        cap.read(img_color);

        if (img_color.empty()) 
        {
            cerr << "�� ������ ĸ�ĵǾ����ϴ�.\n";
            break;
        }

        switch (step)
        {
        case 1:                                                         // ���콺 ��Ŭ�� �� �� ����
            circle(img_color, Point(start_x, start_y), 10, Scalar(0, 255, 0), -1);
            break;

        case 2:                                                         // ���콺 ��Ŭ�� �� �巡�� �� �簢�� ����
            rectangle(img_color, Point(start_x, start_y), Point(end_x, end_y), Scalar(0, 255, 0), 3);
            break;

        case 3:
            if (start_x > end_x) 
            {
                swap(&start_x, &end_x);
                swap(&start_y, &end_y);
            }
            track_window = Rect(start_x, start_y, end_x - start_x, end_y - start_y);

            cvtColor(img_color, img_hsv, COLOR_BGR2HSV);                // hsv ��ȯ
            img_ROI = Mat(img_hsv, track_window);                       // ROI ����

            imshow("ROI", img_ROI);

            calcHist(&img_ROI, 1, channels, Mat(), objectHistogram, 1, hsize, histRange);   // ROI ������׷� ���

            normalize(objectHistogram, objectHistogram, 0, 255, NORM_MINMAX);   // ����ȭ

            step++;

            break;

        case 4:
            Mat bp;
            cvtColor(img_color, img_hsv, COLOR_BGR2HSV);                // hsv ��ȯ

            calcBackProject(&img_hsv, 1, channels, objectHistogram, bp, histRange); // ROI ������׷� ������

            meanShift(bp, track_window, TermCriteria(TermCriteria::EPS | TermCriteria::COUNT, 10, 1));  // meanshift

            rectangle(img_color, track_window, Scalar(0, 0, 255), 2);
            break;
        }

        imshow("Color", img_color);

        if (waitKey(25) >= 0)
            break;
    }

    return 0;
}

*/

///*
// camshift(: meanshift���� Ʈ�� ������ ũ�⸦ ��� �°� ����)

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

bool mouse_is_pressing = false;
int start_x, start_y, end_x, end_y;
int step = 0;

void swap(int* v1, int* v2) 
{
    int temp = *v1;
    *v1 = *v2;
    *v2 = temp;
}

void mouse_callback(int event, int x, int y, int flags, void* userdata)
{
    if (event == EVENT_LBUTTONDOWN) 
    {
        step = 1;

        mouse_is_pressing = true;
        start_x = x;
        start_y = y;
    }
    else if (event == EVENT_MOUSEMOVE) 
    {
        if (mouse_is_pressing) 
        {
            end_x = x;
            end_y = y;

            step = 2;
        }
    }
    else if (event == EVENT_LBUTTONUP) 
    {
        mouse_is_pressing = false;

        end_x = x;
        end_y = y;

        step = 3;
    }
}

int main()
{
    Mat img_color, img_hsv, img_mask, img_ROI, mask_ROI;
    Mat objectHistogram;
    Rect track_window;

    int channels[] = { 0 };
    int hsize[] = { 180 };
    float range1[] = { 0, 180 };
    const float* histRange[] = { range1 };

    VideoCapture cap(0);

    if (!cap.isOpened()) 
    {
        cerr << "video ���� - ī�޶� �Ǵ� ������ �� �� �����ϴ�.\n";
        return -1;
    }

    namedWindow("Color");
    setMouseCallback("Color", mouse_callback);

    while (1)
    {
        cap.read(img_color);

        if (img_color.empty()) 
        {
            cerr << "�� ������ ĸ�ĵǾ����ϴ�.\n";
            break;
        }

        switch (step)
        {
        case 1:
            circle(img_color, Point(start_x, start_y), 10, Scalar(0, 255, 0), -1);
            break;

        case 2:
            rectangle(img_color, Point(start_x, start_y), Point(end_x, end_y), Scalar(0, 255, 0), 3);
            break;

        case 3:

            if (start_x > end_x) 
            {
                swap(&start_x, &end_x);
                swap(&start_y, &end_y);
            }

            track_window = Rect(start_x, start_y, end_x - start_x, end_y - start_y);

            cvtColor(img_color, img_hsv, COLOR_BGR2HSV);

            img_ROI = Mat(img_hsv, track_window);

            imshow("ROI", img_ROI);

            calcHist(&img_ROI, 1, channels, Mat(), objectHistogram, 1, hsize, histRange);

            normalize(objectHistogram, objectHistogram, 0, 255, NORM_MINMAX);

            step++;

            break;

        case 4:

            Mat bp;
            cvtColor(img_color, img_hsv, COLOR_BGR2HSV);

            calcBackProject(&img_hsv, 1, channels, objectHistogram, bp, histRange);

            RotatedRect rotatedRect = CamShift(bp, track_window, TermCriteria(TermCriteria::EPS | TermCriteria::COUNT, 10, 1)); // camshift

            ellipse(img_color, rotatedRect, Scalar(0, 0, 255), 2);      // Ʈ�� ������ ������ Ÿ�� ���

            Point2f vertices[4];                                        // camshift Ʈ�� ������ ���
            rotatedRect.points(vertices);
            for (int i = 0; i < 4; i++)
                line(img_color, vertices[i], vertices[(i + 1) % 4], Scalar(0, 255, 0), 2);

            break;
        }

        imshow("Color", img_color);

        if (waitKey(25) >= 0)
            break;
    }

    return 0;
}

//*/