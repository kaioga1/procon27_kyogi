# include "GUI.h"

// グローバル変数
bool moving = false;

GUI::GUI() {
	img = cv::Mat(cv::Size(960, 540), CV_8UC3, cv::Scalar(100, 100, 100));
}

// コールバック関数
void my_mouse_callback(int event, int x, int y, int flags, void* param) {
	cv::Mat* image = static_cast<cv::Mat*>(param);

	switch (event) {
	case cv::EVENT_MOUSEMOVE:
		if (moving) {
		}
		break;

	case cv::EVENT_LBUTTONDOWN:
		moving = true;
		break;

	case cv::EVENT_LBUTTONUP:
		moving = false;
		break;
	}
}

void GUI::draw(vector<shared_ptr<Piece> > pieces, shared_ptr<cv::Mat> frame) {
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

		//																								平行移動の量
		cv::Mat mat = (cv::Mat_<double>(2, 3) << 1.0, 0.0, 100, 0.0, 1.0, 100);
		cv::warpAffine(*frame, temp, mat, temp.size(), CV_INTER_LINEAR, cv::BORDER_TRANSPARENT);
		
		for (int i = 0; i < pieces.size(); i++) {
			shared_ptr<cv::Mat> p = pieces[i]->image;
			cv::warpAffine(*p, temp, mat, temp.size(), CV_INTER_LINEAR, cv::BORDER_TRANSPARENT);
		}

		cv::imshow("GUI", temp);

		// Escで終了
		if (cv::waitKey(15) == 27)
			break;
	}


	//cv::imshow("GUI", img);
}
