#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <string.h>
#include <stdlib.h>
#include <vector>
#define pieces 6//ピースの数
#define gosa 1//誤差

using namespace std;

int main() {


	vector<vector<double> > frame{ { 90,90,90,90 },{ 100,150,100,150 } }; //仮枠
	vector<vector<double> > line_length{ { 110,40,110,40 },{ 40,60,40,60 },{ 40,40,56.5685 },{ 50.5685,70,50 },{ 50,60,30,20 },{ 60,80,60,80 } }; //仮辺
	//vector<vector<double> > line_length{ { 60,60,60,60 },{ 60,60,60,60 },{ 30,60,30,60 },{ 40,50,40,50 },{ 40,50,40,50 },{ 40,50,40,50 } };
	vector<vector<double> > angle{ { 90,90,90,90 },{ 90,90,90,90 },{ 45,90,45 },{ 53.1302,81.8698,45 },{ 90,90,143.1302,36.8698 },{ 90,90,90,90 } }; //仮角度
	//vector<vector<double> > angle{ { 90,90,90,90 },{ 90,90,90,90 },{ 90,90,90,90 },{ 90,90,90,90 },{ 90,90,90,90 },{ 90,90,90,90 } };
	vector<vector<cv::Point> > vertex;
	cv::Mat img = cv::Mat::zeros(300, 300, CV_8UC3);
	int a = 0;
	int c = 0;
	vector<vector<pair<double, double> > > line_pt; //複数の組み合わせで枠の辺の長さに合うものを記録
	vector<vector<pair<double, double > > > angle_pt; //複数の組み合わせで枠の角度に合うものを記録
	//vector<vector<pair<double, double> > > line_save;

	for (int x = 0;x < frame[0].size();x++) {
		angle_pt.push_back(vector<pair<double, double> >());
		for (int i = 0; i < pieces; i++) {
			for (int j = 0; j < angle[i].size(); j++) {
				if (angle[i][j] < frame[0][x] + gosa && angle[i][j] > frame[0][x] - gosa) {
					cout << "angle[" << i << "][" << j << "]　　　　　　　 角" << angle[i][j] << "です。" << endl;
					angle_pt.push_back(vector<pair<double, double> >());
					angle_pt[a].push_back(make_pair(i, j)); //ピース単体で枠の角度と一致するものを保持
					a++;
				}
				for (int k = i + 1; k < pieces; k++) {
					for (int g = 0; g < angle[k].size(); g++) {
						//枠の辺の長さからあてはめたピースの隣接する辺の長さを差し引いたとき、長さが一致する辺をもつピースの探索
						if (frame[1][x] - line_length[i][j] < line_length[k][g] + gosa && frame[1][x] - line_length[i][j] > line_length[k][g] - gosa) {
							cout << "pair[" << i << "][" << j << "]" << line_length[i][j] << " & " << 
								 "[" << k << "][" << g << "]" << line_length[k][g] << endl;
							if (j == line_length[i].size()-1) {
								if (g == 0) {
									if (line_length[i].front() == line_length[k].back()) {
										cout << "" << line_length[i].front() << " & " << line_length[k].back() << endl;
									}
								}
								else {
									if (line_length[i][0] == line_length[k][g - 1]) {
										cout << endl << "hogeeeee" << line_length[i].front() << " & " <<  line_length[k][g - 1] << endl;
									}
								}
							}
							else {
								if (g == 0) {
									cout << endl << "hogearts" << endl;
									if (line_length[i][j + 1] == line_length[k].back()) {
										cout << endl << "hogennnnn" << line_length[i][j+1] << " & " << line_length[k].back() << endl;
									}
								}
								else {
									cout << endl << "hogegegegegegege" << endl;
									if (line_length[i][j + 1] == line_length[k][g - 1]) {
										cout << endl << "perfect hoge" << line_length[i][j + 1] << " & " << line_length[k][g - 1] << endl;
									}
								}
							}
						}

						if (line_length[i][j] == line_length[i].back()) {
							if (line_length[k][g] == line_length[k].front()) {
								if (line_length[i].front() == line_length[k].back()) {
									cout << endl << "hogehoge" << endl;
								}
							}
						}

						if (angle[i][j] + angle[k][g] < frame[0][x] + gosa && angle[i][j] + angle[k][g] > frame[0][x] - gosa) {
							cout << "angle[" << i << "][" << j << "] & " << "angle[" << k << "][" << g << "] " <<
								"角" << angle[i][j] << "と" << angle[k][g] << "がセットです。" << endl;
							angle_pt.push_back(vector<pair<double, double> >());
							angle_pt[a].push_back(make_pair(i, j));
							angle_pt[a].push_back(make_pair(k, g));
							a++;
						}
						else if (angle[i][j] + angle[k][g] < frame[0][x] - gosa) {
						}
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







	/*for (int z = 0;z < frame[1].size(); z++) {
		line_pt.push_back(vector<pair<double, double> >());
		for (int i = 0; i < pieces; i++) {
			for (int j = 0; j < line_length[i].size(); j++) {
				if (line_length[i][j] < frame[1][z] + gosa && line_length[i][j] > frame[1][z] - gosa) {
					cout << "line_length[" << i << "][" << j << "]　　　　　　　　　 辺" << line_length[i][j] << "です。" << endl;
					line_pt.push_back(vector<pair<double, double> >());
					line_pt[c].push_back(pair<double, double>(i, j));
					c++;
				}
				for (int k = i + 1; k < pieces; k++) {
					for (int g = 0; g < line_length[k].size(); g++) {
						if (line_length[i][j] + line_length[k][g] < frame[1][z] + gosa && line_length[i][j] + line_length[k][g] > frame[1][z] - gosa) {
							cout << "line_length[" << i << "][" << j << "] & " << "line_length[" << k << "][" << g << "] " <<
								"辺" << line_length[i][j] << "と" << line_length[k][g] << "がセットです。" << endl;
							line_pt.push_back(vector<pair<double, double> >());
							line_pt[c].push_back(pair<double, double>(i, j));
							line_pt[c].push_back(pair<double, double>(k, g));
							cout << endl;
							c++;
						}
					}
				}
			}
		}
		cout << endl;
	}

	for (int i = 0; i < c; i++) {
		cout << endl;
		for (int j = 0;j < line_pt[i].size();j++) {
			cout << "[" << line_pt[i][j].first << "][" << line_pt[i][j].second << "] ";
		}
	}//動作テスト
	*/
	cv::imshow("hoge", img);
	cv::waitKey(0);
}