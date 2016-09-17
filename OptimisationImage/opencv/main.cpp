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

int main(int argc, char **argv) {

	//cv::Mat img = cv::imread("item/zzz.jpg", 0);
	//cv::Mat color_img = cv::imread("item/zzz.jpg", 1);

	cv::Mat source = cv::imread("item/img1.png");
	cv::Mat alpha_image = cv::Mat(source.size(), CV_8UC3);
	cv::cvtColor(source, alpha_image, CV_RGB2RGBA);
	//cv::imshow("original", source);
	//cv::imshow("image", alpha_image);


	for (int y = 0; y < alpha_image.rows; ++y) {
		for (int x = 0; x < alpha_image.cols; ++x) {
			cv::Vec4b px = alpha_image.at<cv::Vec4b>(y, x);
			if (px[0] + px[1] + px[2] == 255*3) {
				px[3] = 0;
				alpha_image.at<cv::Vec4b>(y, x) = px;
			}
		}
	}
	//cv::imshow("うぇ～～い", img);
	cv::imwrite("imte/new.png", alpha_image);

	

	//cv::imshow("うぇ～い", alpha_image);

	cv::waitKey();
	return 0;
}