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

//渡したMatデータが透過して帰ってくる
void transmission(cv::Mat &);

//不要な白い部分をカットする
void cut(cv::Mat &);

int main(int argc, char **argv) {

	cv::Mat img = cv::imread("item/zzz.jpg");

	//この関数でimgの白の部分が透過される
	//正確に言うと(255, 255, 255)の部分
	transmission(img);

	cut(img);

	cv::imwrite("item/new.png", img);

	cv::waitKey();
	return 0;
}

void transmission(cv::Mat &source) {
	cv::Mat alpha_image = cv::Mat(source.size(), CV_8UC3);
	cv::cvtColor(source, alpha_image, CV_RGB2RGBA);

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
	source = alpha_image;
	//cv::imshow("aaa", source);
}

void cut(cv::Mat &source) {
	cv::Mat alpha_image = cv::Mat(source.size(), CV_8UC3);
	cv::cvtColor(source, alpha_image, CV_RGB2RGBA);
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

	cv::Mat roi_img(alpha_image, cv::Rect(mi.x, mi.y , (ma.x - mi.x), (ma.y - mi.y)));
	//cv::imshow("bbb", roi_img);
	source = roi_img;
}