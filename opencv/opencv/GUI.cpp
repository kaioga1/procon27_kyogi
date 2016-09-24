# include "GUI.h"

// グローバル変数
bool moving = false;
cv::Point mouse;
vector<shared_ptr<Piece> > pieces;
shared_ptr<Piece> piece = nullptr;

GUI::GUI() {
	img = cv::Mat(cv::Size(960, 540), CV_8UC3, cv::Scalar(100, 100, 100));
}

// コールバック関数
void my_mouse_callback(int event, int x, int y, int flags, void* param) {
	cv::Mat* image = static_cast<cv::Mat*>(param);

	switch (event) {
	case cv::EVENT_MOUSEMOVE:
		if (moving) {
			//Mouseの位置ををピースに代入
			piece->adr.x = x;
			piece->adr.y = y;
		}
		break;

	case cv::EVENT_LBUTTONDOWN:
		moving = true;
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
			if (i == pieces.size() - 1)	moving = false;
		}
		break;

	case cv::EVENT_LBUTTONUP:
		moving = false;
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
			for (int j = 0; j < corner; j++) {
				if (j != corner - 1) {
					line(temp, cv::Point(vertex[j]->x, vertex[j]->y), cv::Point(vertex[j + 1]->x, vertex[j + 1]->y), p->color, 1, 8);
				}
				else {
					line(temp, cv::Point(vertex[j]->x, vertex[j]->y), cv::Point(vertex[0]->x, vertex[0]->y), p->color, 1, 8);
				}
	
			}
			//shared_ptr<cv::Mat> p = pieces[i]->image;
			//mat = (cv::Mat_<double>(2, 3) << 1.0, 0.0, pieces[i]->adr.x, 0.0, 1.0, pieces[i]->adr.y);
			//cv::warpAffine(*p, temp, mat, temp.size(), CV_INTER_LINEAR, cv::BORDER_TRANSPARENT);
		}

		if (moving) {
		}

		cv::imshow("GUI", temp);

		// Escで終了
		if (cv::waitKey(15) == 27)
			break;
	}


	//cv::imshow("GUI", img);
}
