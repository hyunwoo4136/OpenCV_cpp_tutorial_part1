/*
// Ʈ����

#include <opencv2/opencv.hpp>

using namespace cv;

static void on_trackbar( int, void* )                       // Ʈ���� ���� �� �ݹ� �Լ�
{
}

int main()
{
    namedWindow("Canny");                                   // Ʈ���� ������ ����

    createTrackbar("low threshold", "Canny", 0, 1000, on_trackbar); // Ʈ���� ����
    createTrackbar("high threshold", "Canny", 0, 1000, on_trackbar);

    setTrackbarPos("low threshold", "Canny", 50);           // Ʈ���� �ʱⰪ ����
    setTrackbarPos("high threshold", "Canny", 150);

    Mat img_gray;
    img_gray = imread("orange.png", IMREAD_GRAYSCALE);

    while(1)
    {
        int low = getTrackbarPos("low threshold", "Canny"); // Ʈ���� ��ġ read
        int high = getTrackbarPos("high threshold", "Canny");

        Mat img_canny;
        Canny(img_gray, img_canny, low, high);

        imshow("Canny", img_canny);

        if (waitKey(1) == 27)
            break;
    }

    destroyAllWindows();
    return 0;
}

*/

/*
// Ű���� �̺�Ʈ

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

    int step = 1;

    while (1)
    {
        bool ret = cap.read(img_frame);

        if (!ret)
        {
            cout << "ĸ�� ����" << endl;
            break;
        }

        if (step > 1) 
        {
            cvtColor(img_frame, img_frame, COLOR_BGR2GRAY); // grayscale ��ȯ

            if (step > 2)
                Canny(img_frame, img_frame, 30, 90);        // canny ���� ����
        }

        imshow("Result", img_frame);

        int key = waitKey(1);

        if (key == 27)
            break;

        else if (key == 49)
            step = 1;
        else if (key == 50)
            step = 2;
        else if (key == 51)
            step = 3;
    }

    cap.release();
    return 0;
}

*/

/*
// Ű���� �̺�Ʈ

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

bool mouse_is_pressing = false;                             // ���콺 ��Ŭ�� flag
bool drawing_mode = true;                                   // �׸��� ��� flag
int start_x = -1;                                           // ���콺 ��ġ ���� ���� 
int start_y = -1;

Scalar color(255, 255, 255);                                // ���� �� ����
Mat img;
RNG rng(543210);

void mouse_callback(int event, int x, int y, int flags, void* userdata) // ���콺 �̺�Ʈ �ݹ� �Լ� 
{
    if (event == EVENT_MOUSEMOVE) 
    {
        if (mouse_is_pressing == true) 
        {
            if (drawing_mode == true)
                rectangle(img, Point(start_x, start_y), Point(x, y), color, -1);
            else
                circle(img, Point(start_x, start_y), max(abs(start_x - x), abs(start_y - y)), color, -1);
        }
    }
    else if (event == EVENT_LBUTTONDOWN)                    // ��Ŭ�� �� ���� ���� ��ǥ ����
    {
        color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));

        mouse_is_pressing = true;

        start_x = x;
        start_y = y;
    }
    else if (event == EVENT_LBUTTONUP) 
    {
        mouse_is_pressing = false;

        if (drawing_mode == true)
            rectangle(img, Point(start_x, start_y), Point(x, y), color, -1);
        else
            circle(img, Point(start_x, start_y), max(abs(start_x - x), abs(start_y - y)), color, -1);
    }
    else if (event == EVENT_RBUTTONDOWN)                    // ��Ŭ������ ���� ��ȯ
    {
        drawing_mode = !drawing_mode;
    }
}

int main()
{
    int width = 500;
    int height = 500;

    img = Mat(height, width, CV_8UC3, Scalar(0, 0, 0));

    namedWindow("image");

    setMouseCallback("image", mouse_callback, 0);           // ���콺 �ݹ� �Լ� ����

    while (1) 
    {
        imshow("image", img);

        int key = waitKey(1);
        if (key == 27)
            break;
    }

    destroyAllWindows();
}

*/

///*
// ������ Ȱ��(�̹��� Ÿ���� ���� �ʺ� �Ǵ� ���̰� ���ƾ� ���� ����)

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    Mat img_color;

    img_color = imread("ball.png", IMREAD_COLOR);

    if (img_color.empty())
    {
        cout << "�̹��� ������ ���� �� �����ϴ�." << endl;
        return -1;
    }

    Mat img_gray;
    cvtColor(img_color, img_gray, COLOR_BGR2GRAY);

    Mat img_canny;
    Canny(img_gray, img_canny, 90, 180);

    vector<Mat> matrices = { img_gray, img_canny };         // ������ �̹��� ����

    Mat img_result;

    hconcat(matrices, img_result);                          // ������ �̹��� ����

    imshow("Result", img_result);

    waitKey(0);
    destroyAllWindows();
}

//*/