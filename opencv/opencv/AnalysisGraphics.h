#pragma once
# include "Common.h"

int AnalysisGraphics();
void measureVertex(int &anscount, cv::Point ten[], cv::Point ans[], int line_size);
void measureLine(int anscount, cv::Point ans[], double &root);
void measureAngle(int anscount, cv::Point ans[], double naiseki[], double angle[]);
void remakeFigure(int anscount, cv::Mat &img, cv::Point ans[]);