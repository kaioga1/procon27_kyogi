#pragma once
# include "Common.h"
# include "Piece.h"
# include "Frame.h"
# include "PieceManager.h"

//表示用のクラス
class GUI {
public:
	GUI();
	//枠の更新を作るときに参考に
	void draw(vector<shared_ptr<Piece> > pieces, shared_ptr<Frame> frame);

private:
	//土台この上に枠とピースを置いていく的な
	cv::Mat img;
};