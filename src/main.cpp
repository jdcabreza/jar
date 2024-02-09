#include <iostream>
#include <format>

const int IMAGE_HEIGHT = 256;
const int IMAGE_WIDTH = 256;
const int BLUE_VALUE = 0;

int main() {
    const auto ppm_header = std::format("P3\n{} {}\n255\n", IMAGE_WIDTH, IMAGE_HEIGHT);
    std::cout << ppm_header;

    for (int y = 0; y < IMAGE_HEIGHT; ++y) {
        for (int x = 0; x < IMAGE_WIDTH; ++x) {
            auto r = static_cast<int>(255.999 * (float(x) / (IMAGE_WIDTH - 1)));
            auto g = static_cast<int>(255.999 * (float(y) / (IMAGE_HEIGHT - 1)));

            std::cout << std::format("{} {} {}\n", r, g, BLUE_VALUE);
        }
    }

    return 0;
}
