/*
// 색 기반 물체 추적

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

    while (1)
    {
        bool ret = cap.read(img_frame);
        if (!ret)
        {
            cout << "캡쳐 실패" << endl;
            break;
        }

        Mat img_hsv;                                                    // hsv 변환
        cvtColor(img_frame, img_hsv, COLOR_BGR2HSV);

        Mat img_mask;                                                   // 파란색 검출 마스크 이미지
        Vec3b lower_blue = Vec3b(120 - 20, 70, 0);
        Vec3b upper_blue = Vec3b(120 + 20, 255, 255);
        inRange(img_hsv, lower_blue, upper_blue, img_mask);

        Mat kernel = getStructuringElement(MORPH_RECT, Size(11, 11));   // closing 모폴로지 적용
        morphologyEx(img_mask, img_mask, MORPH_CLOSE, kernel);

        Mat img_result;                                                 // 마스크 이미지로 파란색 검출
        bitwise_and(img_frame, img_frame, img_result, img_mask);

        Mat labels, stats, centroids;                                   // 라벨링
        int nlabels = connectedComponentsWithStats(img_mask, labels, stats, centroids);

        for (int i = 0; i < nlabels; i++)
        {
            if (i < 1)
                continue;

            int area = stats.at<int>(i, CC_STAT_AREA);                  // 라벨 정보 저장
            int center_x = centroids.at<double>(i, 0);
            int center_y = centroids.at<double>(i, 1);
            int left = stats.at<int>(i, CC_STAT_LEFT);
            int top = stats.at<int>(i, CC_STAT_TOP);
            int width = stats.at<int>(i, CC_STAT_WIDTH);
            int height = stats.at<int>(i, CC_STAT_HEIGHT);

            if (area > 10000)                                           // 라벨 번호 표시
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
// meanshift(: 목표 대상이 밀집한 좌표 검출)

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

void mouse_callback(int event, int x, int y, int flags, void* userdata) // 마우스로 사각형 영역 지정
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
        cerr << "video 에러 - 카메라 또는 영상을 열 수 없습니다.\n";
        return -1;
    }

    namedWindow("Color");                                               // 윈도우 생성
    setMouseCallback("Color", mouse_callback);                          // 마우스 콜백 함수 지정

    while (1)
    {
        cap.read(img_color);

        if (img_color.empty()) 
        {
            cerr << "빈 영상이 캡쳐되었습니다.\n";
            break;
        }

        switch (step)
        {
        case 1:                                                         // 마우스 좌클릭 시 원 생성
            circle(img_color, Point(start_x, start_y), 10, Scalar(0, 255, 0), -1);
            break;

        case 2:                                                         // 마우스 좌클릭 중 드래그 시 사각형 생성
            rectangle(img_color, Point(start_x, start_y), Point(end_x, end_y), Scalar(0, 255, 0), 3);
            break;

        case 3:
            if (start_x > end_x) 
            {
                swap(&start_x, &end_x);
                swap(&start_y, &end_y);
            }
            track_window = Rect(start_x, start_y, end_x - start_x, end_y - start_y);

            cvtColor(img_color, img_hsv, COLOR_BGR2HSV);                // hsv 변환
            img_ROI = Mat(img_hsv, track_window);                       // ROI 지정

            imshow("ROI", img_ROI);

            calcHist(&img_ROI, 1, channels, Mat(), objectHistogram, 1, hsize, histRange);   // ROI 히스토그램 계산

            normalize(objectHistogram, objectHistogram, 0, 255, NORM_MINMAX);   // 정규화

            step++;

            break;

        case 4:
            Mat bp;
            cvtColor(img_color, img_hsv, COLOR_BGR2HSV);                // hsv 변환

            calcBackProject(&img_hsv, 1, channels, objectHistogram, bp, histRange); // ROI 히스토그램 역투영

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
// camshift(: meanshift에서 트랙 윈도우 크기를 대상에 맞게 조절)

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
        cerr << "video 에러 - 카메라 또는 영상을 열 수 없습니다.\n";
        return -1;
    }

    namedWindow("Color");
    setMouseCallback("Color", mouse_callback);

    while (1)
    {
        cap.read(img_color);

        if (img_color.empty()) 
        {
            cerr << "빈 영상이 캡쳐되었습니다.\n";
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

            ellipse(img_color, rotatedRect, Scalar(0, 0, 255), 2);      // 트랙 윈도우 주위에 타원 출력

            Point2f vertices[4];                                        // camshift 트랙 윈도우 출력
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