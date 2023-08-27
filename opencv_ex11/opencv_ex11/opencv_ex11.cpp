/*
// ���� �� ��ȯ(�� ���� ������ ������ ���� ������ �������� ã�� ���� ����)

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    Mat img_edge, img_result;

    Mat img_src = imread("test.jpg", IMREAD_GRAYSCALE);

    Canny(img_src, img_edge, 50, 150);
    cvtColor(img_edge, img_result, COLOR_GRAY2BGR);

    vector<Vec2f> lines;                                    // ���� ���� ���� 
    HoughLines(img_edge, lines, 1, CV_PI / 180, 150);       // rho, theta ��ȯ 
                                // (�Է� �̹���, ��� �迭, rho, theta, threshold)

    for (size_t i = 0; i < lines.size(); i++)
    {
        float rho = lines[i][0], theta = lines[i][1];       // rho �� theta ����
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);              // ���� ��ǥ��� ��ȯ
        double x0 = a * rho, y0 = b * rho;

        pt1.x = cvRound(x0 + 1000 * (-b));                  // ���� ���� ����
        pt1.y = cvRound(y0 + 1000 * (a));
        pt2.x = cvRound(x0 - 1000 * (-b));
        pt2.y = cvRound(y0 - 1000 * (a));

        line(img_result, pt1, pt2, Scalar(0, 0, 255), 3);   // ���� ���
    }

    imshow("Source", img_src);
    imshow("Standard Hough Line Transform", img_result);

    waitKey();
    return 0;
}

*/

///*
// Ȯ���� ���� �� ��ȯ

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    Mat img_edge, img_result;

    Mat src = imread("test.jpg", IMREAD_GRAYSCALE);

    Canny(src, img_edge, 50, 150);
    cvtColor(img_edge, img_result, COLOR_GRAY2BGR);

    vector<Vec4i> linesP;                                   // Ȯ���� ���� ���� ����
    HoughLinesP(img_edge, linesP, 1, CV_PI / 180, 50, 50, 5);   // ������ ���۰� ���� ��ȯ
                // (�Է� �̹���, ��� �迭, rho, theta, threshold, �ּ� �� ����, �� ���� �Ÿ�)

    for (size_t i = 0; i < linesP.size(); i++)
    {
        Vec4i l = linesP[i];                                // ���� ���
        line(img_result, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, LINE_AA);
    }

    imshow("Source", src);
    imshow("Probabilistic Line Transform", img_result);

    waitKey();
    return 0;
}

//*/

/*
// ���� �� ��ȯ(������ �׷����Ʈ�� �̿��� �� ����)

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    Mat img_gray;

    img_gray = imread("test1.jpg", IMREAD_GRAYSCALE);
    medianBlur(img_gray, img_gray, 5);
    Mat img_color;
    cvtColor(img_gray, img_color, COLOR_GRAY2BGR);

    vector<Vec3f> circles;                                  // ���� �� ���� 
    HoughCircles(img_gray, circles, HOUGH_GRADIENT, 1, 20, 50, 35, 0, 0);   // �� �߽� ��ǥ �� ������ ��ȯ
            // (�Է� �̹���, ��� �迭, ���� ���, �ػ�, �� ���� �ּ� �Ÿ�, threshold1, threshold2, �ּ� ������, �ִ� ������)

    for (size_t i = 0; i < circles.size(); i++)
    {
        Vec3i c = circles[i];                               // �� ���
        Point center(c[0], c[1]);
        int radius = c[2];

        circle(img_color, center, radius, Scalar(0, 255, 0), 2);
        circle(img_color, center, 2, Scalar(0, 0, 255), 3);
    }

    imshow("detected circles", img_color);
    waitKey(0);
    destroyAllWindows();

    return 0;
}

*/