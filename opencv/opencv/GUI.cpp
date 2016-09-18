# include "GUI.h"

GUI::GUI() {
	img = cv::Mat(cv::Size(1000, 1000), CV_8UC3);
}

void GUI::draw(vector<shared_ptr<Piece> > pieces, shared_ptr<cv::Mat> frame) {
	//前景画像の変形行列
	//																								平行移動の量
	cv::Mat mat = (cv::Mat_<double>(2, 3) << 1.0, 0.0, 100, 0.0, 1.0, 100);
	cv::warpAffine(*frame, img, mat, img.size(), CV_INTER_LINEAR, cv::BORDER_TRANSPARENT);

	//白で塗りつぶし
	//cv::rectangle(img, cv::Point(200, 350), cv::Point(300, 450), cv::Scalar(200, 0, 0), -1, CV_AA);
	for (int i = 0; i < pieces.size(); i++) {
		cv::Mat mat = (cv::Mat_<double>(2, 3) << 1.0, 0.0, 100, 0.0, 1.0, 100);
		shared_ptr<cv::Mat> p = pieces[i]->image;
		cv::warpAffine(*p, img, mat, img.size(), CV_INTER_LINEAR, cv::BORDER_TRANSPARENT);
	}

	cv::imshow("GUI", img);
}