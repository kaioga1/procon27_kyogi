# include "Piece.h"

Piece::Piece(shared_ptr<cv::Mat> img, int num) {
	image = img;
	number.push_back(num);
	flag = false;
	string str = "a";
	str += (char)('1' + num);
	color = cv::Scalar(rand() & 255, rand() & 255, rand() & 255);

	cut_image();

	//２値化
	threshold(*image, *image, 50, 255, CV_THRESH_BINARY);
	cv::imshow(str, *image);

	//画像の書き込み(確認のためなので特に意味はない
	cv::imwrite("new_item/" + to_string(num + 1) + ".png", *image);

	//頂点の検出
	search_vertex();
	//頂点より辺を求める
	search_line();
	//角度の検出
	search_angle();
}

cv::Point Piece::get_min_vertex() {
	cv::Point mi(10000, 10000);
	for (int i = 0; i < vertex.size(); i++) {
		if (mi.x > vertex[i]->x) {
			mi.x = vertex[i]->x;
		}
		if (mi.y > vertex[i]->y) {
			mi.y = vertex[i]->y;
		}
	}
	return mi;
}

cv::Point Piece::get_max_vertex() {
	cv::Point ma(0, 0);
	for (int i = 0; i < vertex.size(); i++) {
		if (ma.x < vertex[i]->x) {
			ma.x = vertex[i]->x;
		}
		if (ma.y < vertex[i]->y) {
			ma.y = vertex[i]->y;
		}
	}
	return ma;
}

void Piece::search_vertex() {
	//元データ
	cv::Mat src = *image;
	//出力先
	cv::Mat dst = cv::Mat::zeros(src.rows, src.cols, CV_8UC3);
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
	cout << "辺の長さ" << endl;
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
	//画像にアクセス用
	int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};
	int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
	
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
	//角度の総和
	double sum_angle = 0;

	cout << "角度" << endl;
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

		//公式を元にとりあえず角度を求める
		double ang = acos((pow(b, 2.0) + pow(c, 2.0) - pow(a, 2.0))/(2.0 * b * c));
		ang = ang * 180 / CV_PI;

		//凹凸で角度を認識するため
		//凸包か凹包か
		//8近傍の塗られている・塗られていない領域を数える
		int fill = 0, not_fill = 0;
		for (int k = 0; k < 8; k++) {
			int x = A.x + dx[k];
			int y = A.y + dy[k];
			if (x >= 0 && y >= 0 && x < image->cols && y < image->rows) {
				int sum = 0;
				for (int i = 0; i < 3; i++) {
					sum += (*image).at<cv::Vec3b>(y, x)[i];
				}
				if (sum == 0) {
					not_fill++;
				}
				else {
					fill++;
				}
			}
			else {
				//端っこにあった場合は凸包に間違いない
				not_fill += 100;
			}
		}

		//not_fillのほうが大きければ凸包なのでそのまま
		if (fill > not_fill) {
			//塗られてる面積のほうが大きければ
			ang = 360 - ang;
		}
		else if (fill == not_fill) {
			//厄介
			//量が同じだったらアドレスを見る
			//ang = 0;
		}
		sum_angle += ang;
		angle.push_back(make_shared<double>(ang));
		cout << *angle[i] << endl;
	}
	cout << "角度の総和" << endl;
	cout << sum_angle << endl;
	cout << endl;
	
}

// グローバル変数
cv::Rect box;
bool drawing_box = false;
cv::Point start;
cv::Point stop;
cv::Mat frame;

void draw_box(cv::Mat* img, cv::Rect rect) {
	cv::rectangle(*img, cv::Point2d(box.x, box.y), cv::Point2d(box.x + box.width, box.y + box.height),
		cv::Scalar(0xff, 0x00, 0x00));
}

// コールバック関数
void my_mouse_callback(int event, int x, int y, int flags, void* param) {
	cv::Mat* image = static_cast<cv::Mat*>(param);

	switch (event) {
	/*case cv::EVENT_MOUSEMOVE:
		if (drawing_box) {
			box.width = x - box.x;
			box.height = y - box.y;
		}
		break;*/

	case cv::EVENT_LBUTTONDOWN:
		drawing_box = true;
		box = cv::Rect(x, y, 0, 0);
		start.x = x;
		start.y = y;
		cout << "start" << endl;
		cout << start << endl;
		break;

	case cv::EVENT_LBUTTONUP:
		drawing_box = false;
		stop.x = x;
		stop.y = y;
		cout << "stop" << endl;
		cout << stop << endl;
			/*if (box.width < 0) {
				box.x += box.width;
				box.width *= -1;
			}
			if (box.height < 0) {
				box.y += box.height;
				box.height *= -1;
			}
			draw_box(image, box);*/
		cv::Mat cut_img(frame, cv::Rect(start , stop));
		cv::imwrite("new_item/frame.png", cut_img);
			break;
	}
}

void Piece::cut_image() {
	std::string name = "Box Example";
	box = cv::Rect(-1, -1, 0, 0);
	
	/* //灰色の画像を生成
	cv::Mat image(cv::Size(960, 540), CV_8UC3, cv::Scalar(100, 100, 100));*/
	cv::Mat temp = frame.clone();

	frame = cv::imread("item/frame.png", 0);

	// ウィンドウを生成
	cv::namedWindow("name", CV_WINDOW_AUTOSIZE);


	// コールバックを設定
	cv::setMouseCallback("name", my_mouse_callback, (void *)&frame);

	// Main loop
	while (1) {
		// frameをtempにコピー
		frame.copyTo(temp);

		// マウスの左クリックを離すまでの間、矩形を一時的に描画
		/*if (drawing_box) {
			draw_box(&frame, box);
		}*/

		cv::imshow("name",temp);

		// Escで終了
		if (cv::waitKey(15) == 27)
			break;
	}
}