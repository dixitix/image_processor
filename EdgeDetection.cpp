#include "EdgeDetection.h"

#include "Grayscale.h"

#include <cmath>

namespace {

static const std::vector<std::vector<int>> MATRIX = {{0, -1, 0},
                                                     {-1, 4, -1},
                                                     {0, -1, 0}};

}  // namespace

EdgeDetection::EdgeDetection(double threshold) : threshold_(threshold) {}

Color EdgeDetection::ApplyMatrix(const Image& image, int x, int y) {
    Grayscale grayscale_filter;
    grayscale_filter.ApplyFormula(image.GetColor(x, y));
    int c_gray = 0;

    for (int x_diff = -1; x_diff < 2; ++x_diff) {
        for (int y_diff = -1; y_diff < 2; ++y_diff) {
            int cur_x = std::clamp<int>(x + x_diff, 0, image.GetWidth() - 1);
            int cur_y = std::clamp<int>(y + y_diff, 0, image.GetHeight() - 1);

            Color color = image.GetColor(cur_x, cur_y);

            int coefficient = MATRIX[y_diff + 1][x_diff + 1];

            c_gray += static_cast<int>(color.blue) * coefficient;
        }
    }

    if (c_gray > threshold_ * 255) {
        c_gray = 255;
    } else {
        c_gray = 0;
    }

    return {.blue = static_cast<uint8_t>(c_gray),
            .green = static_cast<uint8_t>(c_gray),
            .red = static_cast<uint8_t>(c_gray)};
}
