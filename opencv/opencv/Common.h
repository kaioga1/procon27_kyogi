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
	/*Piece(int number_of_corner, shared_ptr<vector<double> > line_lengths,
		shared_ptr<vector<cv::Point> > angle, shared_ptr<vector<cv::Point> > vertex);*/
	Piece(shared_ptr<cv::Mat> image);

	//アクセサ
	int get_number_of_corner() const { return number_of_corner; }
	vector<shared_ptr<double> > get_line_lengths() const { return line_lengths; }
	vector<shared_ptr<cv::Point> > get_angle() const { return angle; }
	vector<shared_ptr<cv::Point> > get_vertex() const { return vertex; }
	//必要そうなのでseter
	/*void get_number_of_corner(int num ) { number_of_corner = num; }
	void get_line_lengths(shared_ptr<vector<double> > lengths) { line_lengths = lengths; }
	void get_angle(shared_ptr<vector<cv::Point> > ang) { angle = ang; }
	void get_vertex(shared_ptr<vector<cv::Point> > ver){ vertex = ver; }
	*/

	//頂点を求める
	void search_vertex();
	//辺を求める
	void search_line();
	//角度を求める
	void search_angle();

private:
	//何角形か
	int number_of_corner;
	//辺の長さ(r)
	vector<shared_ptr<double> > line_lengths;
	//角度(θ)
	vector<shared_ptr<cv::Point> > angle;
	//頂点
	vector<shared_ptr<cv::Point> > vertex;
};

//ピースのマネジャー
/*
使い方
制約などは基本的にPieceと同じ
コチラは複数のピースをまとめるためのクラス
*/
class PieceManager {
public:
	//デフォルトコンストラクタはなしで！
	//PieceManager(shared_ptr<vector<Piece> > pieces): pieces(pieces){}
	PieceManager();

	//アクセサ
	vector<shared_ptr<Piece> > get_pieces() const { return pieces; }
	//num番目のピースを返す(未実装
	//shared_ptr<Piece> get_p(int num) const { return pieces[num]; }

	//ピースの初期化
	void init_pieces(vector<shared_ptr<cv::Mat> > images);
	

private:
	//ピースの配列
	vector<shared_ptr<Piece> > pieces;
};