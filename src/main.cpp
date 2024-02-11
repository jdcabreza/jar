#include "color.h"
#include "vector3d.h"

#include <iostream>
#include <format>

const int IMAGE_HEIGHT = 256;
const int IMAGE_WIDTH = 256;
const int BLUE_VALUE = 0;

int main() {
    const auto ppm_header = std::format("P3\n{} {}\n255\n", IMAGE_WIDTH, IMAGE_HEIGHT);
    std::cout << ppm_header;

    for (int y = 0; y < IMAGE_HEIGHT; ++y) {
        const auto progress_log = std::format("\rINFO: Scanlines remaining: {} ", (IMAGE_HEIGHT - y));
        std::clog << progress_log << std::flush;

        for (int x = 0; x < IMAGE_WIDTH; ++x) {
            auto pixel_color = Color(
                float(x) / (IMAGE_WIDTH - 1),
                float(y) / (IMAGE_HEIGHT - 1),
                0
            );
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rINFO: Rendering done.";
    return 0;
}
