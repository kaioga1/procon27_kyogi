#pragma once
# include "Common.h"

int AnalysisGraphics();
void measureVertex(int &anscount, cv::Point ten[], cv::Point ans[], int line_end);
void measureLine(int anscount, cv::Point vertex[][50], double &root, double sen[][50], int nop);
void measureAngle(int anscount, cv::Point vertex[][50], double naiseki[], double angle[][50], double sen[][50], double pie,int nop);
void remakeFigure(int anscount, cv::Mat &img, cv::Point vertex[]);