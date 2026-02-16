// main.cpp
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "cluster.h"
#include "color.h"
#include "line.h"
#include "resistor_value.h"
#include "take_photo.h"

std::vector<line> resistor_lines;
std::vector<std::string> band_positions;

int main() {
  take_photo();
  cv::Mat target = cv::imread("image/image.png");
  cv::Mat background;
  target.copyTo(background);

  cv::cvtColor(target, target, cv::COLOR_BGR2HSV);
  cv::rectangle(target, cv::Point(0, 0), cv::Point(640, 30), (0, 0, 0), cv::FILLED);

  get_all_lines(resistor_lines, target);

  bool horizontal = is_horizontal(resistor_lines);

  if (horizontal) {
    resistor_lines = cluster_by_x(resistor_lines, 50);
    std::cout << "is horizontal" << "\n";
  } else {
    resistor_lines = cluster_by_y(resistor_lines, 50);
    std::cout << "is vertical" << "\n";
  }

  bool forward = orientation(resistor_lines, horizontal);
  std::cout << "orientation: " << forward << "\n";

  for (auto &ln : resistor_lines) {
    std::cout << "Band: " << ColorToString(ln.color) << " at X=" << ln.position.x
              << " at Y=" << ln.position.y << "\n";

    band_positions.push_back(ColorToString(ln.color));
  }

  if (!forward) {
    std::reverse(band_positions.begin(), band_positions.end());
  }

  get_resistor_value(band_positions);
  draw_lines(resistor_lines, background);
/*
  cv::imshow("contours", background);

  // Wait until the window is closed
  while (true) {
    int key = cv::waitKey(30);  // wait 30ms for key press

    if (key >= 0 || cv::getWindowProperty("contours", cv::WND_PROP_VISIBLE) < 1) break;
  }

  cv::destroyAllWindows();*/

  return 0;
}