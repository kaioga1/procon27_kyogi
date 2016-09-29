# include "PieceManager.h"

# include "Piece.h"

PieceManager::PieceManager() {
	pieces = vector<shared_ptr<Piece> >(); //ãƒ”ãƒ¼ã‚¹ã®æƒ…å ±
}

void PieceManager::init_pieces(vector<shared_ptr<cv::Mat> > images) {
	for (int i = 0; i < images.size(); i++) {
		pieces.push_back(make_shared<Piece>(Piece(images[i], i)));
	}
}

//“–‚½‚è”»’è@Šp“x“ñ‚Â‚ğ“n‚µ‚Äg‚Á‚Ä‚­‚¾‚³‚¢
bool PieceManager::hit_judge(cv::Point edge1, cv::Point edge2) {

	vector<shared_ptr<double>> angle1;
	vector<shared_ptr<double>> angle2;
	angle1.push_back(make_shared<double>());	//è§’åº¦ã®ãƒ‡ãƒ¼ã‚¿
	angle2.push_back(make_shared<double>());	//è§’åº¦ã®ãƒ‡ãƒ¼ã‚¿
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

<<<<<<< HEAD
//•Ó‚Ì’·‚³‚Æ‡‚¤ƒpƒ^[ƒ“‚ÌŠ„‚èo‚µ@’·‚³‚ğ“n‚µ‚Äg‚Á‚Ä‚­‚¾‚³‚¢
void PieceManager::sertch_line(double to_find_line) {

	//‘g‚İ‡‚í‚¹‚½ƒs[ƒX‚ğŠi”[‚·‚é
	vector<vector<shared_ptr<double> > > marged_line;
	vector<vector<shared_ptr<double> > > line_clone;
	//ˆê“x’Ê‚Á‚½‚Æ‚±‚ë‚ğ‚Ó‚³‚®‚½‚ß‚Ì•Ï”
	vector<vector<shared_ptr<double>>> stack_deadend;
	vector<shared_ptr<double> > line_once;
	shared_ptr<double> line_min;
	int test = 0;
	int flag = 0;
	//deadend‚ğ”‚¦‚é—p‚Ì•Ï”
	int dcount = 0;
	//marged_line‚ğ”‚¦‚é—p‚Ì•Ï”
	int mcount = 0;
	stack<shared_ptr<double>> line_stack;
	//ˆê“x’Ê‚Á‚½ƒpƒ^[ƒ“‚ğ‹L˜^‚µ‚Ä‚¨‚­•Ï”


	//“ñŸŒ³”z—ñ‚Ìclone‚Éƒp[ƒc‚Ì•Ó‚Ì‘Sî•ñ‚ğŠi”[
	for (int i = 0; i < pieces.size(); i++) {
		line_once.push_back(shared_ptr<double>());
		line_once = pieces[i]->get_line_lengths();
		line_clone.push_back(vector<shared_ptr<double> >());
		line_clone[i] = line_once;
	}

	//ˆê”Ô’Z‚¢•Ó‚ğ‹‚ß‚éBŒã‚Åg‚¤
	line_min = line_clone[0][0];
	for (int i = 0; i < line_clone.size(); i++){
		for (int j = 0; j < line_clone[i].size(); j++) {
			if (line_min > line_clone[i][j]) {
				line_min = line_clone[i][j];
			}
		}

	}

	//push‚µ‚½‚çto_find_line‚©‚çpush‚µ‚½•Ó‚Ì•ª‚Ì’·‚³‚ğˆø‚­‚Ì‚ğ–Y‚ê‚¸‚É

	//[‚³—Dæ’Tõ‚ÅÀ‘•
	line_stack.push(line_clone[0][0]);
	stack_deadend.push_back(vector<shared_ptr<double> >());
	marged_line.push_back(vector<shared_ptr<double> >());
	while (!line_stack.empty()) {
		for (int i = 0; i < line_clone.size(); i++) {
			for (int j = 0; j < line_clone[i].size(); j++) {
				//to_find_line‚ÆŒë·‚ª+-10‚Ü‚Å‚Ì•Ó‚ğpush
				if (*line_clone[i][j] - 10 <= to_find_line && *line_clone[i][j] + 10 >= to_find_line) {
					line_stack.push(line_clone[i][j]);
					marged_line[mcount].push_back(line_clone[i][j]);
					to_find_line -= *line_clone[i][j]; //‚Ğ‚­
					stack_deadend[dcount].push_back(line_clone[i][j]);
					flag = 1;
				}
				//‹‚ß‚½‚¢•Ó‚Ì’·‚³‚æ‚è’Z‚¢‚à‚Ì‚ğpush‚½‚¾‚µc‚è‚Ì•Ó‚ªÅ¬‚Ì•Ó‚æ‚è¬‚³‚­‚È‚ç‚È‚¢‚æ‚¤‚É
				else if (*line_clone[i][j] < to_find_line && to_find_line - *line_clone[i][j] >= *line_min) {
					line_stack.push(line_clone[i][j]);
					marged_line[mcount].push_back(line_clone[i][j]);
					to_find_line -= *line_clone[i][j];
					stack_deadend[dcount].push_back(line_clone[i][j]);
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

		//“K‚·‚é•Ó‚ªŒ©‚Â‚©‚Á‚Ä‚¢‚È‚¯‚ê‚Îflag‚Í0‚Ì‚Í‚¸(‚±‚êˆÈãö‚ê‚È‚¢)
		if (flag == 0) {
			//Ÿ‚Ìs‚Ö
			stack_deadend.push_back(vector < shared_ptr<double> > ());
			marged_line.pop_back();
			to_find_line += *line_stack.top(); //‚½‚·
			line_stack.pop(); //‚È‚­‚·
		}

		flag = 0;
		//‹‚ß‚½‚¢•Ó‚Ì’·‚³‚ª10ˆÈ‰º‚¾‚Á‚½‚Æ‚«‚É“š‚¦‚Æ‚İ‚È‚µ‚Äpushback
		if (to_find_line <= 10) {
			marged_line.push_back(vector<shared_ptr<double> >());
			stack_deadend.push_back(vector < shared_ptr<double> >());
			to_find_line += *line_stack.top();
			line_stack.pop();
		}
	}
}
=======
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
				cout << "angle[" << i << "][" << j << "]ã€€ã€€ã€€ã€€ã€€ã€€ã€€ è§’" << *angles[i][j] << "ã§ã™ã€‚" << endl;
				angle_pt.push_back(vector<pair<double, double> >());
				angle_pt[a].push_back(make_pair(i, j));
				a++;
			}
			for (int k = i + 1; k < pieces.size(); k++) {
				for (int g = 0; g < angles[k].size(); g++) {
					if (*angles[i][j] + *angles[k][g] < N + gosa && *angles[i][j] + *angles[k][g] > N - gosa) {
						cout << "angle[" << i << "][" << j << "] & " << "angle[" << k << "][" << g << "] " <<
							"è§’" << *angles[i][j] << "ã¨" << *angles[k][g] << "ãŒã‚»ãƒƒãƒˆã§ã™ã€‚" << endl;
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
	}//å‹•ä½œãƒ†ã‚¹ãƒˆ

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
				cout << "line_length[" << i << "][" << j << "]ã€€ã€€ã€€ã€€ã€€ã€€ã€€ã€€ã€€ è¾º" << *lines[i][j] << "ã§ã™ã€‚" << endl;
				line_pt.push_back(vector<pair<double, double> >());
				line_pt[c].push_back(pair<double, double>(i, j));
				c++;
			}
			for (int k = i + 1; k < pieces.size(); k++) {
				for (int g = 0; g < lines[k].size(); g++) {
					if (*lines[i][j] + *lines[k][g] < M + gosa && *lines[i][j] + *lines[k][g] > M - gosa) {
						cout << "line_length[" << i << "][" << j << "] & " << "line_length[" << k << "][" << g << "] " <<
							"è¾º" << *lines[i][j] << "ã¨" << *lines[k][g] << "ãŒã‚»ãƒƒãƒˆã§ã™ã€‚" << endl;
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
	}//å‹•ä½œãƒ†ã‚¹ãƒˆ

	cv::imshow("hoge", img);
	cv::waitKey(0);
}
>>>>>>> origin/master
