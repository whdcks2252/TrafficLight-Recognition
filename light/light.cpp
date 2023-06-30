//#include "vision.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <vector>
#include <iostream>
#include <string>


using namespace cv;
using namespace std;

#define PI 3.141592

vector<Point> FindLocalMaxima(Mat &src); //Funtion we use to find cornerpoints

int main()
{
	// 이미지 입력
	Mat img = imread("sample3.jpg", IMREAD_COLOR);
	Mat templ = imread("temp.jpg", IMREAD_COLOR);

	img = img + Scalar(50, 50, 50);

	Mat noise(img.size(), CV_32SC3);
	randn(noise, 0, 10);
	add(img, noise, img, Mat(), CV_8UC3);

    // Template Matching
	Mat res, res_norm;
	matchTemplate(img, templ, res, TM_CCOEFF_NORMED);
	normalize(res, res_norm, 0, 255, NORM_MINMAX, CV_8U);

	double maxv;
	Point maxloc;
	minMaxLoc(res, 0, &maxv, 0, &maxloc);

	rectangle(img, Rect(maxloc.x, maxloc.y, templ.cols, templ.rows), Scalar(0, 0, 0), 2);


	//ROI를 Template Matching 영역으로 설정
	Mat Img;
	Img = img(Rect(maxloc.x, maxloc.y, templ.cols, templ.rows));

	Mat Gray_Img, FilteredImage;
	cvtColor(Img, Gray_Img, COLOR_BGR2GRAY);

	bilateralFilter(Gray_Img, FilteredImage, -1, 10, 10);


	//원 검출
	vector<Vec3f> circles;
	HoughCircles(FilteredImage, circles, HOUGH_GRADIENT, 1, 5, 150, 8, 1, 4);

	for (int i = 0; i < circles.size(); i++) { cout << "center: " << circles[i][0] << endl; }//각 원 순서대로 중심점 색 정보 출력

	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);

		circle(lmg, center, radius, Scalar(0, 0, 255), 1, LINE_AA);//outline  화면에 원 그리는 함수 

		imshow("dst", img);
	}


	//원의 중심 좌표 저장
	int k1 = circles[0][0];//x 
	int j1 = circles[0][1];//y

	int k2 = circles[1][0];//x 
	int j2 = circles[1][1];//y

	int k3 = circles[2][0];//x 
	int j3 = circles[2][1];//y

    //원의 중심 좌표를 출력하고, 중심에서의 B,G,R 저장
	cout << "k1: " << k1 << " j1: " << j1 << endl;
	int B1 = Img.at<Vec3b>(j1, k1)[0]; 
	int G1 = Img.at<Vec3b>(j1, k1)[1];
	int R1 = Img.at<Vec3b>(j1, k1)[2];

	cout << "k2: " << k2 << " j2: " << j2 << endl;
	int B2 = Img.at<Vec3b>(j2, k2)[0]; 
	int G2 = Img.at<Vec3b>(j2, k2)[1];
	int R2 = Img.at<Vec3b>(j2, k2)[2];

	cout << "k3: " << k3 << " j3: " << j3 << endl;
	int B3 = Img.at<Vec3b>(j3, k3)[0]; 
	int G3 = Img.at<Vec3b>(j3, k3)[1];
	int R3 = Img.at<Vec3b>(j3, k3)[2];

	// 저장된 B,G,R출력
	cout << "B1 : " << B1 << endl;
	cout << "G1 : " << G1 << endl;
	cout << "R1 : " << R1 << endl;

	cout << "B2 : " << B2 << endl;
	cout << "G2 : " << G2 << endl;
	cout << "R2 : " << R2 << endl;

	cout << "B3 : " << B3 << endl;
	cout << "G3 : " << G3 << endl;
	cout << "R3 : " << R3 << endl;

	// 중심 좌표와 색상 정보에 대한 조건문을 설정하여, 각 신호에 대한 알림 출력
	if (R3 == 255 && B3 == 255 && k3 < k2 < k1) { cout << "-----the RedLight : Stop-----" << endl; }
	if (B1 == 255 && G1 == 255 && k2 < k3 < k1) { cout << "-----the GreenLight : Go straight-----" << endl; }
	if (R1 == 255 && G1 == 255 && k2 < k1 < k3) { cout << "-----the YellowLight : Caution-----" << endl; }

	waitKey(0);
	return 0;
}


vector<Point> FindLocalMaxima(Mat & src)
{
	return vector<Point>();
}
