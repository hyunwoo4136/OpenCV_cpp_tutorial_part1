/*
// 실시간 ROI(Region of Interest) 구현

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

bool mouse_is_pressing = false;
int start_x, start_y, end_x, end_y;
int step = 0;
Mat img_color;

void swap(int* v1, int* v2) 
{
    int temp = *v1;
    *v1 = *v2;
    *v2 = temp;
}

void mouse_callback(int event, int x, int y, int flags, void* param)
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
    VideoCapture cap(0);
    if (!cap.isOpened()) 
    {
        cout << "에러 - 카메라를 열 수 없습니다.\n";
        return -1;
    }

    namedWindow("Color");
    setMouseCallback("Color", mouse_callback);

    while (1)
    {
        cap.read(img_color);
        if (img_color.empty()) 
        {
            cout << "캡쳐 실패 \n";
            break;
        }

        switch (step)
        {
        case 1:
            circle(img_color, Point(start_x, start_y), 10,
                Scalar(0, 255, 0), -1);
            break;

        case 2:
            rectangle(img_color, Point(start_x, start_y),
                Point(end_x, end_y), Scalar(0, 255, 0), 3);
            break;

        case 3:
            if (start_x > end_x) 
            {
                swap(&start_x, &end_x);
                swap(&start_y, &end_y);
            }

            Mat ROI(img_color, Rect(start_x, start_y, end_x - start_x, end_y - start_y));

            cvtColor(ROI, ROI, COLOR_BGR2GRAY);
            Canny(ROI, ROI, 150, 50);
            cvtColor(ROI, ROI, COLOR_GRAY2BGR);

            ROI.copyTo(img_color(Rect(start_x, start_y, end_x - start_x, end_y - start_y)));

            break;
        }

        imshow("Color", img_color);

        if (waitKey(25) > 0)
            break;
    }

    destroyAllWindows();
    return 0;
}

*/

///*
// ROI 평균 색 추출

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    VideoCapture capture(0);

    while (1)
    {
        Mat img_color;
        bool ret = capture.read(img_color);

        Mat img_result = img_color.clone();
        int width = img_color.cols;
        int height = img_color.rows;
        int center_x = img_color.cols / 2.0;
        int center_y = img_color.rows / 2.0;

        rectangle(img_result, Point(center_x - 100, center_y - 100), Point(center_x + 100, center_y + 100), Scalar(0, 0, 255), 3);

        Mat img_roi(img_color, Rect(center_x - 100, center_y - 100, 200, 200)); // ROI 평균 색 계산
        Scalar m = mean(img_roi);

        Mat img_mean(img_roi.rows, img_roi.cols, CV_8UC3, Scalar(m[0], m[1], m[2]));

        imshow("mean", img_mean);
        imshow("Color", img_result);
        imshow("roi", img_roi);

        int key = waitKey(1);
        if (key == 27)
            break;
    }

    capture.release();
    return 0;
}

//*/