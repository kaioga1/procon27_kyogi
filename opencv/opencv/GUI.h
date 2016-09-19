#pragma once
# include "Common.h"
# include "Piece.h"
# include "PieceManager.h"

//表示用のクラス
class GUI {
public:
	GUI();
	void draw(vector<shared_ptr<Piece> > pieces, shared_ptr<cv::Mat> frame);

private:
	//土台この上に枠とピースを置いていく的な
	cv::Mat img;
};