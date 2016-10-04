#pragma once

# include "Common.h"
# include "Piece.h"
# include "Frame.h"


class PieceManager {
public:
	//デフォルトコンストラクタはなしで！
	PieceManager();
	//ピースの初期化
	void init_pieces(vector<shared_ptr<cv::Mat> > images, shared_ptr<Frame> f);

	//アクセサ
	vector<shared_ptr<Piece> > get_pieces() const { return pieces; }

	//アルゴリズム？の実行関数
	void exec_algorithm();
	//角度のサーチ関数
	void search_angle();
private:
	//ピースの配列
	vector<shared_ptr<Piece> > pieces;
	//角度の組み合わせ格納 [フレームの角度の番号][ピースの番号] = ピースの角度の番号
	vector<vector<int> > combination_angles;
	//フレームクラチュ
	shared_ptr<Frame> frame;
};
