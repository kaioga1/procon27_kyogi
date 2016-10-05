#pragma once

# include "Common.h"
# include "Piece.h"
# include "Frame.h"

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
	PieceManager();
	//ピースの初期化
	void init_pieces(vector<shared_ptr<cv::Mat> > images, shared_ptr<Frame> f);

	//アクセサ
	vector<shared_ptr<Piece> > get_pieces() const { return pieces; }

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
