/*
// ������׷�(: �ȼ� ���� �׷���, x: �ȼ���, y: �ȼ� ��)

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    Mat src = imread("apple.jpg", IMREAD_COLOR);

    vector<Mat> bgr_planes;                                         // �÷� �̹��� b, g, r ä�η� �и�
    split(src, bgr_planes);

    int histSize = 256;                                             // �ȼ��� ����
    float range[] = { 0, 256 };
    const float* histRange = { range };
    bool uniform = true, accumulate = false;

    Mat b_hist, g_hist, r_hist;                                     // ä�κ� ������׷� ���
    calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);
            // (�Է� �̹���, �̹��� ��, ä�� �ε���, ���� ����ũ, ��� �迭, �迭 ���� ��, �迭 ũ��, ����, ���� �÷���, ���� �÷���)

    int hist_w = 256 * 3, hist_h = 400;                             // ��� �̹��� ����
    Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

    normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());   // ������׷� ����ȭ
    normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
                                    // (�Է� �迭, ��� �迭, ��ȯ �ּҰ�, ��ȯ �ִ밪, ��ȯ ���)
    for (int i = 0; i < histSize; i++)      
    {                                                               // ������׷� ���
        line(histImage, Point(i, hist_h - cvRound(b_hist.at<float>(i))), Point(i, hist_h - 0), Scalar(255, 0, 0), 2);
        line(histImage, Point(i + 256, hist_h - cvRound(g_hist.at<float>(i))), Point(i + 256, hist_h - 0), Scalar(0, 255, 0), 2);
        line(histImage, Point(i + 256 * 2, hist_h - cvRound(r_hist.at<float>(i))), Point(i + 256 * 2, hist_h - 0), Scalar(0, 0, 255), 2);
    }

    imshow("Source image", src);
    imshow("Histogram", histImage);
    waitKey();
    return EXIT_SUCCESS;
}

*/

/*
// ��� ������׷�

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    Mat src = imread("cat on laptop.jpg", IMREAD_GRAYSCALE);

    int histSize = 256;                                             // �ȼ��� ����
    float range[] = { 0, 256 };
    const float* histRange = { range };
    bool uniform = true, accumulate = false;

    Mat gray_hist;                                                  // ������׷� ���
    calcHist(&src, 1, 0, Mat(), gray_hist, 1, &histSize, &histRange, uniform, accumulate);
                // (�Է� �̹���, �̹��� ��, ä�� �ε���, ���� ����ũ, ��� �迭, �迭 ���� ��, �迭 ũ��, ����, ���� �÷���, ���� �÷���)

    int hist_w = 256, hist_h = 400;                                 // ��� �̹��� ����
    Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));

    normalize(gray_hist, gray_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat()); // ������׷� ����ȭ

    for (int i = 0; i < histSize; i++)                              // ������׷� ���
    {
        line(histImage, Point(i, hist_h - cvRound(gray_hist.at<float>(i))), Point(i, hist_h - 0), Scalar(255, 255, 255), 2);
    }

    imshow("Source image", src);
    imshow("Histogram", histImage);
    waitKey();
    return EXIT_SUCCESS;
}

*/

/*
// ������׷� ��Ȱȭ(: ��Ʈ��Ʈ ���, ��Ʈ��Ʈ: ���� �κа� ��ο� �κ��� ����)

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Mat draw_histogram(Mat img)
{
    int hist_h = img.rows;                                          // ������׷� ��� �̹��� ����
    int hist_w = 256;
    Mat img_histogram1(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));

    Mat hist_item;                                                  // ������׷� �迭 ����

    int histSize = 256;                                             // �ȼ��� ����
    float range[] = { 0, 256 };
    const float* histRange = { range };
    bool uniform = true; bool accumulate = false;
                                                                    // ������׷� ��� �� ����ȭ
    calcHist(&img, 1, 0, Mat(), hist_item, 1, &histSize, &histRange, uniform, accumulate);
    normalize(hist_item, hist_item, 0, 255, NORM_MINMAX);

    for (int i = 1; i < histSize; i++)                              // ������׷� ���
        line(img_histogram1, Point(i, hist_h - cvRound(hist_item.at<float>(i))), Point(i, hist_h), Scalar(255, 255, 255));

    Mat img_histogram2(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));   // ���� ������׷� ��� �̹��� ����

    Mat c_hist(hist_item.size(), hist_item.type());                 // ���� ������׷� �迭 ����

    c_hist.at<float>(0) = hist_item.at<float>(0);                   // ���� ������׷� �迭�� ������׷� �迭 ����
    for (int i = 1; i < hist_item.rows; ++i)
        c_hist.at<float>(i) = hist_item.at<float>(i) + c_hist.at<float>(i - 1);

    normalize(c_hist, c_hist, 0, 255, NORM_MINMAX);                 // ���� ������׷� ����ȭ

    vector<Point> contour;                                          // ���� ������׷� ���

    for (int i = 1; i < histSize; ++i)
    {
        contour.clear();
        contour.push_back(Point(i, hist_h - cvRound(c_hist.at<float>(i))));
        contour.push_back(Point((i - 1), hist_h - cvRound(c_hist.at<float>(i - 1))));

        const Point* pts = (const cv::Point*)Mat(contour).data;
        int npts = Mat(contour).rows;

        polylines(img_histogram2, &pts, &npts, 1, true, Scalar(255, 255, 255));
    }

    Mat result;
    hconcat(img_histogram1, img_histogram2, result);

    return result;
}


int main()
{
    Mat img_gray = imread("test1.png", IMREAD_GRAYSCALE);

    Mat img_histo1 = draw_histogram(img_gray);                      // ��Ȱȭ �� ������׷�
    Mat result1;
    hconcat(img_gray, img_histo1, result1);
    imshow("result1", result1);

    Mat img_equ;                                                    // ��Ȱȭ �� ������׷�
    equalizeHist(img_gray, img_equ);
    Mat img_histo2 = draw_histogram(img_equ);
    Mat result2;
    hconcat(img_equ, img_histo2, result2);
    imshow("result2", result2);

    waitKey(0);

    return 0;
}

*/

///*
// ������ ������׷� ��Ȱȭ(CLAHE)

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Mat draw_histogram(Mat img)
{
    int hist_h = img.rows;
    int hist_w = 256;
    Mat img_histogram1(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));   // ������׷� ��� �̹��� ����

    Mat hist_item;                                                  // ������׷� �迭 ����

    int histSize = 256;                                             // �ȼ��� ����
    float range[] = { 0, 256 };
    const float* histRange = { range };
    bool uniform = true; bool accumulate = false;
                                                                    // ������׷� ��� �� ����ȭ
    calcHist(&img, 1, 0, Mat(), hist_item, 1, &histSize, &histRange, uniform, accumulate);
    normalize(hist_item, hist_item, 0, 255, NORM_MINMAX);

    for (int i = 1; i < histSize; i++)                              // ������׷� ���
        line(img_histogram1, Point(i, hist_h - cvRound(hist_item.at<float>(i))), Point(i, hist_h), Scalar(255, 255, 255));

    Mat img_histogram2(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));   // ���� ������׷� ��� �̹��� ����

    Mat c_hist(hist_item.size(), hist_item.type());                 // ���� ������׷� �迭 ����

    c_hist.at<float>(0) = hist_item.at<float>(0);                   // ���� ������׷� �迭�� ������׷� �迭 ����
    for (int i = 1; i < hist_item.rows; ++i)
        c_hist.at<float>(i) = hist_item.at<float>(i) + c_hist.at<float>(i - 1);

    normalize(c_hist, c_hist, 0, 255, NORM_MINMAX);                 // ���� ������׷� ����ȭ

    vector<Point> contour;                                          // ���� ������׷� ���

    for (int i = 1; i < histSize; ++i)
    {
        contour.clear();
        contour.push_back(Point(i, hist_h - cvRound(c_hist.at<float>(i))));
        contour.push_back(Point((i - 1), hist_h - cvRound(c_hist.at<float>(i - 1))));

        const Point* pts = (const cv::Point*)Mat(contour).data;
        int npts = Mat(contour).rows;

        polylines(img_histogram2, &pts, &npts, 1, true, Scalar(255, 255, 255));
    }

    Mat result;
    hconcat(img_histogram1, img_histogram2, result);

    return result;
}


int main()
{
    Mat img_gray = imread("test.png", IMREAD_GRAYSCALE);

    Mat img_histo1 = draw_histogram(img_gray);                      // ��Ȱȭ �� ������׷�
    Mat result1;
    hconcat(img_gray, img_histo1, result1);
    imshow("result1", result1);

    Mat img_clahe;                                                  // CLAHE ���� �� ������׷�
    Ptr<CLAHE> clahe = createCLAHE();
    clahe->setClipLimit(2.0);
    clahe->setTilesGridSize(Size(8, 8));

    clahe->apply(img_gray, img_clahe);

    Mat img_histo2 = draw_histogram(img_clahe);
    Mat result2;
    hconcat(img_clahe, img_histo2, result2);
    imshow("result2", result2);

    waitKey(0);

    return 0;
}

//*/