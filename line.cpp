//line.cpp
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include "line.h"

line::line(){
}
 
line::line(Color color, cv::Rect rect, int x, int y){
    this->color = color;
    this->rect = rect;
    this->position = cv::Point(x, y);
}

void get_lines(std::vector<line>& lines, cv::Mat img, cv::Scalar low, cv::Scalar high, Color color) {
  cv::Mat mask;
  cv::inRange(img, low, high, mask);
  std::vector<std::vector<cv::Point> > contours;
  cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

  for (size_t i = 0; i < contours.size(); i++) {
    cv::Rect boundRect = boundingRect(contours[i]);
    if (boundRect.area() > 350) {
      lines.emplace_back(color, boundRect, boundRect.x + boundRect.width / 2,
                         boundRect.y + boundRect.height / 2);
    }
  }
}

void draw_lines(std::vector<line>& lines, cv::Mat background) {
  for (size_t i = 0; i < lines.size(); i++) {
    switch (lines[i].color) {
      case RED:
        rectangle(background, lines[i].rect.tl(), lines[i].rect.br(), CV_RGB(255, 0, 0), 2);
        break;
      case BLUE:
        rectangle(background, lines[i].rect.tl(), lines[i].rect.br(), CV_RGB(0, 0, 255), 2);
        break;
      case GREEN:
        rectangle(background, lines[i].rect.tl(), lines[i].rect.br(), CV_RGB(0, 255, 0), 2);
        break;
      case YELLOW:
        rectangle(background, lines[i].rect.tl(), lines[i].rect.br(), CV_RGB(255, 255, 0), 2);
        break;
      case PURPLE:
        rectangle(background, lines[i].rect.tl(), lines[i].rect.br(), CV_RGB(128, 0, 128), 2);
        break;
      case ORANGE:
        rectangle(background, lines[i].rect.tl(), lines[i].rect.br(), CV_RGB(255, 165, 0), 2);
        break;
      case BLACK:
        rectangle(background, lines[i].rect.tl(), lines[i].rect.br(), CV_RGB(38, 13, 10), 2);
        break;
      case GOLD:
        rectangle(background, lines[i].rect.tl(), lines[i].rect.br(), CV_RGB(38, 13, 10), 2);
        break;
    }
  }
}