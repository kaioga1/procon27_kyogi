# include "Operator.h"

Operator::Operator() {
	piece_manager = make_shared<PieceManager>();
	gui = make_shared<GUI>();
	images = vector<shared_ptr<cv::Mat> >();
}

void Operator::exec() {
	read_image();
	init_pieces();
}

void Operator::read_image() {
	//読み込んだ画像はimagesにpushしていく
	//images->push_back(ほげほげ);
	//ここぐらいはやってもらわないとこまる割合的に
	for (int i = 1; i <= 10; i++) {
		string str = "item/img";
		str += to_string(i);
		str += ".png";
		images.push_back(shared_ptr<cv::Mat> (new cv::Mat(cv::imread(str, 0))));
	}
}

void Operator::init_pieces() {
	piece_manager->init_pieces(images);
}