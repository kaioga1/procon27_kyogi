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

	cv::Mat img = cv::imread("item/zzz.jpg", 0);
	cv::Mat color_img = cv::imread("item/zzz.jpg", 1);

	cv::imshow("うぇ～～い", img);

	cv::waitKey();
	return 0;
}