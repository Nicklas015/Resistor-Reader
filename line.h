#pragma once
 
#include "color.h"
#include <opencv2/core/types.hpp>
 
class line
{
public:
    Color color;
    cv::Point position;
    cv::Rect rect;
 
    line();
    line(Color color, cv::Rect rect, int x, int y);
 
};

void Getlines(std::vector<line>& lines, cv::Mat img, cv::Scalar low, cv::Scalar high, Color color);
void drawlines(std::vector<line>& lines, cv::Mat background);