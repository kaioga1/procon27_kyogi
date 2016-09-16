# include "AnalysisGraphics.h"


int AnalysisGraphics() {
	cv::Mat im = cv::imread("item/IMGP.jpg", 0);
	cv::Mat color_im = cv::imread("item/IMGP.jpg", 1);
	cv::Mat im_canny, im_sobel, im_laplacian;
	cv::Mat img = cv::Mat::zeros(600, 600, CV_8UC3);



	int j = 0, k = 0, x = 0;
	double root=0;
	int hoge = 0;
	double naiseki[50];
	double angle[32];
	double pie = 3.141592;

	int line_size;

	int anscount;


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
	cv::Point ten[1600];
	cv::Point ans[1600];
	cv::Point zero = 0;
	for (int i = 0; i < lines.size(); i++) {
		for (int j = 0; j < 4; j++) {
			if (j % 2 == 0) {
				ten[k].x = lines[i][j];
				k++;
			}
			else {
				ten[x].y = lines[i][j];
				x++;
			}
		}
	}
	for (int i = 0; i < 1600; i++) {
		if (ten[i] == zero) {
			break;
		}
		cout << ten[i] << endl;
	}
	cout << endl;

	cout << ten[1].x + 1 << endl;

	cout << "mikan" << endl;

	for (int j = 0; j < line_size; j++) {
		circle(color_im, cv::Point(ten[j].x, ten[j].y), 10, cv::Scalar(0, 255, 0), 1, 8);
	}

	measureVertex(anscount, ten, ans, line_size);

	//新しく割り出した頂点の出力
	for (int i = 0; i < anscount; i++) {
		cout << ans[i] << endl;
	}


	measureLine(anscount, ans, root);

	//辺の出力
	for (int i = 0; i < anscount; i++) {
		//cout << sen_t[i] << endl;
	}


	measureAngle(anscount, ans, naiseki, angle);

	//角度の出力
	cout << angle[0] << endl;

	remakeFigure(anscount, img, ans);


	imshow("canny", im_canny);
	imshow("sobel", im_sobel);
	imshow("laplacian", im_laplacian);
	imshow("original", im);
	imshow("はふ", color_im);
	imshow("再生成", img);

	cv::waitKey(0);

}

//頂点の割り出し
void measureVertex(int &anscount, cv::Point ten[], cv::Point ans[], int line_size) {
	int m = 0;
	int count = 0;
	anscount = 0;
	for (int j = 0; j < 1600; j++) {
		for (int x = 0; x < line_size; x++) {
			if (ten[m].x + j >= ten[x].x && ten[m].x - j <= ten[x].x && ten[m].y + j >= ten[x].y && ten[m].y - j <= ten[x].y && ten[m] != ten[x]) {
				if (j <= 5) {
					ans[anscount] = (ten[m] + ten[x]) / 2;
					cout << "!";
					anscount++;
				}
				cout << ten[m] << ten[x] << endl;
				if (x % 2 == 1) {
					m = x - 1;
				}
				else {
					m = x + 1;
				}
				count++;
				j = 0;
				break;
			}
		}
		if (count == line_size / 2 - 1) {
			break;
		}
	}
}

//頂点から辺の割り出し
void measureLine(int anscount, cv::Point ans[], double &root) {
	double sen_t[50];
	for (int i = 0; i < anscount; i++) {
		if (i == anscount - 1) {
			root = (ans[i].x - ans[0].x)*(ans[i].x - ans[0].x) + (ans[i].y - ans[0].y)*(ans[i].y - ans[0].y);
			sen_t[i] = sqrt(root);
		}
		else {
			root = (ans[i].x - ans[i + 1].x)*(ans[i].x - ans[i + 1].x) + (ans[i].y - ans[i + 1].y)*(ans[i].y - ans[i + 1].y);
			sen_t[i] = sqrt(root);
		}
	}
}


void measureAngle(int anscount, cv::Point ans[], double naiseki[], double angle[]){
	//角度の割り出し
	/*for (int i = 0; i < anscount; i++) {
		if (i == anscount - 1) {
			naiseki[i] = (ans[i].x - ans[0].x);
			angle[i] = naiseki[i] / (sen[i] * sen[0]);
			angle[i] = acos(angle[i]);
			angle[i] = angle[i] * 180.0;
		}
		else {
			angle[i] = naiseki[i] / (sen[i] * sen[i + 1]);
			angle[i] = acos(angle[i]);
			angle[i] = angle[i] * 180.0;
		}
	}*/
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