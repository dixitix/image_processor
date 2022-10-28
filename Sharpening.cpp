#include "Sharpening.h"

namespace {

static const std::vector<std::vector<int>> MATRIX = {{0, -1, 0},
                                                     {-1, 5, -1},
                                                     {0, -1, 0}};

}  // namespace

Color Sharpening::ApplyMatrix(const Image& image, int x, int y) {
    int c_blue = 0;
    int c_green = 0;
    int c_red = 0;

    for (int x_diff = -1; x_diff < 2; ++x_diff) {
        for (int y_diff = -1; y_diff < 2; ++y_diff) {
            int cur_x = std::clamp<int>(x + x_diff, 0, image.GetWidth() - 1);
            int cur_y = std::clamp<int>(y + y_diff, 0, image.GetHeight() - 1);

            Color color = image.GetColor(cur_x, cur_y);

            int coefficient = MATRIX[y_diff + 1][x_diff + 1];

            c_red += static_cast<int>(color.red) * coefficient;
            c_blue += static_cast<int>(color.blue) * coefficient;
            c_green += static_cast<int>(color.green) * coefficient;
        }
    }

    return {.blue = static_cast<uint8_t>(std::clamp(c_blue, 0, 255)),
            .green = static_cast<uint8_t>(std::clamp(c_green, 0, 255)),
            .red = static_cast<uint8_t>(std::clamp(c_red, 0, 255))};
}
