// main.cpp
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "cluster.h"
#include "color.h"
#include "line.h"
#include "resistor_value.h"

std::vector<line> resistor_lines;
std::vector<std::string> band_positions;

int main() {
  cv::Mat target = cv::imread("image/test6.png");

  cv::Mat background;
  target.copyTo(background);

  cv::cvtColor(target, target, cv::COLOR_BGR2HSV);

  cv::rectangle(target, cv::Point(0, 0), cv::Point(640, 30), (0, 0, 0), cv::FILLED);

  get_lines(resistor_lines, target, YELLOW_RANGE.low, YELLOW_RANGE.high, Color::YELLOW);
  get_lines(resistor_lines, target, BLUE_RANGE.low, BLUE_RANGE.high, Color::BLUE);
  get_lines(resistor_lines, target, RED_RANGE.low, RED_RANGE.high, Color::RED);
  get_lines(resistor_lines, target, GREEN_RANGE.low, GREEN_RANGE.high, Color::GREEN);
  get_lines(resistor_lines, target, PURPLE_RANGE.low, PURPLE_RANGE.high, Color::PURPLE);
  get_lines(resistor_lines, target, ORANGE_RANGE.low, ORANGE_RANGE.high, Color::ORANGE);
  get_lines(resistor_lines, target, BLACK_RANGE.low, BLACK_RANGE.high, Color::BLACK);
  get_lines(resistor_lines, target, GOLD_RANGE.low, GOLD_RANGE.high, Color::GOLD);
  
  bool horizontal = is_horizontal(resistor_lines);
  bool forward = orientation(resistor_lines, horizontal);
  std::cout << "orientation: " << forward << "\n";
 
  if (horizontal) {
    resistor_lines = cluster_by_x(resistor_lines, 50);
    std::cout << "is horizontal" << "\n";
  } else {
    resistor_lines = cluster_by_y(resistor_lines, 50);
    std::cout << "is vertical" << "\n";
  }  

  for (auto &ln : resistor_lines) {
      std::cout << "Band: " << ColorToString(ln.color)
                << " at X=" << ln.position.x
                << " at Y=" << ln.position.y << "\n";

      band_positions.push_back(ColorToString(ln.color));
  }
  
  if (!forward) {
      std::reverse(band_positions.begin(), band_positions.end());
  } 
  
  get_resistor_value(band_positions);

  draw_lines(resistor_lines, background);

  cv::imshow("contours", background);

  // Wait until the window is closed
  while (true) {
    int key = cv::waitKey(30);  // wait 30ms for key press

    if (key >= 0 || cv::getWindowProperty("contours", cv::WND_PROP_VISIBLE) < 1) break;
  }

  cv::destroyAllWindows();

  return 0;
}