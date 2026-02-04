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

void get_all_lines(std::vector<line>& lines, cv::Mat img);
void get_lines(std::vector<line>& lines, cv::Mat img, cv::Scalar low, cv::Scalar high, Color color);
void draw_lines(std::vector<line>& lines, cv::Mat background);