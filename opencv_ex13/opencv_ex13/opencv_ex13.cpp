/*
// 템플릿 매칭(: 템플릿 이미지와 일치하는 영역 탐색)

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
    Mat img_rgb = imread("test.jpg");

    Mat img_gray;
    cvtColor(img_rgb, img_gray, COLOR_BGR2GRAY);

    Mat img_template = imread("template.jpg", IMREAD_GRAYSCALE);        // 템플릿 이미지 생성
    int w = img_template.cols;
    int h = img_template.rows;

    Mat result;                                                         // 템플릿 매치
    matchTemplate(img_gray, img_template, result, TM_CCOEFF_NORMED);    // (입력 이미지, 템플릿 이미지, 출력 이미지, 매치 방식)

    double min_val, max_val;
    Point min_loc, max_loc;
    minMaxLoc(result, &min_val, &max_val, &min_loc, &max_loc);          // 픽셀 최소 최대값 검출
                                                                        // (입력 이미지, 최소값, 최대값, 최소값 위치, 최대값 위치)
    Point top_left = max_loc;
    Point bottom_right = Point(top_left.x + w, top_left.y + h);

    rectangle(img_rgb, top_left, bottom_right, (0, 0, 255), 2);         // 템플릿 매치 위치 출력

    imshow("result", img_rgb);
    waitKey(0);

    return 0;
}

*/

///*
// 임계값 사용 템플릿 매칭

#include <opencv2/opencv.hpp>
#include <cmath>

using namespace cv;
using namespace std;

vector<Point> detectedObjects;

bool notInList(Point newObject)                                         // 새로운 좌표가 기존 리스트의 좌표와 5.0 거리 이내에 있는지 확인
{
    for (int i = 0; i < detectedObjects.size(); i++)
    {
        float a = detectedObjects[i].x - newObject.x;
        float b = detectedObjects[i].y - newObject.y;

        if (sqrt(a * a + b * b) < 5.0)
            return false;
    }

    return true;
}

int main()
{
    Mat img_rgb = imread("test.jpg");

    Mat img_gray;
    cvtColor(img_rgb, img_gray, COLOR_BGR2GRAY);

    Mat img_template = imread("template.jpg", IMREAD_GRAYSCALE);        // 템플릿 이미지 생성
    int w = img_template.cols;
    int h = img_template.rows;

    Mat result;                                                         // 템플릿 매치
    matchTemplate(img_gray, img_template, result, TM_CCOEFF_NORMED);

    int count = 0;
    for (int x = 0; x < result.cols; x++)
        for (int y = 0; y < result.rows; y++)
        {
            if (result.at<float>(y, x) > 0.9 && notInList(Point(x, y))) // 0.9 임계값보다 크고 기존 좌표와 가깝지 않은 좌표 탐색
            {
                detectedObjects.push_back(Point(x, y));
                rectangle(img_rgb, Point(x, y), Point(x + w, y + h), Scalar(0, 0, 255), 1);
                count++;
            }
        }

    cout << count << endl;
    imshow("result", img_rgb);
    waitKey(0);

    return 0;
}

//*/