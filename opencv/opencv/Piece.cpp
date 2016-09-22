# include "Piece.h"


/*Piece::Piece(int number_of_corner, shared_ptr<vector<double> > line_lengths,
			shared_ptr<vector<cv::Point> > angle, shared_ptr<vector<cv::Point> > vertex) :
	number_of_corner(number_of_corner),
	line_lengths(line_lengths),
	angle(angle), vertex(vertex){
}*/

Piece::Piece(shared_ptr<cv::Mat> img, int num) {
	image = img;
	number.push_back(num);
	flag = false;
	string str = "a";
	str += (char)('1' + num);

	//２値化
	threshold(*image, *image, 100, 255, CV_THRESH_BINARY);

	cv::imwrite("new_item/" + to_string(num + 1) + ".png", *image);

	search_vertex();
	imshow(str, *image);

	//search_line();
	//search_angle();
	//imshow(str, *image);
	adr = cv::Point(10, 10);
}

void Piece::search_vertex() {
	// (1)load a specified file as a 3-channel color image
	cv::Mat harris_img = *image;

	// (2)convert to a grayscale image and normalize it
	cv::Mat gray_img = *image;
	//cvtColor(eigen_img, gray_img, CV_BGR2GRAY);
	normalize(gray_img, gray_img, 0, 255, cv::NORM_MINMAX);

	// (3)detect and draw strong corners on the image based on Eigen Value
	vector<cv::Point2f> corners;
	goodFeaturesToTrack(gray_img, corners, 80, 0.01, 5);
	vector<cv::Point2f>::iterator it_corner = corners.begin();
	for (; it_corner != corners.end(); ++it_corner) {
		//circle(eigen_img, cv::Point(it_corner->x, it_corner->y), 1, cv::Scalar(0, 200, 255), -1);
		//circle(eigen_img, cv::Point(it_corner->x, it_corner->y), 8, cv::Scalar(0, 200, 255));
	}

	// (4)detect and draw strong corners on the image using Harris detector
	goodFeaturesToTrack(gray_img, corners, 5, 0.01, 3, cv::Mat(), 3, true);
	it_corner = corners.begin();
	for (; it_corner != corners.end(); ++it_corner) {
		circle(harris_img, cv::Point(it_corner->x, it_corner->y), 1, cv::Scalar(0, 255, 0), -1);
		circle(harris_img, cv::Point(it_corner->x, it_corner->y), 8, cv::Scalar(0, 255, 0));
	}

	// (5)detect corners using high-speed corner detection; FAST
	int threshold = 100;
	bool nonmax = true;
	vector<cv::KeyPoint> keypoints;
	FAST(gray_img, keypoints, threshold, nonmax);
	vector<cv::KeyPoint>::iterator it_kp = keypoints.begin();
	for (; it_kp != keypoints.end(); ++it_kp) {
		//circle(fast_img, cv::Point(it_kp->pt.x, it_kp->pt.y), 1, cv::Scalar(50, 0, 255), -1);
		//circle(fast_img, cv::Point(it_kp->pt.x, it_kp->pt.y), 8, cv::Scalar(50, 0, 255));
	}

	// (6)show destination images, and quit when any key pressed
	//cv::imshow("EigenValue", eigen_img);
	cv::imshow("Harris", harris_img);
	//cv::imshow("Fast", fast_img);
	cv::waitKey(0);

	//srcは入力画像をMatに変換したものを渡すこととする
	/*vector<vector<cv::Point>> squares;
	vector<vector<cv::Point> > contours;// 輪郭情報
	vector<vector<cv::Point> > poly;// ボリゴン情報

											// 輪郭抽出
	cv::findContours(*image, contours, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	*/
	/*
	cv::Mat src = *image;
	cv::Mat dst = cv::Mat::zeros(src.rows, src.cols, CV_8UC3);
	cv::Scalar color(rand() & 255, rand() & 255, rand() & 255);

	vector<vector<cv::Point> > contours;
	vector<cv::Vec4i> hierarchy;
	findContours(src, contours, hierarchy,
		CV_RETR_CCOMP, CV_CHAIN_APPROX_TC89_KCOS);

	//vector<cv::Point> p = contours[1];
	//cv::approxPolyDP(p, approx, 0.1 , true);

	/*for (int i = 0; i < approx.size(); i++) {
		cout << approx[i] << " ";
	}

	for (int i = 0; i < contours.size(); i++) {
		if (contours[i][0].x == 1 || contours[i][0].y == 1) { 
			//外線がなぜが枠とされていたので, 省く
			auto itr = contours[i].begin();
			while (itr != contours[i].end()) {
				itr = contours[i].erase(itr);
			}
			continue; 
		}
		else {
			//必要なのは始点と終点だけなのでその他の途中のデータは消去
			/*auto itr = contours[i].begin();
			while (itr + 1 != contours[i].end()) {
				if (itr != contours[i].begin()) {
					itr = contours[i].erase(itr);
				}
				else {
					itr++;
				}
			}
		}
		for (int j = 0; j < contours[i].size(); j++) {
			cout << contours[i][j] << " ";
		}
	}
	cout << endl;
	//cv::waitKey();

	// トップレベルにあるすべての輪郭を横断し，
	// 各連結成分をランダムな色で描きます．
	int idx = 0;

	drawContours(dst, contours, idx, color, 1, 8, hierarchy);
	*image = dst;*/

	}

void Piece::search_line() {
	//頂点を元に辺を求める
	double root = 0;
	for (int i = 0; i < number_of_corner; i++) {
		if (i == number_of_corner - 1) {
			root = (vertex[i]->x - vertex[0]->x)*(vertex[i]->x - vertex[0]->x) + (vertex[i]->y - vertex[0]->y)*(vertex[i]->y - vertex[0]->y);
			root = sqrt(root);
			line_lengths.push_back(make_shared<double>(root));
		}
		else {
			root = (vertex[i]->x - vertex[i + 1]->x)*(vertex[i]->x - vertex[i + 1]->x) + (vertex[i]->y - vertex[i + 1]->y)*(vertex[i]->y - vertex[i + 1]->y);
			root = sqrt(root);
			line_lengths.push_back(make_shared<double>(root));
		}
	}

	for (int i = 0; i < number_of_corner; i++) {
		cout << *line_lengths[i] << endl;
	}
}

void Piece::search_angle() {
	//vertex[0]->x = 0;
	//頂点と辺から角度を求める
	if (number_of_corner <= 2) {
		cout << "存在しない多角形です" << endl;
	}
	else {
		double sum = 0;
		double naiseki_x = 0;
		double naiseki_y = 0;
		double naiseki = 0;
		double corner = 0;
		double pie = 3.141592;
		int binary[50] = { 0 };
		for (int i = 0; i < number_of_corner; i++) {
			if (i == number_of_corner - 1) {
				if (vertex.size() == 1) {
					break;
				}
				naiseki_x = (vertex[0]->x - vertex[i]->x) * (vertex[0]->x - vertex[1]->x);
				naiseki_y = (vertex[0]->y - vertex[i]->y) * (vertex[0]->y - vertex[1]->y);
				naiseki = naiseki_x + naiseki_y;
				corner = naiseki / (*line_lengths[i] * *line_lengths[0]);
				corner = acos(corner);
				corner = corner * 180.0 / pie;
				angle.push_back(make_shared<double>(corner));
			}
			else if (i == number_of_corner - 2) {
				naiseki_x = (vertex[i + 1]->x - vertex[i]->x) * (vertex[i + 1]->x - vertex[0]->x);
				naiseki_y = (vertex[i + 1]->y - vertex[i]->y) * (vertex[i + 1]->y - vertex[0]->y);
				naiseki = naiseki_x + naiseki_y;
				corner = naiseki / (*line_lengths[i] * *line_lengths[i + 1]);
				corner = acos(corner);
				corner = corner * 180.0 / pie;
				angle.push_back(make_shared<double>(corner));
			}
			else {
				naiseki_x = (vertex[i + 1]->x - vertex[i]->x) * (vertex[i + 1]->x - vertex[i + 2]->x);
				naiseki_y = (vertex[i + 1]->y - vertex[i]->y) * (vertex[i + 1]->y - vertex[i + 2]->y);
				naiseki = naiseki_x + naiseki_y;
				corner = naiseki / (*line_lengths[i] * *line_lengths[i + 1]);
				corner = acos(corner);
				corner = corner * 180.0 / pie;
				angle.push_back(make_shared<double>(corner));
			}
		}
		cout << endl;

		int roop = pow(2, number_of_corner);
		for (int i = 0; i < roop; i++) {
			//反転が必要なければbreak。
			if ((number_of_corner - 2) * 180 < sum + 3 && (number_of_corner + 2) * 180 > sum + 3) {
				break;
			}
			//反転のパターンを全部網羅するための処理
			int memory = i;
			for (int j = 0; j < number_of_corner; j++) {
				binary[j] = 0;
			}
			for (int j = number_of_corner - 1; j >= 0; j--) {
				int divison = pow(2, j);
				if (memory / divison >= 1) {
					binary[j] = 1;
					memory = memory - divison;
				}
				cout << binary[j];
			}
			//反転させる処理
			for (int j = 0; j < number_of_corner; j++) {
				if (binary[j] == 1) {
					*angle[j] = 360 - *angle[j];
				}
			}
			//反転したものをたしあわせる
			sum = 0;
			for (int j = 0; j < number_of_corner; j++) {
				sum = sum + *angle[j];
			}
			//反転してそれがあっているか確認する処理。誤差は+-3°。
			if ((number_of_corner - 2) * 180 < sum + 3 && (number_of_corner + 2) * 180 > sum + 3) {
				cout << endl;
				break;
			}
			//違ったとき反転したものを元に戻す
			for (int j = 0; j < number_of_corner; j++) {
				if (binary[j] == 1) {
					*angle[j] = 360 - *angle[j];
				}
			}
			cout << endl;
		}

		for (int i = 0; i < number_of_corner; i++) {
			if (angle.size() == 0) {
				break;
			}
			double data = *angle[0];
			if (i == number_of_corner - 1) {
				*angle[i] = data;
			}
			else {
				*angle[i] = *angle[i + 1];
			}
		}

		for (int i = 0; i < number_of_corner; i++) {
			cout << *angle[i] << endl;
		}
	}
}