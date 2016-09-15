# include "Operator.h"

Operator::Operator() {
	piece_manager = make_shared<PieceManager>();
	gui = make_shared<GUI>();
	images = make_shared<vector<cv::Mat> >();
}

void Operator::read_image() {
	//読み込んだ画像はimagesにpushしていく
}

void Operator::search_vertex() {
	//読み込んだ画像を元に頂点を求める

	//こんな感じでピースクラスの配列を取ってこれる
	shared_ptr<vector<Piece> > pieces = piece_manager->get_pieces();

	/*
	ピース単体を取りたいとき
	get_p(num)
	でnum番目のピースを返すような処理をします
	*/


	/*
	ピースクラスの中身を見たい時
	pieces->get_angle()
	で値が取れる
	*/

}

void Operator::search_line() {
	//頂点を元に辺を求める
}

void Operator::search_angle() {
	//頂点と辺から角度を求める
}
