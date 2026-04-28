#include <iostream>
#include <chrono>
#include <thread>
#include <gpiod.h>

unsigned int pin_offset = 17;

struct gpiod_chip *chip = nullptr;
struct gpiod_line_request *request = nullptr;

int led_driver_init() {
    chip = gpiod_chip_open("/dev/gpiochip4");
    if (!chip) {
        std::cerr << "Failed to open GPIO chip." << std::endl;
        return 1;
    }

    struct gpiod_line_config *line_cfg = gpiod_line_config_new();
    struct gpiod_line_settings *settings = gpiod_line_settings_new();
    struct gpiod_request_config *req_cfg = gpiod_request_config_new();

    gpiod_line_settings_set_direction(settings, GPIOD_LINE_DIRECTION_OUTPUT);
    gpiod_line_config_add_line_settings(line_cfg, &pin_offset, 1, settings);
    gpiod_request_config_set_consumer(req_cfg, "resistor_reader_led");

    request = gpiod_chip_request_lines(chip, req_cfg, line_cfg);

    gpiod_line_settings_free(settings);
    gpiod_line_config_free(line_cfg);
    gpiod_request_config_free(req_cfg);

    if (!request) {
        std::cerr << "Failed to request line." << std::endl;
        gpiod_chip_close(chip);
        return 1;
    }

    return 0;
}

int led_status(int status) {
    std::cout << "LED on GPIO " << pin_offset << "... Status: " << status << std::endl;

    gpiod_line_value value = (status != 0) ? GPIOD_LINE_VALUE_ACTIVE : GPIOD_LINE_VALUE_INACTIVE;
    gpiod_line_request_set_value(request, pin_offset, value);

    return 0;
}

/*void led_driver_close() {
    if (request) gpiod_line_request_release(request);
    if (chip) gpiod_chip_close(chip);
}
*/
