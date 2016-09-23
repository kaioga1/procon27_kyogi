# include "Piece.h"


/*Piece::Piece(int number_of_corner, shared_ptr<vector<double> > line_lengths,
			shared_ptr<vector<cv::Point> > angle, shared_ptr<vector<cv::Point> > vertex) :
	number_of_corner(number_of_corner),
	line_lengths(line_lengths),
	angle(angle), vertex(vertex){
}*/

Piece::Piece(shared_ptr<cv::Mat> img, int num) {
	image = img;
	number.push_back(num);
	flag = false;
	string str = "a";
	str += (char)('1' + num);

	//２値化
	threshold(*image, *image, 90, 255, CV_THRESH_BINARY);

	//画像の書き込み(確認のためなので特に意味はない
	cv::imwrite("new_item/" + to_string(num + 1) + ".png", *image);

	//頂点の検出
	search_vertex();
	//頂点より辺を求める
	search_line();
	imshow(str, *image);

	search_angle();
	//imshow(str, *image);
	adr = cv::Point(10, 10);
}

void Piece::search_vertex() {
	//元データ
	cv::Mat src = *image;
	//出力先
	cv::Mat dst = cv::Mat::zeros(src.rows, src.cols, CV_8UC3);
	//色の指定(特に意味はない，きれいだから？
	cv::Scalar color(rand() & 255, rand() & 255, rand() & 255);
	//近似データ
	std::vector< cv::Point > approx;
	//輪郭のアドレスを格納
	vector<vector<cv::Point> > contours;
	//図に書き込み用(普通の配列でないとコンパイラが通らないので
	cv::Point app[50];


	//２値化のみ(情報量少なめ)
	//findContours(src, contours, hierarchy,
		//CV_RETR_CCOMP, CV_CHAIN_APPROX_TC89_KCOS);
	//情報量を拡大
	cv::findContours(src, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

	//輪郭を直線近似する
	cv::approxPolyDP(contours[0], approx, 0.01 * cv::arcLength(contours[0], true), true);


	// 各連結成分をランダムな色で描きます．
	//drawContours(dst, contours, 0, color, 1, 8);
	//メンバ変数に代入
	*image = dst;

	//コマンドプロンプトへ出力＆vertexに代入&画面にかきこみ
	for (int i = 0; i < approx.size(); i++) {
		//判定の邪魔なのでコメントアウト
		//cv::circle(*image, approx[i], 5, cv::Scalar(0, 200, 0), 1, 8);
		vertex.push_back(make_shared<cv::Point>(approx[i]));
		app[i] = approx[i];
		cout << *vertex[i] << " ";
	}

	cv::fillConvexPoly(*image, app, approx.size(), color);
	number_of_corner = vertex.size();
	cout << endl << endl;
}

void Piece::search_line() {
	//頂点を元に辺を求める
	double ang;
	for (int i = 0; i < number_of_corner; i++) {
		if (i == number_of_corner - 1) {
			//二乗するから正負関係なしやで
			ang = sqrt(pow(vertex[i]->x - vertex[0]->x, 2.0) + pow(vertex[i]->y - vertex[0]->y, 2.0));
			line_lengths.push_back(make_shared<double>(ang));
		}
		else {
			ang = sqrt(pow(vertex[i]->x - vertex[i+1]->x, 2.0) + pow(vertex[i]->y - vertex[i+1]->y, 2.0));
			line_lengths.push_back(make_shared<double>(ang));
		}
	}

	for (int i = 0; i < number_of_corner; i++) {
		cout << *line_lengths[i] << endl;
	}
	cout << endl;
}

void Piece::search_angle() {
	if (number_of_corner <= 2) {
		exit(-1);
	}
	//頂点と辺から角度を求める
	/*
	Aが求めたい角度
	a^2 = b^2 + c^2 -2cosθ
	θ = 1/2{(b^2 + c^2) - a^2}
	という公式を使ってみる
	http://www.geisya.or.jp/~mwm48961/kou2/cos_rule.htm
	*/
	//辺a, b, c
	double a, b, c;
	//頂点A, B, C
	cv::Point A, B, C;
	for (int i = 0; i < vertex.size(); i++) {
		//三角形の頂点と辺の長さを割り出す
		A = *vertex[i];
		if (i == vertex.size() - 1) {
			//最後
			b = *line_lengths[i];
			c = *line_lengths[i-1];
			B = *vertex[i-1];
			C = *vertex[0];
		}
		else if (i == 0) {
			//最初
			b = *line_lengths[i];
			c = *line_lengths[vertex.size() - 1];
			B = *vertex[vertex.size() - 1];
			C = *vertex[i+1];
		}
		else {
			//その他他他他
			b = *line_lengths[i];
			c = *line_lengths[i - 1];
			B = *vertex[i - 1];
			C = *vertex[i+1];
		}
		a = sqrt(pow(B.x - C.x, 2.0) + pow(B.y - C.y, 2.0));

		double ang = acos((pow(b, 2.0) + pow(c, 2.0) - pow(a, 2.0))/(2.0 * b * c));
		angle.push_back(make_shared<double>(ang * 180 / CV_PI));
		cout << *angle[i] << endl;
	}
	cout << endl;
	
}