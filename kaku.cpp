#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <utility>   // pair
#include <algorithm> // sort
#include <map> // pair
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

	int a = 0,c = 0;
	vector<vector<double> > line_length{ { 150,40,110,40 },{ 40,60,40,60 },{ 40,40,56.5685 },{ 50.5685,70,50 },{ 30,20,50,60 },{ 60,80,60,80 } };
	vector<vector<double> > angle{ { 90,90,90,90 },{ 90,90,90,90 },{ 45,90,45 },{ 53.1302,81.8698,45 },{ 90,90,143.1302,36.8698 },{ 90,90,90,90 } };
	vector<vector<cv::Point> > vertex{ {} };
	vector<vector<pair<double, double> > > angle_pt;
	vector<vector<pair<double, double> > > line_pt;
	for (int i = 0; i < pieces; i++) {
		for (int j = 0; j < angle[i].size(); j++) {
			angle_pt.push_back(vector<pair<double, double> >() );
			if (angle[i][j] < N + gosa && angle[i][j] > N - gosa) {
				cout << "angle[" << i << "][" << j << "]　　　　　　　 角" << angle[i][j] << "です。" << endl;
				angle_pt[a].push_back(make_pair(i, j));
				a++;
			}
			for (int k = i + 1; k < pieces; k++) {
				for (int g = 0; g < angle[k].size(); g++) {
					if (angle[i][j] + angle[k][g] < N + gosa && angle[i][j] + angle[k][g] > N - gosa) {
						cout << "angle[" << i << "][" << j << "] & " << "angle[" << k << "][" << g << "] " <<
							"角" << angle[i][j] << "と" << angle[k][g] << "がセットです。" << endl;
						angle_pt[a].push_back(make_pair(i, j));
						angle_pt[a].push_back(make_pair(k, g));
						a++;
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
			line_pt.push_back(vector<pair<double, double> >());
			if (line_length[i][j] < M + gosa && line_length[i][j] > M - gosa) {
				cout << "line_length[" << i << "][" << j << "]　　　　　　　　　 辺" << line_length[i][j] << "です。" << endl;
				line_pt[c].push_back(make_pair(i, j));
				c++;
			}
			for (int k = i + 1; k < pieces; k++) {
				for (int g = 0; g < line_length[k].size(); g++) {
					if (line_length[i][j] + line_length[k][g] < M + gosa && line_length[i][j] + line_length[k][g] > M - gosa) {
						cout << "line_length[" << i << "][" << j << "] & " << "line_length[" << k << "][" << g << "] " <<
							"辺" << line_length[i][j] << "と" << line_length[k][g] << "がセットです。" << endl;
						line_pt[c].push_back(make_pair(i, j));
						line_pt[c].push_back(make_pair(k, g));
						c++;
					}
				}
			}
		}
	}
	for (int i = 0; i < a; i++) {
		cout << endl;
		for (int j = 0;j < angle_pt[i].size();j++) {
			cout << "[" << angle_pt[i][j].first << "][" << angle_pt[i][j].second << "] ";
		}
	}//動作テスト

	cout << endl;

	for (int i = 0; i < c; i++) {
		cout << endl;
		for (int j = 0;j < line_pt[i].size();j++) {
			cout << "[" << line_pt[i][j].first << "][" << line_pt[i][j].second << "] ";
		}
	}//動作テスト

	cv::imshow("hoge", img);
	cv::waitKey(0);
}
