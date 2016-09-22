# include "Operator.h"

Operator::Operator() {
	piece_manager = make_shared<PieceManager>();
	gui = make_shared<GUI>();
	images = vector<shared_ptr<cv::Mat> >();
}

void Operator::exec() {
	read_image();
	init_pieces();

	//GUI(計算結果の表示にも使える)
	gui->draw(piece_manager->get_pieces(), frame);
}

void Operator::read_image() {
	//読み込んだ画像はimagesにpushしていく
	//images->push_back(ほげほげ);
	//ここぐらいはやってもらわないとこまる割合的に
	for (int i = 1; i <= 7; i++) {
		//string str = "new_item/img";
		string str = "item/img (";
		str += to_string(i);
		str += ").png";
		images.push_back(make_shared<cv::Mat> (cv::imread(str, 0)));
	}
	//枠の読み込み
	frame = make_shared<cv::Mat>(cv::imread("item/frame.png", 0));
	threshold(*frame, *frame, 100, 255, CV_THRESH_BINARY);
	cv::imshow("aaa", *frame);
}

void Operator::init_pieces() {
	piece_manager->init_pieces(images);
}