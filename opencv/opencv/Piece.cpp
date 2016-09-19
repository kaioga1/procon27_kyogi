# include "Piece.h"


/*Piece::Piece(int number_of_corner, shared_ptr<vector<double> > line_lengths,
			shared_ptr<vector<cv::Point> > angle, shared_ptr<vector<cv::Point> > vertex) :
	number_of_corner(number_of_corner),
	line_lengths(line_lengths),
	angle(angle), vertex(vertex){
}*/

Piece::Piece(shared_ptr<cv::Mat> img, int number) {
	image = img;
	flag = false;
	string str = "a";
	str += (char)('1' + number);

	imshow(str, *image);
	search_vertex();
	search_line();
	search_angle();
	cout << endl;
	//imshow(str, *image);
	adr = cv::Point(10, 10);
}

void Piece::search_vertex() {
	//読み込んだ画像を元に頂点を求める
	//描画用のキャンバスの作成
	cv::Mat img = cv::Mat::zeros(500, 500, CV_8UC3);
	cv::Mat im_canny;

	cv::Point ten[50];
	
	cv::Point zero = 0;

	int a = 0, b = 0;
	int apex = 0;
	int standard = 0;
	int count = 0;
	int counter = 0;
	
	Canny(*image, im_canny, 50, 200);

	vector<cv::Vec4i> lines;

	HoughLinesP(im_canny, lines, 1, CV_PI / 180, 85, 30, 10);

	for (size_t i = 0; i < lines.size(); i++){
		line(img, cv::Point(lines[i][0], lines[i][1]),
			cv::Point(lines[i][2], lines[i][3]), cv::Scalar(0, 0, 255), 2, 8);
	}

	for (int i = 0; i < lines.size(); i++) {
		for (int j = 0; j < 4; j++) {
			if (j % 2 == 0) {
				ten[a].x = lines[i][j];
				a++;
			}
			else {
				ten[b].y = lines[i][j];
				b++;
			}
		}
	}
	for (apex = 0;; apex++) {
		if (ten[apex] == zero) {
			break;
		}
	}
	cout << lines.size() << "," << apex << endl;
	for (int i = 0; i < apex; i++) {
		circle(img, cv::Point(ten[i].x, ten[i].y), 10, cv::Scalar(0, 255, 0), 1, 8);
	}

	for (int j = 0; j < 1600; j++) {
		for (int x = 0; x < apex; x++) {
			if (ten[standard].x + j >= ten[x].x && ten[standard].x - j <= ten[x].x && ten[standard].y + j >= ten[x].y && ten[standard].y - j <= ten[x].y && ten[standard] != ten[x]) {
				if (j <= 5) {
					vertex.push_back(make_shared<cv::Point>((ten[standard] + ten[x]) / 2));
					cout << "!";
					counter++;
				}
				cout << ten[standard] << ten[x] << endl;
				if (x % 2 == 1) {
					standard = x - 1;
				}
				else {
					standard = x + 1;
				}
				count++;
				j = 0;
				break;
			}
		}
		if (count == apex / 2) {
			break;
		}
	}
	number_of_corner = counter;
	for (int i = 0; i < number_of_corner; i++) {
		for (int j = 0; j < number_of_corner - i; j++) {
			if (vertex[i] == vertex[j] && i != j) {
				*vertex[j] = zero;
				number_of_corner = j;
			}
		}
	}
	/*for (int i = 0; i < number_of_corner; i++) {
		cout << *vertex[i] << endl;
	}*/

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