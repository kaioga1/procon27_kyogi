# include "Frame.h"

Frame::Frame(shared_ptr<cv::Mat> img, int num) : Piece(img, num) {
	vector<shared_ptr<cv::Point> > vertex = get_vertex();
	//y, x100ずつシフト
	for (int i = 0; i < vertex.size(); i++) {
		*vertex[i] += cv::Point(100, 100);
	}
}