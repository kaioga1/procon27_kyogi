# include "Piece.h"


/*Piece::Piece(int number_of_corner, shared_ptr<vector<double> > line_lengths,
			shared_ptr<vector<cv::Point> > angle, shared_ptr<vector<cv::Point> > vertex) :
	number_of_corner(number_of_corner),
	line_lengths(line_lengths),
	angle(angle), vertex(vertex){
}*/

Piece::Piece(shared_ptr<cv::Mat> image, int number) {
		string str = "a";
		str += (char)('1' + number);
		imshow(str, *image);
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