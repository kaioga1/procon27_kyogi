#include "opencv2\opencv.hpp"
#include <math.h>
#include <iostream>
#include <queue>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv/cvaux.h>
using namespace cv;
using namespace std;

double cor_x[100] = { 0 };
double cor_y[100] = { 0 };
double sen[100] = { 0 };

char no[300];

Mat im = imread("IMGP.jpg", 0);
Mat color_im = imread("IMGP.jpg", 1);
Mat im_canny, im_sobel, im_laplacian;
Mat img = Mat::zeros(600, 600, CV_8UC3);

int main(int argc, char **argv){
	int i,j=0,k = 0,x = 0;
	double root;
	int hoge = 0;


	if (!im.data){
		return -1;
	}

	Canny(im, im_canny, 50, 200);

	Sobel(im, im_sobel, CV_32F, 1, 1);
	convertScaleAbs(im_sobel, im_sobel, 1, 0);

	Laplacian(im, im_laplacian, CV_32F, 3);
	convertScaleAbs(im_laplacian, im_laplacian, 1, 0);

	//確率的ハフ変換による線分の検出＆描画
	vector<Vec4i> lines;
	
	HoughLinesP(im_canny, lines, 1, CV_PI / 180, 85, 30, 10);
	for (size_t i = 0; i < lines.size(); i++)
	{
	line(color_im, Point(lines[i][0], lines[i][1]),
	Point(lines[i][2], lines[i][3]), Scalar(0, 0, 255), 2, 8);
	}

	//直線の端の座標から頂点を割り出す
	Point ten[1600];
	Point ans[1600];
	Point zero = 0;
	for (size_t i = 0; i < lines.size(); i++){
		for (int j = 0; j < 4; j++){
			if (j % 2 == 0){
				ten[k].x = lines[i][j];
				k++;
			}
			else{
				ten[x].y = lines[i][j];
				x++;
			}
		}
	}
	for (i = 0; i < 1600; i++){
		if (ten[i] == zero){
			break;
		}
		cout << ten[i] << endl;
	}
	cout << endl;

	cout << ten[1].x + 1 << endl;

	cout << "mikan" << endl;

	for (int j = 0; j < i; j++){
		circle(color_im, Point(ten[j].x, ten[j].y), 10, Scalar(0, 255, 0), 1, 8);
	}

	//頂点の割り出し
	int m = 0;
	int count = 0;
	int anscount = 0;
	for (int j = 0; j < 1600; j++){
		for (int x = 0; x < i; x++){
			if (ten[m].x + j >= ten[x].x && ten[m].x - j <= ten[x].x && ten[m].y + j >= ten[x].y && ten[m].y - j <= ten[x].y && ten[m] != ten[x]){
				if (j <= 5){
					ans[anscount] = (ten[m] + ten[x]) / 2;
					cout << "!";
					anscount++;
				}
				cout << ten[m] << ten[x] << endl;
				if (x % 2 == 1){
					m = x - 1;
				}
				else{
					m = x + 1;
				}
				count++;
				j = 0;
				break;
			}
		}
		if (count == i / 2 -1){
			break;
		}
	}

	for (int i = 0; i < anscount; i++){
		cout << ans[i] << endl;
	}
	for (int i = 0; i < anscount; i++){
		if (i != anscount - 1){
			line(img, Point(ans[i].x, ans[i].y), Point(ans[i + 1].x, ans[i + 1].y), Scalar(0, 0, 255), 3, 8);
		}
		else{
			line(img, Point(ans[i].x, ans[i].y), Point(ans[0].x, ans[0].y), Scalar(0, 0, 255), 3, 8);
		}
	}

	imshow("canny", im_canny);
	imshow("sobel", im_sobel);
	imshow("laplacian", im_laplacian);
	imshow("original", im);
	imshow("はふ", color_im);
	imshow("再生成", img);

	waitKey(0);

	return 0;
}