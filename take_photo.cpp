#include <cstdlib>
#include <iostream>

void take_photo() {
    // Fix white balance for consistent color reading
    system("v4l2-ctl --device=/dev/video0 --set-ctrl=white_balance_automatic=0");
    system("v4l2-ctl --device=/dev/video0 --set-ctrl=white_balance_temperature=4600");

    // Manual exposure
    system("v4l2-ctl --device=/dev/video0 --set-ctrl=auto_exposure=1");
    system("v4l2-ctl --device=/dev/video0 --set-ctrl=exposure_time_absolute=5000");

    // Fix focus
    system("v4l2-ctl --device=/dev/video0 --set-ctrl=focus_automatic_continuous=0");
    system("v4l2-ctl --device=/dev/video0 --set-ctrl=focus_absolute=68");

    // Capture
    int ret = system("v4l2-ctl --device=/dev/video0 "
                     "--set-fmt-video=width=640,height=480,pixelformat=MJPG "
                     "--stream-mmap --stream-count=1 "
                     "--stream-to=image/image.jpg");

    if (ret != 0) {
        std::cerr << "Error: Could not capture image\n";
        return;
    }
    std::cout << "Image saved\n";
}