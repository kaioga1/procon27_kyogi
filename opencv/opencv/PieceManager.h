#pragma once

# include "Common.h"

class Piece;


//ピースのマネジャー
/*
使い方
制約などは基本的にPieceと同じ
コチラは複数のピースをまとめるためのクラス
*/
class PieceManager {
public:
	//デフォルトコンストラクタはなしで！
	//PieceManager(shared_ptr<vector<Piece> > pieces): pieces(pieces){}
	PieceManager();

	//アクセサ
	vector<shared_ptr<Piece> > get_pieces() const { return pieces; }
	//num番目のピースを返す(未実装
	//shared_ptr<Piece> get_p(int num) const { return pieces[num]; }

	//ピースの初期化
	void init_pieces(vector<shared_ptr<cv::Mat> > images);
	//当たり判定
	bool hit_judge(cv::Point edge1, cv::Point edge2);
	

private:
	//ピースの配列
	vector<shared_ptr<Piece> > pieces;
};
