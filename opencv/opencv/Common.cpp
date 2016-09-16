# include "Common.h"

/*Piece::Piece(int number_of_corner, shared_ptr<vector<double> > line_lengths,
			shared_ptr<vector<cv::Point> > angle, shared_ptr<vector<cv::Point> > vertex) :
	number_of_corner(number_of_corner),
	line_lengths(line_lengths),
	angle(angle), vertex(vertex){
}*/

Piece::Piece(shared_ptr<cv::Mat> image) {
	//imshow("canny", image);
}

void Piece::search_vertex() {
	//読み込んだ画像を元に頂点を求める

	/*
	ピース単体を取りたいとき
	pieces.get()[0];
	とかで取れると思う
	実行してないから動作確認はできてない
	*/


	/*
	ピースクラスの中身を見たい時
	pieces->get_angle()
	で値が取れる
	*/

}

void Piece::search_line() {
	//頂点を元に辺を求める
}

void Piece::search_angle() {
	//頂点と辺から角度を求める
}

PieceManager::PieceManager() {
	pieces = vector<shared_ptr<Piece> >();
}

void PieceManager::init_pieces(vector<shared_ptr<cv::Mat> > images){
	for (int i = 0; i < 10/*images.size()*/; i++) {
		//shared_ptr<cv::Mat> image = images[i];
		//shared_ptr<cv::Mat> image = make_shared<cv::Mat>(cv::imread("item/IMGP.jpg", 0));
		cv::Mat image = cv::Mat::zeros(500, 500, CV_8UC3);
		//cv::Mat image = cv::imread("item/IMGP.jpg", 0);
		cv::line(image, cv::Point(100, 100), cv::Point(i*100, 105), cv::Scalar(0, 0, 200), 3, 4);
		//pieces.push_back(shared_ptr<Piece>(new Piece(image)));
		string str = "a" + (char)('1' + i);
		imshow(str, image);
	}
	cv::waitKey();
}