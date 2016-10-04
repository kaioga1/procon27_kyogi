# include "PieceManager.h"


PieceManager::PieceManager() {
	pieces = vector<shared_ptr<Piece> >();
}

void PieceManager::init_pieces(vector<shared_ptr<cv::Mat> > images, shared_ptr<Frame> f){
	for (int i = 0; i < images.size(); i++) {
		pieces.push_back(make_shared<Piece>(Piece(images[i], i)));
	}
	frame = f;
}

void PieceManager::exec_algorithm() {
	search_angle();
}


void PieceManager::search_angle() {
	//フレームの角度
	vector<shared_ptr<double> > frame_angles = frame->get_angle();

	for (int i = 0; i < frame_angles.size(); i++) {
		combination_angles.push_back(vector<int>());
		for (int j = 0; j < pieces.size(); j++) {
			//ピース一つの角度
			vector<shared_ptr<double> > angles = pieces[j]->get_angle();
			for (int k = 0; k < angles.size(); k++) {
				int p_ang = (int)(*angles[j]);
				int f_ang = (int)(*frame_angles[k]);
				if (abs(p_ang - f_ang) <= 2) {
					combination_angles[i].push_back(k);
					cout << i << " " << j << " " << k;
				}
			}
			cout << endl;
		}
		cout << endl;
	}
	cout << endl;
}