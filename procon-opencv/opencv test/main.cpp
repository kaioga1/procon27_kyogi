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

	//固有値に基づいたコーナー検出
	/*vector<Point2f> corners;
	goodFeaturesToTrack(im_canny, corners, 10, 0.4, 5);
	vector<Point2f>::iterator it_corner = corners.begin();
	for (i = 0; it_corner != corners.end(); it_corner++, i++){
		circle(im, Point(it_corner->x, it_corner->y), 1, Scalar(0, 255, 0), -1);
		circle(im, Point(it_corner->x, it_corner->y), 8, Scalar(0, 255, 0));
		sprintf(no, "%d", i);
		putText(im_laplacian, no, Point(it_corner->x, it_corner->y), FONT_HERSHEY_SIMPLEX, 2, Scalar(255, 255, 255), 2);
		cor_x[i] = it_corner->x;
		cor_y[i] = it_corner->y;
	}
	for (int j = 0; j < i; j++){
		if (j + 1 > i){
			root = ((cor_x[j] - cor_x[0]) * (cor_x[j] - cor_x[0])) + ((cor_y[j] - cor_y[0]) * (cor_y[j] - cor_y[0]));
			sen[j] = sqrt(root);
		}
		else{
			root = ((cor_x[j] - cor_x[j + 1]) * (cor_x[j] - cor_x[j + 1])) + ((cor_y[j] - cor_y[j + 1]) * (cor_y[j] - cor_y[j + 1]));
			sen[j] = sqrt(root);
		}
	}*/

	// Harris検出器を使った検出
	/*goodFeaturesToTrack(im_canny, corners, 8, 0.1, 3, Mat(), 3, true);
	it_corner = corners.begin();
	for (i=0; it_corner != corners.end(); ++it_corner,i++) {
	circle(im_laplacian, Point(it_corner->x, it_corner->y), 1, Scalar(0, 0, 0), -1);
	circle(im_laplacian, Point(it_corner->x, it_corner->y), 8, Scalar(0, 0, 0));
	sprintf(no, "%d", i);
	putText(im_laplacian, no, Point(it_corner->x, it_corner->y), FONT_HERSHEY_SIMPLEX, 2, Scalar(255, 255, 255), 2);
	cor_x[i] = it_corner->x;
	cor_y[i] = it_corner->y;
	}*/

	//FASTアルゴリズムを用いた検出
	/*int threshold = 100;
	bool nonmax = true;
	vector<KeyPoint> keypoints;
	FAST(im, keypoints, threshold, nonmax);
	vector<KeyPoint>::iterator it_kp = keypoints.begin();
	for (i = 0; it_kp != keypoints.end(); ++it_kp,i++) {
	circle(im_laplacian, Point(it_kp->pt.x, it_kp->pt.y), 1, Scalar(0, 0, 0), -1);
	circle(im_laplacian, Point(it_kp->pt.x, it_kp->pt.y), 8, Scalar(0, 0, 0));
	sprintf(no, "%d", i);
	putText(im_laplacian, no, Point(it_kp->pt.x, it_kp->pt.y), FONT_HERSHEY_SIMPLEX, 2, Scalar(255, 255, 255), 2);
	cor_x[i] = it_kp->pt.x;
	cor_y[i] = it_kp->pt.y;
	}*/

	/*vector<Vec2f> lines;
	HoughLines(im_laplacian, lines, 1, CV_PI / 180, 160);
	Point memory1[1000] = {0};
	Point memory2[1000] = {0};
	Point boo1[1000] = { 0 };
	Point boo2[1000] = { 0 };
	Point boo[1000] = { 0 };
	bool xstate[1000] = { 0 };  //falseなら同符号trueなら異符号
	bool ystate[1000] = { 0 };
	

	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0];
		float theta = lines[i][1];
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		Point pt1(cvRound(x0 + 1000 * (-b)),
			cvRound(y0 + 1000 * (a)));
		Point pt2(cvRound(x0 - 1000 * (-b)),
			cvRound(y0 - 1000 * (a)));
		line(color_im, pt1, pt2, Scalar(0, 0, 255), 1, 8);
		//cout << pt1 << " " << pt2 << endl;
		//cout << pt1 + pt2 / 2 << endl;
		memory1[i] = pt1;
		memory2[i] = pt2;
	}*/

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


	/*for (int i = 0; i < 1000; i++){
		if (memory1[i] == zero){
			break;
		}
		cout << memory1[i] << " " << memory2[i] << endl;
		if (memory1[i].x < 0){     //符号をそろえて計算をできるように
			boo1[i].x = memory1[i].x * -1;
			xstate[i] = !xstate[i];  //符号を切り替えたのでstateの状態の変更
		}
		else{
			boo1[i].x = memory1[i].x;
		}
		if (memory1[i].y < 0){
			boo1[i].y = memory1[i].y * -1;
			ystate[i] = !ystate[i];
		}
		else{
			boo1[i].y = memory1[i].y;
		}
		if (memory2[i].x < 0){
			boo2[i].x = memory2[i].x * -1;
			xstate[i] = !xstate[i];
		}
		else{
			boo2[i].x = memory2[i].x;
		}
		if (memory2[i].y < 0){
			boo2[i].y = memory2[i].y * -1;
			ystate[i] = !ystate[i];
		}
		else{
			boo2[i].y = memory2[i].y;
		}
		cout << boo1[i] << " " << boo2[i] << endl;

		if (boo1[i].x < boo2[i].x && xstate[i] == false){
			boo[i].x = boo2[i].x - boo1[i].x;
		}
		if (boo1[i].x > boo2[i].x && xstate[i] == false){

		}
		if (xstate[i] == true){
			boo[i].x = boo1[i].x + boo2[i].x;
		}
	}*/
		
	//交点を求める処理
	/*for (int i = 0; i < 4; i++){
		for ()
	}*/

	imshow("canny", im_canny);
	imshow("sobel", im_sobel);
	imshow("laplacian", im_laplacian);
	imshow("original", im);
	imshow("はふ", color_im);
	imshow("再生成", img);

	waitKey(0);

	return 0;
}