/*
// ���ø� ��Ī(: ���ø� �̹����� ��ġ�ϴ� ���� Ž��)

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
    Mat img_rgb = imread("test.jpg");

    Mat img_gray;
    cvtColor(img_rgb, img_gray, COLOR_BGR2GRAY);

    Mat img_template = imread("template.jpg", IMREAD_GRAYSCALE);        // ���ø� �̹��� ����
    int w = img_template.cols;
    int h = img_template.rows;

    Mat result;                                                         // ���ø� ��ġ
    matchTemplate(img_gray, img_template, result, TM_CCOEFF_NORMED);    // (�Է� �̹���, ���ø� �̹���, ��� �̹���, ��ġ ���)

    double min_val, max_val;
    Point min_loc, max_loc;
    minMaxLoc(result, &min_val, &max_val, &min_loc, &max_loc);          // �ȼ� �ּ� �ִ밪 ����
                                                                        // (�Է� �̹���, �ּҰ�, �ִ밪, �ּҰ� ��ġ, �ִ밪 ��ġ)
    Point top_left = max_loc;
    Point bottom_right = Point(top_left.x + w, top_left.y + h);

    rectangle(img_rgb, top_left, bottom_right, (0, 0, 255), 2);         // ���ø� ��ġ ��ġ ���

    imshow("result", img_rgb);
    waitKey(0);

    return 0;
}

*/

///*
// �Ӱ谪 ��� ���ø� ��Ī

#include <opencv2/opencv.hpp>
#include <cmath>

using namespace cv;
using namespace std;

vector<Point> detectedObjects;

bool notInList(Point newObject)                                         // ���ο� ��ǥ�� ���� ����Ʈ�� ��ǥ�� 5.0 �Ÿ� �̳��� �ִ��� Ȯ��
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

    Mat img_template = imread("template.jpg", IMREAD_GRAYSCALE);        // ���ø� �̹��� ����
    int w = img_template.cols;
    int h = img_template.rows;

    Mat result;                                                         // ���ø� ��ġ
    matchTemplate(img_gray, img_template, result, TM_CCOEFF_NORMED);

    int count = 0;
    for (int x = 0; x < result.cols; x++)
        for (int y = 0; y < result.rows; y++)
        {
            if (result.at<float>(y, x) > 0.9 && notInList(Point(x, y))) // 0.9 �Ӱ谪���� ũ�� ���� ��ǥ�� ������ ���� ��ǥ Ž��
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