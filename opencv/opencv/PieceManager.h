#pragma once

# include "Common.h"
# include "Piece.h"
# include "Frame.h"

class Piece;


//ピースのマネジャー
/*
使い方
制約などは基本的にPieceと同じ
コチラは複数のピースをまとめるためのクラス
*/
struct com_piece {
	int num_frame_angle;	//frameの角度の番号
	int num_piece;				//ピースの番号
	int num_angle;				//ピースの角度の番号

	void print() {
		cout << num_frame_angle << " " << num_piece <<
			" " << num_angle << endl;
	}
};

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
	void init_pieces(vector<shared_ptr<cv::Mat> > images, shared_ptr<Frame> f);
	//当たり判定
	bool hit_judge(cv::Point edge1, cv::Point edge2);
	//辺と長さの合う辺の割り出し
	void sertch_line(double to_find_line);
	//一番近い角を探す
	void sertch_edge(vector<shared_ptr<double> > frame);
	//枠の更新
	void Frame_update();
	//枠の更新の記録
	void Frame_record();
	//答えの描画
	void answer_draw();
	//辺の組み合わせ検出
	void line_dt(vector<shared_ptr<double> > frame_angle,vector<shared_ptr<double> > frame_line);
	
	void marge_piece();
	
	//アルゴリズム？の実行関数
	void exec_algorithm();
	//角度のサーチ関数
	void search_angle();
	//サーチで見つけたピースを枠にはめる
	void put_image();


private:
	//ピースの配列
	vector<shared_ptr<Piece> > pieces;
	//角度の組み合わせ格納 
	vector<com_piece> combination_angles;
	//フレームクラチュ
	shared_ptr<Frame> frame;
};
