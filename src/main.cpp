#include "color.h"
#include "ray.h"
#include "vector3d.h"

#include <iostream>
#include <format>

// IMAGE --- maybe make an Image class later on?
const float ASPECT_RATIO = 16.0 / 9.0;
const int IMAGE_WIDTH = 400;
const int IMAGE_HEIGHT = static_cast<int>(IMAGE_WIDTH / ASPECT_RATIO);

// CAMERA --- make a Camera class in the future
// NOTE: A viewport is basically the lens through which we see a 3D scene
//       Probably similar to how a camera has sensors behind its lens.
float VIEWPORT_HEIGHT = 2.0;
float VIEWPORT_WIDTH = VIEWPORT_HEIGHT * (static_cast<float>(IMAGE_WIDTH) / IMAGE_HEIGHT);
float FOCAL_LENGTH = 1.0;
auto CAMERA_CENTER = Point3d(0, 0, 0);

// This points from the left of the image to the right
auto VIEWPORT_U = Vector3d(VIEWPORT_WIDTH, 0, 0);

// This points from the top of the image to the bottom
auto VIEWPORT_V = Vector3d(0, -VIEWPORT_HEIGHT, 0);

// A pixel delta is the distance between the centers of each pixel
auto PIXEL_DELTA_U = VIEWPORT_U / IMAGE_WIDTH;
auto PIXEL_DELTA_V = VIEWPORT_V / IMAGE_HEIGHT;

// Our render loop goes from the top left pixel down to the
// bottom right, so we have to find the top left pixel first
auto VIEWPORT_UPPER_LEFT = CAMERA_CENTER 
                            - Vector3d(0, 0, FOCAL_LENGTH)
                            - (VIEWPORT_U / 2)
                            - (VIEWPORT_V / 2);
auto TOP_LEFT_PIXEL = VIEWPORT_UPPER_LEFT + 0.5 * (PIXEL_DELTA_U + PIXEL_DELTA_V);

Color get_ray_color(const Ray& r) {
    Vector3d ray_direction = unit_vector(r.direction());

    // Calculate our alpha for our linear interpolation
    auto a = 0.5 * (ray_direction.y() + 1.0);
    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}

int main() {
    const auto ppm_header = std::format("P3\n{} {}\n255\n", IMAGE_WIDTH, IMAGE_HEIGHT);
    std::cout << ppm_header;

    for (int y = 0; y < IMAGE_HEIGHT; ++y) {
        const auto progress_log = std::format("\rINFO: Scanlines remaining: {} ", (IMAGE_HEIGHT - y));
        std::clog << progress_log << std::flush;

        for (int x = 0; x < IMAGE_WIDTH; ++x) {
            auto pixel_center = TOP_LEFT_PIXEL
                                + (x * PIXEL_DELTA_U)
                                + (y * PIXEL_DELTA_V);
            auto ray_direction = pixel_center - CAMERA_CENTER;

            Ray r(CAMERA_CENTER, ray_direction);
            Color pixel_color = get_ray_color(r);

            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rINFO: Rendering done.";
    return 0;
}
