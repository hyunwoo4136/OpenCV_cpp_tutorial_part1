/*
// HSV 색공간을 이용한 색 검출

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

        Mat img_hsv;                                                    // HSV로 변환
        cvtColor(img_frame, img_hsv, COLOR_BGR2HSV);

        Mat img_mask;                                                   // 마스크 이미지 생성
        Vec3b lower_blue = Vec3b(120 - 20, 70, 0);                      // (hue, saturation, value)
        Vec3b upper_blue = Vec3b(120 + 20, 255, 255);
        inRange(img_hsv, lower_blue, upper_blue, img_mask);             // 임계값 사이의 픽셀값만을 출력 이미지에 저장
                                                                        // (입력 이미지, 최소 임계값, 최대 임계값, 출력 이미지)

        Mat img_result;                                                 // 대상을 제외한 배경 제거
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
// 라벨링

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

    Mat img_edge;                                                       // 에지 검출
    Canny(img_gray, img_edge, 50, 150);
    imshow("result", img_edge);
    waitKey(0);

    bitwise_not(img_edge, img_edge);                                    // 대상을 흰색으로 변환
    imshow("result", img_edge);
    waitKey(0);

    vector<vector<Point>> contours;                                     // 컨투어 보강
    findContours(img_edge.clone(), contours, RETR_LIST, CHAIN_APPROX_SIMPLE);
    drawContours(img_edge, contours, -1, Scalar(0, 0, 0), 1);
    imshow("result", img_edge);
    waitKey(0);

    Mat labels, stats, centroids;                                       // 라벨링
    int nlabels = connectedComponentsWithStats(img_edge, labels, stats, centroids); // 라벨 수 반환
                                                    // (입력 이미지, 출력 이미지, 출력 객체 정보, 출력 객체 중심)
    for (int i = 0; i < nlabels; i++)
    {
        if (i < 2)                                                      // 배경 제외
            continue;

        int area = stats.at<int>(i, CC_STAT_AREA);                      // 대상 영역 넓이
        int center_x = centroids.at<double>(i, 0);                      // 대상 중심 좌표
        int center_y = centroids.at<double>(i, 1);
        int left = stats.at<int>(i, CC_STAT_LEFT);                      // 대상 위치
        int top = stats.at<int>(i, CC_STAT_TOP);
        int width = stats.at<int>(i, CC_STAT_WIDTH);
        int height = stats.at<int>(i, CC_STAT_HEIGHT);

        if (area > 50) 
        {
            rectangle(img_color, Point(left, top), Point(left + width, top + height), Scalar(0, 0, 255), 1);    // 대상 외곽에 사각형 그리기

            circle(img_color, Point(center_x, center_y), 5, (255, 0, 0), 1);    // 대상 중심에 원 그리기

            putText(img_color, std::to_string(i), Point(left + 20, top + 20), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 3);   // 라벨 번호 표시
        }
    }

    imshow("result", img_color);
    waitKey(0);
}

*/

///*
// 배경 제거

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    Mat img_frame;

    VideoCapture cap(0);

    Ptr<BackgroundSubtractorMOG2> foregroundBackground = createBackgroundSubtractorMOG2(500, 100, false);   // 배경 제거 객체 생성
                                                                        // (히스토리 개수, 분산 임계 값, 그림자 표시)
    while (1)
    {
        bool ret = cap.read(img_frame);
        if (!ret)
        {
            cout << "캡쳐 실패" << endl;
            break;
        }

        GaussianBlur(img_frame, img_frame, Size(5, 5), 0);              // 가우시안 블러 처리

        Mat img_mask;                                                   // 대상만 보이는 마스크 이미지 생성
        foregroundBackground->apply(img_frame, img_mask, 0);

        Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));  // closing 모폴로지 적용
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