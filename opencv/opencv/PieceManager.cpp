# include "PieceManager.h"

# include "Piece.h"

PieceManager::PieceManager() {
	pieces = vector<shared_ptr<Piece> >(); //繝斐・繧ｹ縺ｮ諠・ｱ
}

void PieceManager::init_pieces(vector<shared_ptr<cv::Mat> > images) {
	for (int i = 0; i < images.size(); i++) {
		pieces.push_back(make_shared<Piece>(Piece(images[i], i)));
	}
}

//当たり判定　角度二つを渡して使ってください
bool PieceManager::hit_judge(cv::Point edge1, cv::Point edge2) {

	vector<shared_ptr<double>> angle1;
	vector<shared_ptr<double>> angle2;
	angle1.push_back(make_shared<double>());	//隗貞ｺｦ縺ｮ繝・・繧ｿ
	angle2.push_back(make_shared<double>());	//隗貞ｺｦ縺ｮ繝・・繧ｿ
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

//辺の長さと合うパターンの割り出し　長さを渡して使ってください
void PieceManager::sertch_line(double to_find_line) {

	//組み合わせたピースを格納する
	vector<vector<shared_ptr<double> > > marged_line;
	vector<vector<shared_ptr<double> > > line_clone;
	//一度通ったところをふさぐための変数
	vector<vector<shared_ptr<double>>> stack_deadend;
	vector<shared_ptr<double> > line_once;
	shared_ptr<double> line_min;
	int test = 0;
	int flag = 0;
	int sameflag = 0;
	int limitflag = 0;
	int sp = 0;
	int reject = 1;
	stack<shared_ptr<double>> line_stack;
	//一度通ったパターンを記録しておく変数


	//二次元配列のcloneにパーツの辺の全情報を格納
	for (int i = 0; i < pieces.size(); i++) {
		line_once.push_back(shared_ptr<double>());
		line_once = pieces[i]->get_line_lengths();
		line_clone.push_back(vector<shared_ptr<double> >());
		line_clone[i] = line_once;
	}

	//一番短い辺を求める。後で使う
	line_min = line_clone[0][0];
	for (int i = 0; i < line_clone.size(); i++){
		for (int j = 0; j < line_clone[i].size(); j++) {
			if (*line_min > *line_clone[i][j]) {
				line_min = line_clone[i][j];
			}
		}

	}



	//pushしたらto_find_lineからpushした辺の分の長さを引くのを忘れずに

	//深さ優先探索で実装
	line_stack.push(line_clone[0][0]);
	stack_deadend.push_back(vector<shared_ptr<double> >());
	marged_line.push_back(vector<shared_ptr<double> >());

	while (!line_stack.empty()) {
		for (int i = 0; i < line_clone.size(); i++) {
			sameflag = 0;
			for (int j = 0; j < line_clone[i].size(); j++) {
			//同じ図形の辺が含まれないようにする
				/*for (int k = 0; k + 1 < stack_deadend[stack_deadend.size() - 1].size(); k++) {
					for (int l = 0; l + 1 < line_clone[i].size(); l++) {
						if (stack_deadend[stack_deadend.size() - 1][k] == line_clone[i][l]) {
							sameflag = 1;
						}
					}
				}
				if (sameflag == 1) {
					break;
				}*/
				for (int x = 0; x < line_clone[i].size(); x++) {
					for (int y = 0; y < stack_deadend[stack_deadend.size() - 1].size(); y++) {
						if (line_clone[i][x] == stack_deadend[stack_deadend.size() - 1][y]) {
							sameflag = 1;
						}
						if (sameflag == 1) {
							break;
						}
					}
					if (sameflag == 1) {
						break;
					}
				}
				if (sameflag == 1) {
					break;
				}


			//一度通ったところにもぐれないように
				limitflag = 0;
				for (int k = 0; k + 1 < stack_deadend.size(); k++) {
					stack_deadend[stack_deadend.size() - 1].push_back(line_clone[i][j]);

					if (stack_deadend[stack_deadend.size() - 1] == stack_deadend[k]) {
						limitflag = 1;
					}
					stack_deadend[stack_deadend.size() - 1].pop_back();
				}

				//for内の以下の処理をすべてかっとばす
				if (limitflag == 1) {
					continue;
				}
				
				//to_find_lineと誤差が-10までの辺をpush
				if (*line_clone[i][j]<= to_find_line && *line_clone[i][j] >= to_find_line - 5) {
					line_stack.push(line_clone[i][j]);
					marged_line[marged_line.size() - 1].push_back(line_clone[i][j]);
					to_find_line -= *line_clone[i][j]; //ひく
					stack_deadend[stack_deadend.size() - 1].push_back(line_clone[i][j]);
					flag = 1;
				}
				//求めたい辺の長さより短いものをpushただし残りの辺が最小の辺より小さくならないように
				else if (*line_clone[i][j] < to_find_line && to_find_line - *line_clone[i][j] >= *line_min) {
					line_stack.push(line_clone[i][j]);
					marged_line[marged_line.size() - 1].push_back(line_clone[i][j]);
					to_find_line -= *line_clone[i][j];
					stack_deadend[stack_deadend.size() - 1].push_back(line_clone[i][j]);
					flag = 1;
				}
				if (flag == 1) {
					break;
				}
			}
			if (flag == 1) {
				break;
			}
		}

		//適する辺が見つかっていなければflagは0のはず(これ以上潜れない)
		if (flag == 0) {
			//次の行へ
			stack_deadend.push_back(vector < shared_ptr<double> > ());
			for (int i = 0; i < stack_deadend[stack_deadend.size() - 2].size(); i++) {
				stack_deadend[stack_deadend.size() - 1].push_back(stack_deadend[stack_deadend.size() - 2][i]);
			}
			stack_deadend[stack_deadend.size() - 1].pop_back();
			marged_line[marged_line.size() - 1].pop_back();
			to_find_line += *line_stack.top(); //たす
			line_stack.pop(); //なくす
		}

		flag = 0;
		//求めたい辺の長さが10以下だったときに答えとみなしてpushback
		if (to_find_line <= 5) {
			marged_line.push_back(vector<shared_ptr<double> >());
			for (int i = 0; i < marged_line[marged_line.size() - 2].size(); i++) {
				marged_line[marged_line.size() - 1].push_back(marged_line[marged_line.size() - 2][i]);
			}
			marged_line[marged_line.size() - 1].pop_back();
			stack_deadend.push_back(vector < shared_ptr<double> >());
			for (int i = 0; i < stack_deadend[stack_deadend.size() - 2].size(); i++) {
				stack_deadend[stack_deadend.size() - 1].push_back(stack_deadend[stack_deadend.size() - 2][i]);
			}
			stack_deadend[stack_deadend.size() - 1].pop_back();
			to_find_line += *line_stack.top();
			line_stack.pop();
		}
	}
	for (int i = 0; i < stack_deadend.size(); i++) {
		for (int j = 0; j < stack_deadend[i].size(); j++) {
			cout << *stack_deadend[i][j] << " ";
		}
		cout << endl;
	}
	for (int i = 0; i < marged_line.size(); i++) {
		for (int j = 0; j < marged_line[i].size(); j++) {
			cout << *marged_line[i][j] << " ";
		}
		cout << endl;
	}
}

void PieceManager::sertch_edge(vector<shared_ptr<double> > frame) {
	vector<vector<shared_ptr<double> > > edge_clone;
	vector<shared_ptr<double> > frame_edge;
	shared_ptr<double> nearest_edge = 0;
	double edge_sourse;
	
	for (int i = 0; i < pieces.size(); i++) {
		edge_clone.push_back(pieces[i]->get_angle());
	}
	for (int i = 0; i < frame.size(); i++) {
		frame_edge.push_back(frame[i]);
	}
	for (int i = 0; i < edge_clone.size(); i++) {
		for (int j = 0; j < edge_clone[i].size(); j++) {
			cout << *edge_clone[i][j] << " ";
		}
		cout << endl;
	}
	for (int i = 0; i < frame.size(); i++) {
		cout << *frame_edge[i] << endl;
	}
	cout << endl;
	//枠の角のサイズに一番近い角を見つける処理
	edge_sourse = abs(*frame_edge[0] - *edge_clone[0][0]);
	for (int i = 0; i < edge_clone.size(); i++) {
		for (int j = 0; j < edge_clone[i].size(); j++) {
			if (*edge_clone[i][j] < *frame_edge[0] + edge_sourse && *edge_clone[i][j] > *frame_edge[0] - edge_sourse){
				edge_sourse = abs(*frame_edge[0] - *edge_clone[i][j]);
				nearest_edge = edge_clone[i][j];
				cout << *edge_clone[i][j] << endl;
			}
		}
	}
	cout << endl;
	cout << edge_sourse << endl;
}
void PieceManager::Frame_update() {
	
}

void PieceManager::Frame_record() {

}

void PieceManager::answer_draw() {

}

void PieceManager::marge_piece() {
	vector<vector<shared_ptr<double> > > line_clone;
	vector<vector<shared_ptr<double> > > edge_clone;

	for (int i = 0; i < pieces.size(); i++) {
		edge_clone.push_back(pieces[i]->get_angle());
	}

	for (int i = 0; i < pieces.size(); i++) {
		line_clone.push_back(pieces[i]->get_line_lengths());
	}

	for (int i = 0; i < line_clone.size(); i++) {
		for (int j = 0; j < line_clone[i].size(); j++) {
			cout << *edge_clone[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < line_clone.size(); i++) {
		for (int j = 0; j < line_clone[i].size(); j++) {
			cout << *line_clone[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;
	//足すと360に近いピースを探す
	for (int i = 0; i < edge_clone.size(); i++) {
		for (int j = 0; j < edge_clone[i].size(); j++) {
			for (int k = 0; k < edge_clone.size(); k++) {
				for (int l = 0; l < edge_clone[k].size(); l++) {
					if (*edge_clone[i][j] + *edge_clone[k][l] < 360 + 5 && *edge_clone[i][j] + *edge_clone[k][l] > 360 - 5 && k > i) {
						cout << *edge_clone[i][j] << "," << *edge_clone[k][l] << "," << *edge_clone[i][j] + *edge_clone[k][l] << endl;
						cout << i + 1 << "," << j + 1 << " " << k + 1 << "," << l + 1 << endl; 

						if (*line_clone[i][j] < *line_clone[k][l] + 5 && *line_clone[i][j] > *line_clone[k][l] - 5) {
							cout << "hoge" << endl;
							if (*line_clone[i][j - 1] < *line_clone[k][l - 1] + 5 && *line_clone[i][j - 1] > *line_clone[k][l - 1] - 5) {
								cout << "true" << endl;
							}
							else {
								cout << "false" << endl;
							}
						}
						else {
							cout << "false" << endl;
						}

						if (*line_clone[i][j - 1] < *line_clone[k][l] + 5 && *line_clone[i][j - 1] > *line_clone[k][l] - 5) {
							cout << "hoge" << endl;
							if (*line_clone[i][j] < *line_clone[k][l - 1] + 5 && *line_clone[i][j] > *line_clone[k][l - 1] - 5) {
								cout << "true" << endl;
							}
							else {
								cout << "false" << endl;
							}
						}
						else {
							cout << "false" << endl;
						}

					}
				}
			}
		}
	}

}