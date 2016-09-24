# include "GUI.h"

// グローバル変数
bool lmoving = false;
cv::Point mouse;
vector<shared_ptr<Piece> > pieces;
shared_ptr<Piece> piece = nullptr;
//回転
cv::Point click_point;	//クリックしたところの座標
vector<cv::Point> src_point; //元の座標の配列
bool rmoving = false;

GUI::GUI() {
	img = cv::Mat(cv::Size(960, 540), CV_8UC3, cv::Scalar(100, 100, 100));
}

// コールバック関数
void my_mouse_callback(int event, int x, int y, int flags, void* param) {
	switch (event) {
	case cv::EVENT_MOUSEMOVE:
		if (lmoving) {
			//Mouseの位置ををピースに代入
			piece->adr.x = x;
			piece->adr.y = y;
		}
		else if (rmoving) {
			//回転した値を代入
			cv::Point C;
			double rad = (click_point.y - y)/100.0;
			vector<shared_ptr<cv::Point> > vertex = piece->get_vertex();
			for (int i = 0; i < piece->get_number_of_corner(); i++) {
				C.x = src_point[i].x * cos(rad) - src_point[i].y * sin(rad);
				C.y = src_point[i].x * sin(rad) + src_point[i].y * cos(rad);
				*vertex[i] = C;
			}
		}
		break;
	//左クリックでピースを移動
	case cv::EVENT_LBUTTONDOWN:
		lmoving = true;
		for (int i = 0; i < pieces.size(); i++) {
			//Pieceの画像データを取得
			shared_ptr<cv::Mat> image = pieces[i]->image;
			//Pieceの位置を取得
			cv::Point adr = pieces[i]->adr;
			//クリックした範囲内にあるか判定
			if (x > adr.x && y > adr.y && x < adr.x + image->size().width && y < adr.y + image->size().height) {
				piece = pieces[i];
				break;
			}
			//なければfalse
			if (i == pieces.size() - 1) lmoving = false;
		}
		break;

	case cv::EVENT_LBUTTONUP:
		lmoving = false;
		piece = nullptr;
		break;
	//右クリックで回転を行う
	case cv::EVENT_RBUTTONDOWN:
		//現在の座標を格納
		click_point.x = x;
		click_point.x = y;

		rmoving = true;
		for (int i = 0; i < pieces.size(); i++) {
			shared_ptr<cv::Mat> image = pieces[i]->image;
			cv::Point adr = pieces[i]->adr;
			if (x > adr.x && y > adr.y && x < adr.x + image->size().width && y < adr.y + image->size().height) {
				vector<shared_ptr<cv::Point> > vertex = pieces[i]->get_vertex();
				//変更前のデータを残しておく
				for (int i = 0; i < vertex.size(); i++) {
					src_point.push_back(*vertex[i]);
				}
				piece = pieces[i];
				break;
			}
			if (i == pieces.size() - 1) {rmoving = false;}
		}
		break;
	case cv::EVENT_RBUTTONUP:
		src_point.clear();
		rmoving = false;
		piece = nullptr;
		break;
	}
}

void GUI::draw(vector<shared_ptr<Piece> > pie, shared_ptr<Frame> frame) {
	pieces = pie;
	//前景画像の変形行列

	//クローン
	cv::Mat temp = img.clone();

	// ウィンドウを生成
	cv::namedWindow("GUI", CV_WINDOW_AUTOSIZE);

	// コールバックを設定
	cv::setMouseCallback("GUI", my_mouse_callback, (void *)&img);

	//ピース描画用
	cv::Point app[50];

	// Main loop
	while (1) {
		// imageをtempにコピー
		img.copyTo(temp);

		//Frameの描画
		shared_ptr<cv::Mat> f = frame->image;
		cv::Mat mat = (cv::Mat_<double>(2, 3) << 1.0, 0.0, 100, 0.0, 1.0, 100);
		cv::warpAffine(*f, temp, mat, temp.size(), CV_INTER_LINEAR, cv::BORDER_TRANSPARENT);
		
		//ピースの描画
		for (int i = 0; i < pieces.size(); i++) {
			shared_ptr<Piece> p = pieces[i];
			vector<shared_ptr<cv::Point> > vertex = p->get_vertex();;
			//角の数
			int corner = p->get_number_of_corner();
			//普通の配列じゃないとコンパイラが通らないので
			for (int j = 0; j < corner; j++) {
				app[j] = *vertex[j] + p->adr;
			}
			cv::fillConvexPoly(temp, app, corner, p->color);
			//各線を書き込む
			for (int j = 0; j < corner; j++) {
				if (j != corner - 1) {
					line(temp, cv::Point(vertex[j]->x + p->adr.x, vertex[j]->y + p->adr.y), 
						cv::Point(vertex[j + 1]->x + p->adr.x, vertex[j + 1]->y + p->adr.y), p->color, 1, 8);
				}
				else {
					line(temp, cv::Point(vertex[j]->x + p->adr.x, vertex[j]->y + p->adr.y), 
						cv::Point(vertex[0]->x + p->adr.x, vertex[0]->y + p->adr.y), p->color, 1, 8);
						cv::circle(temp, cv::Point(vertex[j]->x + p->adr.x, vertex[j]->y + p->adr.y), 5, cv::Scalar(0, 200, 0), 1, 8);
				}
	
			}
		}

		cv::imshow("GUI", temp);

		// Escで終了
		if (cv::waitKey(15) == 27)
			break;
	}
}
