# include "PieceManager.h"

# include "Piece.h"

PieceManager::PieceManager() {
	pieces = vector<shared_ptr<Piece> >();
}

void PieceManager::init_pieces(vector<shared_ptr<cv::Mat> > images){
	for (int i = 0; i < images.size(); i++) {
		pieces.push_back(shared_ptr<Piece>(new Piece(images[i], i)));
	}
}
