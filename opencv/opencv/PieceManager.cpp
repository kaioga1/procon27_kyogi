# include "PieceManager.h"

# include "Piece.h"

PieceManager::PieceManager() {
	pieces = vector<shared_ptr<Piece> >(); //ピースの情報
}

void PieceManager::init_pieces(vector<shared_ptr<cv::Mat> > images) {
	for (int i = 0; i < images.size(); i++) {
		pieces.push_back(make_shared<Piece>(Piece(images[i], i)));
	}
}

bool PieceManager::hit_judge(cv::Point edge1, cv::Point edge2) {

	vector<shared_ptr<double>> angle1;
	vector<shared_ptr<double>> angle2;
	angle1.push_back(make_shared<double>());	//角度のデータ
	angle2.push_back(make_shared<double>());	//角度のデータ
	angle1 = pieces[edge1.y]->get_angle();
	angle2 = pieces[edge2.y]->get_angle();
	if (*angle1[edge1.x] + *angle2[edge2.x] > 180) {
		cout << "false " << *angle1[edge1.x] + *angle2[edge2.x] << endl;
		return false;
	}
	else {
		cout << "true " << *angle1[edge1.x] + *angle2[edge2.x] << endl;
		return true;
	}

}

void PieceManager::angle_dt() { 
	cv::Mat img = cv::Mat::zeros(300, 300, CV_8UC3);

	int a = 0;
	//vector<vector<double> > line_length{ { 110,40,110,40 },{ 40,60,40,60 },{ 40,40,56.5685 },{ 50.5685,70,50 },{ 30,20,50,60 },{ 60,80,60,80 } };
	//vector<vector<double> > angle{ { 90,90,90,90 },{ 90,90,90,90 },{ 45,90,45 },{ 53.1302,81.8698,45 },{ 90,90,143.1302,36.8698 },{ 90,90,90,90 } };
	vector<vector<cv::Point> > vertex;
	vector<vector<pair<double, double> > > angle_pt;

	vector<vector<shared_ptr<double> > > angles;
	for (int i = 0;i < pieces.size();i++) {
		angles.push_back(vector<shared_ptr<double> >());
		angles[i] = pieces[i] -> get_angle();
		for (int j = 0;j < angles[i].size();j++) {
			cout << "hoge" << *angles[i][j] << endl;
		}
	}

	angle_pt.push_back(vector<pair<double, double> >());
	for (int i = 0; i < pieces.size(); i++) {
		for (int j = 0; j < angles[i].size(); j++) {
			if (*angles[i][j] < N + gosa && *angles[i][j] > N - gosa) {
				cout << "angle[" << i << "][" << j << "]　　　　　　　 角" << *angles[i][j] << "です。" << endl;
				angle_pt.push_back(vector<pair<double, double> >());
				angle_pt[a].push_back(make_pair(i, j));
				a++;
			}
			for (int k = i + 1; k < pieces.size(); k++) {
				for (int g = 0; g < angles[k].size(); g++) {
					if (*angles[i][j] + *angles[k][g] < N + gosa && *angles[i][j] + *angles[k][g] > N - gosa) {
						cout << "angle[" << i << "][" << j << "] & " << "angle[" << k << "][" << g << "] " <<
							"角" << *angles[i][j] << "と" << *angles[k][g] << "がセットです。" << endl;
						angle_pt.push_back(vector<pair<double, double> >());
						angle_pt[a].push_back(make_pair(i, j));
						angle_pt[a].push_back(make_pair(k, g));
						a++;
					}
					else if (*angles[i][j] + *angles[k][g] < N - gosa) {
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

	cv::imshow("hoge", img);
}
void PieceManager::line_dt() {
	cv::Mat img = cv::Mat::zeros(300, 300, CV_8UC3);

	int c=0;
	vector<vector<cv::Point> > vertex;
	vector<vector<pair<double, double> > > line_pt;

	vector<vector<shared_ptr<double> > > lines;
	for (int i = 0;i < pieces.size();i++) {
		lines.push_back(vector<shared_ptr<double> >());
		lines[i] = pieces[i]->get_line_lengths();
		for (int j = 0;j < lines[i].size();j++) {
			cout << "hoge" << *lines[i][j] << endl;
		}
	}

	line_pt.push_back(vector<pair<double, double> >());
	for (int i = 0; i < pieces.size(); i++) {
		for (int j = 0; j < lines[i].size(); j++) {
			if (*lines[i][j] < M + gosa && *lines[i][j] > M - gosa) {
				cout << "line_length[" << i << "][" << j << "]　　　　　　　　　 辺" << *lines[i][j] << "です。" << endl;
				line_pt.push_back(vector<pair<double, double> >());
				line_pt[c].push_back(pair<double, double>(i, j));
				c++;
			}
			for (int k = i + 1; k < pieces.size(); k++) {
				for (int g = 0; g < lines[k].size(); g++) {
					if (*lines[i][j] + *lines[k][g] < M + gosa && *lines[i][j] + *lines[k][g] > M - gosa) {
						cout << "line_length[" << i << "][" << j << "] & " << "line_length[" << k << "][" << g << "] " <<
							"辺" << *lines[i][j] << "と" << *lines[k][g] << "がセットです。" << endl;
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

	for (int i = 0; i < c; i++) {
		cout << endl;
		for (int j = 0;j < line_pt[i].size();j++) {
			cout << "[" << line_pt[i][j].first << "][" << line_pt[i][j].second << "] ";
		}
	}//動作テスト

	cv::imshow("hoge", img);
	cv::waitKey(0);
}
