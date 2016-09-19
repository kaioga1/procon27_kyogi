# include "Piece.h"


/*Piece::Piece(int number_of_corner, shared_ptr<vector<double> > line_lengths,
			shared_ptr<vector<cv::Point> > angle, shared_ptr<vector<cv::Point> > vertex) :
	number_of_corner(number_of_corner),
	line_lengths(line_lengths),
	angle(angle), vertex(vertex){
}*/

Piece::Piece(shared_ptr<cv::Mat> img, int number) {
	image = img;
	string str = "a";
	str += (char)('1' + number);
	imshow(str, *image);
	search_vertex();
	//search_line();
	cout << endl;
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
	for (apex = 0; apex < 1600; apex++) {
		if (ten[apex] == zero) {
			break;
		}
	}

	for (int i = 0; i < apex; i++) {
		circle(img, cv::Point(ten[i].x, ten[i].y), 10, cv::Scalar(0, 255, 0), 1, 8);
	}
	//新しく割り出した頂点の出力
	/*
	ピース単体を取りたいとき
	pieces.get()[0];
	とかで取れると思う
	実行してないから動作確認はできてない
	*/


	/*
	ピースクラスの中身を見たい時
	pieces->get_angle()
	で値が取れる
	*/
	for (int j = 0; j < 1600; j++) {
		for (int x = 0; x < apex; x++) {
			if (ten[standard].x + j >= ten[x].x && ten[standard].x - j <= ten[x].x && ten[standard].y + j >= ten[x].y && ten[standard].y - j <= ten[x].y && ten[standard] != ten[x]) {
				if (j <= 5) {
					*vertex[number_of_corner] = (ten[standard] + ten[x]) / 2;
					cout << "!";
					number_of_corner++;
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
}

void Piece::search_angle() {
	//頂点と辺から角度を求める
}