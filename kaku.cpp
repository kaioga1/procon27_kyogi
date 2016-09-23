#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <string.h>
#include <stdlib.h>
#include <vector>
#define pieces 6//ピースの数
#define N 90//求めたい角度
#define M 150 //求めたい辺
#define gosa 1//誤差
using namespace std;

/*void mitsuha(){
cout << angle[0][0] << endl;
}*/

int main() {
	cv::Mat img = cv::Mat::zeros(300, 300, CV_8UC3);

	vector<vector<double> > line_length{ { 110,40,110,40 },{ 40,60,40,60 },{ 40,40,56.5685 },{ 50.5685,70,50 },{ 30,20,50,60 },{ 60,80,60,80 } };
	vector<vector<double> > angle{ { 90,90,90,90 },{ 90,90,90,90 },{ 45,90,45 },{ 53.1302,81.8698,45 },{ 90,90,143.1302,36.8698 },{ 90,90,90,90 } };
	vector<vector<cv::Point> > vertex{ {} };
	for (int i = 0; i < pieces; i++) {
		for (int j = 0; j < angle[i].size(); j++) {
			if (angle[i][j] < N + gosa && angle[i][j] > N - gosa) {
				cout << "angle[" << i << "][" << j << "]　　　　　　　 角" << angle[i][j] << "です。" << endl;
			}
			for (int k = i + 1; k < pieces; k++) {
				for (int g = 0; g < angle[k].size(); g++) {
					if (angle[i][j] + angle[k][g] < N + gosa && angle[i][j] + angle[k][g] > N - gosa) {
						cout << "angle[" << i << "][" << j << "] & " << "angle[" << k << "][" << g << "] " <<
							"角" << angle[i][j] << "と" << angle[k][g] << "がセットです。" << endl;
					}
					else if (angle[i][j] + angle[k][g] < N - gosa) {
						//mitsuha();
					}
				}
			}
		}
	}

	for (int i = 0; i < pieces; i++) {
		for (int j = 0; j < line_length[i].size(); j++) {
			if (line_length[i][j] < N + gosa && line_length[i][j] > N - gosa) {
				cout << "line_length[" << i << "][" << j << "]　　　　　　　 角" << angle[i][j] << "です。" << endl;
			}
			for (int k = i + 1; k < pieces; k++) {
				for (int g = 0; g < line_length[k].size(); g++) {
					if (line_length[i][j] + line_length[k][g] < M + gosa && line_length[i][j] + line_length[k][g] > M - gosa) {
						cout << "line_length[" << i << "][" << j << "] & " << "line_length[" << k << "][" << g << "] " <<
							"辺" << line_length[i][j] << "と" << line_length[k][g] << "がセットです。" << endl;
					}
				}
			}
		}
	}
	cout << angle[0][0] << angle[2].size() << angle[0].back() << endl;//動作テスト

	cv::imshow("hoge", img);
	cv::waitKey(0);
}
