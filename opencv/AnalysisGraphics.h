#pragma once
# include "Common.h"

int AnalysisGraphics();
void measureVertex(int &anscount, cv::Point ten[], cv::Point ans[], int line_end);
void measureLine(int anscount, cv::Point ans[], double &root, double sen[]);
void measureAngle(int anscount, cv::Point ans[], double naiseki[], double angle[], double naiseki_x[], double naiseki_y[], double sen[], double pie);
void remakeFigure(int anscount, cv::Mat &img, cv::Point ans[]);