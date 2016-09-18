#pragma once
# include "Common.h"
# include "PieceManager.h"
# include "GUI.h"

class GUI;
class Piece;

/*
全体を操作するクラス
これがメインのクラスになる(はず
変数や関数を足したりする分には構わないが, ココにおくかよく考えてからおく
pieceに置いたほうがいいものはゴニョゴニョしてpieceに置く
すぐに必要なくなるようなものであれば関数ないだけで完結させること
*/
class Operator {
public:
	//クォンストラクタ(ふざけた
	Operator();

	void exec();

	//画像を読み込み
	void read_image();

	//頂点・辺・角を求める
	void init_pieces();

private:
	shared_ptr<PieceManager> piece_manager;
	//画像が届き次第プログラムを書くと
	vector<shared_ptr<cv::Mat> > images;
	//枠
	shared_ptr<cv::Mat> frame;
	//GUI用のクラス
	shared_ptr<GUI> gui;
};