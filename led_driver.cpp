#include <iostream>
#include <chrono>
#include <thread>
#include <gpiod.h> // Using the C header that is already verified on disk

int led_driver() {
    unsigned int pin_offset = 17;

    // Open the chip (adjust gpiochip4 to gpiochip0 if necessary)
    struct gpiod_chip *chip = gpiod_chip_open("/dev/gpiochip4");
    if (!chip) {
        std::cerr << "Failed to open GPIO chip." << std::endl;
        return 1;
    }

    // Prepare line configuration
    struct gpiod_line_config *line_cfg = gpiod_line_config_new();
    struct gpiod_line_settings *settings = gpiod_line_settings_new();
    
    gpiod_line_settings_set_direction(settings, GPIOD_LINE_DIRECTION_OUTPUT);
    gpiod_line_config_add_line_settings(line_cfg, &pin_offset, 1, settings);

    // Prepare request
    struct gpiod_request_config *req_cfg = gpiod_request_config_new();
    gpiod_request_config_set_consumer(req_cfg, "resistor_reader_led");

    // Execute request
    struct gpiod_line_request *request = gpiod_chip_request_lines(chip, req_cfg, line_cfg);

    // Clean up temporary config structs
    gpiod_line_settings_free(settings);
    gpiod_line_config_free(line_cfg);
    gpiod_request_config_free(req_cfg);

    if (!request) {
        std::cerr << "Failed to request line." << std::endl;
        gpiod_chip_close(chip);
        return 1;
    }

    std::cout << "Blinking LED on GPIO " << pin_offset << "..." << std::endl;

    for (int i = 0; i < 10; ++i) {
        gpiod_line_request_set_value(request, pin_offset, GPIOD_LINE_VALUE_ACTIVE);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        gpiod_line_request_set_value(request, pin_offset, GPIOD_LINE_VALUE_INACTIVE);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    // Clean up resources
    gpiod_line_request_release(request);
    gpiod_chip_close(chip);

    std::cout << "Done!" << std::endl;
    return 0;
}
