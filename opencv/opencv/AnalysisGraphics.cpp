# include "AnalysisGraphics.h"


int AnalysisGraphics() {
	//グローバルにあった変数を移動


	cv::Mat im = cv::imread("item/IMGP.jpg", 0);
	cv::Mat color_im = cv::imread("item/IMGP.jpg", 1);
	cv::Mat im_canny, im_sobel, im_laplacian;
	cv::Mat img = cv::Mat::zeros(600, 600, CV_8UC3);



	int j = 0, k = 0, z = 0;
	double root = 0;
	int hoge = 0;
	int line_end = 0;
	double naiseki[50];
	double naiseki_x[50];
	double naiseki_y[50];
	double sen[50];
	double angle[32];
	double pie = 3.141592;

	int line_size;

	//頂点や角、辺の数
	int anscount = 0;


	if (!im.data) {
		return -1;
	}

	Canny(im, im_canny, 50, 200);

	Sobel(im, im_sobel, CV_32F, 1, 1);
	convertScaleAbs(im_sobel, im_sobel, 1, 0);

	Laplacian(im, im_laplacian, CV_32F, 3);
	convertScaleAbs(im_laplacian, im_laplacian, 1, 0);

	//確率的ハフ変換による線分の検出＆描画
	vector<cv::Vec4i> lines;

	HoughLinesP(im_canny, lines, 1, CV_PI / 180, 85, 30, 10);
	for (size_t i = 0; i < lines.size(); i++)
	{
		line(color_im, cv::Point(lines[i][0], lines[i][1]),
			cv::Point(lines[i][2], lines[i][3]), cv::Scalar(0, 0, 255), 2, 8);
	}

	line_size = lines.size();
	//直線の端の座標から頂点を割り出す
	cv::Point ten[50];
	//最終的に出た頂点が格納されています
	cv::Point ans[1600];
	cv::Point zero = 0;
	for (int i = 0; i < lines.size(); i++) {
		for (int j = 0; j < 4; j++) {
			if (j % 2 == 0) {
				ten[k].x = lines[i][j];
				k++;
			}
			else {
				ten[z].y = lines[i][j];
				z++;
			}
		}
	}
	for (line_end = 0; line_end < 1600; line_end++) {
		if (ten[line_end] == zero) {
			break;
		}
	}

	for (int i = 0; i < line_end; i++) {
		circle(color_im, cv::Point(ten[i].x, ten[i].y), 10, cv::Scalar(0, 255, 0), 1, 8);
	}

	measureVertex(anscount, ten, ans, line_end);

	//新しく割り出した頂点の出力
	for (int i = 0; i < anscount; i++) {
		cout << ans[i] << endl;
	}


	measureLine(anscount, ans, root, sen);

	//辺の出力
	for (int i = 0; i < anscount; i++) {
		cout << sen[i] << endl;
	}

	measureAngle(anscount, ans, naiseki, angle, naiseki_x, naiseki_y, sen, pie);

	//角度の出力
	for (int i = 0; i < anscount; i++) {
		cout << angle[i] << endl;
	}

	remakeFigure(anscount, img, ans);

	imshow("original", im);
	imshow("はふ", color_im);
	imshow("再生成", img);

	cv::waitKey(0);

}

//頂点の割り出し
void measureVertex(int &anscount, cv::Point ten[], cv::Point ans[], int line_end) {
	int standard = 0;
	int count = 0;
	anscount = 0;
	for (int j = 0; j < 1600; j++) {
		for (int x = 0; x < line_end; x++) {
			if (ten[standard].x + j >= ten[x].x && ten[standard].x - j <= ten[x].x && ten[standard].y + j >= ten[x].y && ten[standard].y - j <= ten[x].y && ten[standard] != ten[x]) {
				if (j <= 5) {
					ans[anscount] = (ten[standard] + ten[x]) / 2;
					cout << "!";
					anscount++;
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
		if (count == line_end / 2) {
			break;
		}
	}
	for (int i = 0; i < anscount; i++) {
		for (int j = 0; j < anscount - i; j++) {
			if (ans[i] == ans[j] && i != j) {
				ans[j].x = 0;
				ans[j].y = 0;
				anscount = j;
			}
		}
	}
}

//頂点から辺の割り出し
void measureLine(int anscount, cv::Point ans[], double &root, double sen[]) {
	for (int i = 0; i < anscount; i++) {
		if (i == anscount - 1) {
			root = (ans[i].x - ans[0].x)*(ans[i].x - ans[0].x) + (ans[i].y - ans[0].y)*(ans[i].y - ans[0].y);
			sen[i] = sqrt(root);
		}
		else {
			root = (ans[i].x - ans[i + 1].x)*(ans[i].x - ans[i + 1].x) + (ans[i].y - ans[i + 1].y)*(ans[i].y - ans[i + 1].y);
			sen[i] = sqrt(root);
		}
	}
}


void measureAngle(int anscount, cv::Point ans[], double naiseki[], double angle[], double naiseki_x[], double naiseki_y[], double sen[], double pie) {
	double sum = 0;
	int binary[50] = { 0 };
	for (int i = 0; i < anscount; i++) {
		if (i == anscount - 1) {
			naiseki_x[i] = (ans[0].x - ans[i].x) * (ans[0].x - ans[1].x);
			naiseki_y[i] = (ans[0].y - ans[i].y) * (ans[0].y - ans[1].y);
			naiseki[i] = naiseki_x[i] + naiseki_y[i];
			angle[i] = naiseki[i] / (sen[i] * sen[0]);
			angle[i] = acos(angle[i]);
			angle[i] = angle[i] * 180.0 / pie;
		}
		else if (i == anscount - 2) {
			naiseki_x[i] = (ans[i + 1].x - ans[i].x) * (ans[i + 1].x - ans[0].x);
			naiseki_y[i] = (ans[i + 1].y - ans[i].y) * (ans[i + 1].y - ans[0].y);
			naiseki[i] = naiseki_x[i] + naiseki_y[i];
			angle[i] = naiseki[i] / (sen[i] * sen[i + 1]);
			angle[i] = acos(angle[i]);
			angle[i] = angle[i] * 180.0 / pie;
		}
		else {
			naiseki_x[i] = (ans[i + 1].x - ans[i].x) * (ans[i + 1].x - ans[i + 2].x);
			naiseki_y[i] = (ans[i + 1].y - ans[i].y) * (ans[i + 1].y - ans[i + 2].y);
			naiseki[i] = naiseki_x[i] + naiseki_y[i];
			angle[i] = naiseki[i] / (sen[i] * sen[i + 1]);
			angle[i] = acos(angle[i]);
			angle[i] = angle[i] * 180.0 / pie;
		}
	}
	cout << endl;

	int roop = pow(2, anscount);
	for (int i = 0; i < roop; i++) {
		//反転が必要なければbreak。
		if ((anscount - 2) * 180 < sum + 3 && (anscount + 2) * 180 > sum + 3) {
			break;
		}
		//反転のパターンを全部網羅するための処理
		int memory = i;
		for (int j = 0; j < anscount; j++) {
			binary[j] = 0;
		}
		for (int j = anscount - 1; j >= 0; j--) {
			int divison = pow(2, j);
			if (memory / divison >= 1) {
				binary[j] = 1;
				memory = memory - divison;
			}
			cout << binary[j];
		}
		//反転させる処理
		for (int j = 0; j < anscount; j++) {
			if (binary[j] == 1) {
				angle[j] = 360 - angle[j];
			}
		}
		//反転したものをたしあわせる
		sum = 0;
		for (int j = 0; j < anscount; j++) {
			sum = sum + angle[j];
		}
		//反転してそれがあっているか確認する処理。誤差は+-3°。
		if ((anscount - 2) * 180 < sum + 3 && (anscount + 2) * 180 > sum + 3) {
			cout << endl;
			break;
		}
		//違ったとき反転したものを元に戻す
		for (int j = 0; j < anscount; j++) {
			if (binary[j] == 1) {
				angle[j] = 360 - angle[j];
			}
		}
		cout << endl;
	}
}

void remakeFigure(int anscount, cv::Mat &img, cv::Point ans[]) {
	//図形の再形成
	for (int i = 0; i < anscount; i++) {
		if (i != anscount - 1) {
			line(img, cv::Point(ans[i].x, ans[i].y), cv::Point(ans[i + 1].x, ans[i + 1].y), cv::Scalar(0, 0, 255), 3, 8);
		}
		else {
			line(img, cv::Point(ans[i].x, ans[i].y), cv::Point(ans[0].x, ans[0].y), cv::Scalar(0, 0, 255), 3, 8);
		}
	}
}