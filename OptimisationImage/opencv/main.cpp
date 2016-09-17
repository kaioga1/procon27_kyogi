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
 

int main(int argc, char **argv) {

	cv::Mat img = cv::imread("item/zzz.jpg");

	transmission(img);
	
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
			if (px[0] + px[1] + px[2] == 255*3) {
				px[3] = 0;
				alpha_image.at<cv::Vec4b>(y, x) = px;
			}
		}
	}
	cv::imwrite("item/new.png", alpha_image);
}