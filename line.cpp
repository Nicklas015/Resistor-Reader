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

void get_all_lines(std::vector<line>& lines, cv::Mat img) {
  get_lines(lines, img, YELLOW_RANGE.low, YELLOW_RANGE.high, Color::YELLOW);
  get_lines(lines, img, BLUE_RANGE.low, BLUE_RANGE.high, Color::BLUE);
  get_lines(lines, img, RED_RANGE.low, RED_RANGE.high, Color::RED);
  get_lines(lines, img, GREEN_RANGE.low, GREEN_RANGE.high, Color::GREEN);
  get_lines(lines, img, PURPLE_RANGE.low, PURPLE_RANGE.high, Color::PURPLE);
  get_lines(lines, img, ORANGE_RANGE.low, ORANGE_RANGE.high, Color::ORANGE);
  get_lines(lines, img, BLACK_RANGE.low, BLACK_RANGE.high, Color::BLACK);
  get_lines(lines, img, GOLD_RANGE.low, GOLD_RANGE.high, Color::GOLD);
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