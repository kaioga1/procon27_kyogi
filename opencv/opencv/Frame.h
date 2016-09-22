#pragma once

# include "Piece.h"

class Frame : public Piece {
public:
	//特に相違がないので, 今は手を加えていないけど, 必要があれば加えてください
	Frame(shared_ptr<cv::Mat> img, int num);
private:
};