#pragma once
# include "Common.h"

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

	//画像を読み込み
	void read_image();
	//頂点を求める
	void search_vertex();
	//辺を求める
	void search_line();
	//角度を求める
	void search_angle();


private:
	shared_ptr<PieceManager> piece_manager;
	//画像が届き次第プログラムを書くと
	shared_ptr<vector<cv::Mat> > images;
	//GUI用のクラス
	shared_ptr<GUI> gui;
};