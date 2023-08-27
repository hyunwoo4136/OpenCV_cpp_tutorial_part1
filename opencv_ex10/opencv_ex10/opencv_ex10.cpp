/*
// erosion 모폴로지 (흰 오브잭트 외곽 픽셀을 0으로)

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
    Mat img_gray;
    img_gray = imread("test.png", IMREAD_GRAYSCALE);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3)); // 커널 생성
    Mat img_result;
    erode(img_gray, img_result, kernel, Point(-1, -1), 1);      // erosion 적용
                                //(입력 이미지, 결과 이미지, 커널, 앵커 좌표, 반복 수)
    imshow("Input", img_gray);
    imshow("Result", img_result);
    waitKey(0);

    return 0;
}

*/

/*
// dilation 모폴로지 (흰 오브잭트 외곽 픽셀을 1로)

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
    Mat img_gray;
    img_gray = imread("test.png", IMREAD_GRAYSCALE);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    Mat img_result;
    dilate(img_gray, img_result, kernel, Point(-1, -1), 1);     // dilation 적용

    imshow("Input", img_gray);
    imshow("Result", img_result);
    waitKey(0);

    return 0;
}

*/

/*
// opening 모폴로지 (erosion 후 dilation, 이미지의 흰 노이즈 제거)

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
    Mat img_gray;
    img_gray = imread("test2.png", IMREAD_GRAYSCALE);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    Mat img_result;
    morphologyEx(img_gray, img_result, MORPH_OPEN, kernel);     // opening 적용

    imshow("Input", img_gray);
    imshow("Result", img_result);
    waitKey(0);

    return 0;
}

*/

///*
// closing 모폴로지 (dilation 후 erosion, 이미지의 검은 노이즈 제거)

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
    Mat img_gray;
    img_gray = imread("test3.png", IMREAD_GRAYSCALE);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(11, 11));
    Mat img_result;
    morphologyEx(img_gray, img_result, MORPH_CLOSE, kernel);    // closing 적용

    imshow("Input", img_gray);
    imshow("Result", img_result);
    waitKey(0);

    return 0;
}

//*/