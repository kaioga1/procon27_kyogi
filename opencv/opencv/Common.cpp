# include "Common.h"

Piece::Piece(int number_of_corner) :
	number_of_corner(number_of_corner) {
	line_lengths = make_shared<vector<double> >();
	angle = make_shared<vector<cv::Point> >();
	vertex = make_shared<vector<cv::Point> >();
}