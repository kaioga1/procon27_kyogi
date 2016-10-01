# include "Operator.h"

Operator::Operator() {
	piece_manager = make_shared<PieceManager>();
	gui = make_shared<GUI>();
	images = vector<shared_ptr<cv::Mat> >();
}

void Operator::exec() {
	read_image();
	init_pieces();

	int number_of_corner = frame->get_number_of_corner();
	cout << number_of_corner << endl;
	sertch_line();
	//GUI(計算結果の表示にも使える)
	gui->draw(piece_manager->get_pieces(), frame);
}

void Operator::read_image() {
	//読み込んだ画像はimagesにpushしていく
	//images->push_back(ほげほげ);
	//ここぐらいはやってもらわないとこまる割合的に(結局やった
	for (int i = 1; i <= 7; i++) {
		//string str = "new_item/img";
		string str = "item/img (";
		str += to_string(i);
		str += ").png";
		images.push_back(make_shared<cv::Mat> (cv::imread(str, 0)));
	}

	//枠の読み込み
	frame = make_shared<Frame>(make_shared<cv::Mat> (cv::imread("item/frame.png", 0)), 0);
}

void Operator::init_pieces() {
	piece_manager->init_pieces(images);
}

void Operator::sertch_line() {
	piece_manager->sertch_line(343.013);
}
