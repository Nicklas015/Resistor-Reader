#include <opencv2/opencv.hpp>
#include <iostream>


void take_photo() {
    cv::VideoCapture cap(0);  // 0 = default USB camera

    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open camera\n";
        return;
    }

    cv::Mat frame;

    std::cout << "Press SPACE to capture image\n";

    while (true) {
        cap >> frame;  // capture frame

        if (frame.empty()) {
            std::cerr << "Error: Empty frame\n";
            break;
        }

        //cv::imshow("Camera", frame);

        int key = cv::waitKey(30);

        if (key == 32) {  // SPACE key
            cv::imwrite("image/image.png", frame);
            std::cout << "Image saved to image/image.png\n";
            break;
        }

        if (key == 27) {  // ESC key
            break;
        }
    }

    cap.release();
    //cv::destroyAllWindows();
}