/*
// 트랙바

#include <opencv2/opencv.hpp>

using namespace cv;

static void on_trackbar( int, void* )                       // 트랙바 조정 시 콜백 함수
{
}

int main()
{
    namedWindow("Canny");                                   // 트랙바 윈도우 생성

    createTrackbar("low threshold", "Canny", 0, 1000, on_trackbar); // 트랙바 생성
    createTrackbar("high threshold", "Canny", 0, 1000, on_trackbar);

    setTrackbarPos("low threshold", "Canny", 50);           // 트랙바 초기값 설정
    setTrackbarPos("high threshold", "Canny", 150);

    Mat img_gray;
    img_gray = imread("orange.png", IMREAD_GRAYSCALE);

    while(1)
    {
        int low = getTrackbarPos("low threshold", "Canny"); // 트랙바 위치 read
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
// 키보드 이벤트

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
        cout << "카메라를 열 수 없습니다." << endl;
        return -1;
    }

    int step = 1;

    while (1)
    {
        bool ret = cap.read(img_frame);

        if (!ret)
        {
            cout << "캡쳐 실패" << endl;
            break;
        }

        if (step > 1) 
        {
            cvtColor(img_frame, img_frame, COLOR_BGR2GRAY); // grayscale 변환

            if (step > 2)
                Canny(img_frame, img_frame, 30, 90);        // canny 에지 검출
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
// 키보드 이벤트

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

bool mouse_is_pressing = false;                             // 마우스 좌클릭 flag
bool drawing_mode = true;                                   // 그리기 모드 flag
int start_x = -1;                                           // 마우스 위치 저장 변수 
int start_y = -1;

Scalar color(255, 255, 255);                                // 도형 색 변수
Mat img;
RNG rng(543210);

void mouse_callback(int event, int x, int y, int flags, void* userdata) // 마우스 이벤트 콜백 함수 
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
    else if (event == EVENT_LBUTTONDOWN)                    // 좌클릭 시 도형 시작 좌표 저장
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
    else if (event == EVENT_RBUTTONDOWN)                    // 우클릭으로 도형 변환
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

    setMouseCallback("image", mouse_callback, 0);           // 마우스 콜백 함수 지정

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
// 윈도우 활용(이미지 타입이 같고 너비 또는 높이가 같아야 결합 가능)

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
        cout << "이미지 파일을 읽을 수 없습니다." << endl;
        return -1;
    }

    Mat img_gray;
    cvtColor(img_color, img_gray, COLOR_BGR2GRAY);

    Mat img_canny;
    Canny(img_gray, img_canny, 90, 180);

    vector<Mat> matrices = { img_gray, img_canny };         // 결합할 이미지 지정

    Mat img_result;

    hconcat(matrices, img_result);                          // 결합한 이미지 생성

    imshow("Result", img_result);

    waitKey(0);
    destroyAllWindows();
}

//*/