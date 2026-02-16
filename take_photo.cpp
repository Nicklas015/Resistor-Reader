#include <opencv2/opencv.hpp>
#include <iostream>

void take_photo() {
    cv::VideoCapture cap(0);

    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open camera\n";
        return;
    }

    cv::Mat frame;
    cap >> frame;

    if (!frame.empty()) {
        cv::imwrite("image/image.png", frame);
        std::cout << "Image saved\n";
    }

    cap.release();
}