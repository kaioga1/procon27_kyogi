#pragma once

//opencv
# include "opencv2\opencv.hpp"
# include <opencv2/core/core.hpp>
# include <opencv2/highgui/highgui.hpp>
# include <opencv2/imgproc/imgproc.hpp>
# include <opencv/cvaux.h>

//C++
# include <iostream>
# include <cmath>
# include <algorithm>
# include <list>
# include <queue>
# include <vector>
# include <memory>

/*
どれがopencvの関数なのかわからなくなるので, 
cvの名前空間は今回はなしにしましょう
*/
//using namespace cv;
using namespace std;




//一つのピースのクラス
/*
使い方
直接変数はいじれないようにしています。
値は変更する方法は初期化の時に与える時だけ
もしその他に必要な時があれば教えて下さい。対応します

値を見たい場合にはアクセサのgetの関数を使って行ってください。
*/
class Piece {
public:
	//デフォルトコンストラクタはなしで！
	Piece(int number_of_corner, shared_ptr<vector<double> > line_lengths,
		shared_ptr<vector<cv::Point> > angle, shared_ptr<vector<cv::Point> > vertex);

	//アクセサ
	int get_number_of_corner() const { return number_of_corner; }
	shared_ptr<vector<double> > get_line_lengths() const { return line_lengths; }
	shared_ptr<vector<cv::Point> > get_angle() const { return angle; }
	shared_ptr<vector<cv::Point> > get_vertex() const { return vertex; }

private:
	//何角形か
	int number_of_corner;
	//辺の長さ(r)
	shared_ptr<vector<double> > line_lengths;
	//角度(θ)
	shared_ptr<vector<cv::Point> > angle;
	//頂点
	shared_ptr<vector<cv::Point> > vertex;
};