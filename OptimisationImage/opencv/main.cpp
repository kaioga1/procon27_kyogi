﻿//opencv
# include "opencv2\opencv.hpp"
# include <opencv2/core/core.hpp>
# include <opencv2/highgui/highgui.hpp>
# include <opencv2/imgproc/imgproc.hpp>
# include <opencv/cvaux.h>
# include <opencv2/imgproc/imgproc.hpp>


//C++
# include <iostream>
# include <cmath>
# include <algorithm>
# include <list>
# include <queue>
# include <vector>
# include <memory>

//２値化かかか
void binarization(cv::Mat &);

//渡したMatデータが透過して帰ってくる
void transmission(cv::Mat &);

//不要な白い部分をカットする
void cut(cv::Mat &);

int main(int argc, char **argv) {
	int N;
	//ピースの数を入力
	std::cin >> N;

	for (int i = 0; i < N; i++) {
		std::string str = "item/img (";
		str += (char)(i + '1');
		str += ").png";
		cv::Mat img = cv::imread(str);

		//この関数でimgの白の部分が透過される
		//正確に言うと(255, 255, 255)の部分

		binarization(img);

		cv::imshow(str, img);

		transmission(img);

		cut(img);

		std::string st = "new_item/img";
		st += (char)(i + '1');
		st += ".png";
		cv::imwrite(st, img);
	}

	//枠
	cv::Mat img = cv::imread("item/frame.png");
	binarization(img);
	transmission(img);
	cut(img);
	cv::imwrite("new_item/frame.png", img);

	cv::waitKey();
	return 0;
}

void binarization(cv::Mat& src_img) {
	//グレースケールから２値化を行う
	cv::Mat gray_img;
	cvtColor(src_img, gray_img, CV_BGR2GRAY);

	//大津(白黒の割合を1;1になるようにしてるらしい)
	//threshold(gray_img, gray_img, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);

	//100がしきい値
	threshold(gray_img, gray_img, 100, 255, CV_THRESH_BINARY);
	//adaptiveThreshold(gray_img, gray_img, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 7, 8);

	src_img = gray_img;
}

void transmission(cv::Mat &src_img) {
	cv::Mat alpha_image = cv::Mat(src_img.size(), CV_8UC3);
	//一回カラーに直さないといけないっぽい
	cv::cvtColor(src_img, src_img, CV_GRAY2RGBA);
	cv::cvtColor(src_img, alpha_image, CV_RGB2RGBA);

	//透過処理
	for (int y = 0; y < alpha_image.rows; ++y) {
		for (int x = 0; x < alpha_image.cols; ++x) {
			cv::Vec4b px = alpha_image.at<cv::Vec4b>(y, x);
			if (px[0] + px[1] + px[2] == 255 * 3) {
				px[3] = 0;
				alpha_image.at<cv::Vec4b>(y, x) = px;
			}
		}
	}
	src_img = alpha_image;
	//cv::imshow("aaa", src_img_img);
}

void cut(cv::Mat &src_img) {
	cv::Mat alpha_image = cv::Mat(src_img.size(), CV_8UC3);
	cv::cvtColor(src_img, alpha_image, CV_RGB2RGBA);
	//maxとmin初期化
	cv::Point ma, mi;
	mi = cv::Point(1000, 1000);
	ma = cv::Point(0, 0);

	for (int y = 0; y < alpha_image.rows; ++y) {
		for (int x = 0; x < alpha_image.cols; ++x) {
			cv::Vec4b px = alpha_image.at<cv::Vec4b>(y, x);
			//黒だったら
			if (px[0] + px[1] + px[2] == 0) {
				mi.x = std::min(mi.x, x);
				mi.y = std::min(mi.y, y);
				ma.x = std::max(ma.x, x);
				ma.y = std::max(ma.y, y);
			}
		}
	}

	cv::Mat roi_img(alpha_image, cv::Rect(mi.x, mi.y, (ma.x - mi.x), (ma.y - mi.y)));
	//cv::imshow("bbb", roi_img);
	src_img = roi_img;
}