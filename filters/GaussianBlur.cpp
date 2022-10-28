#include "GaussianBlur.h"

#include <cmath>

namespace {

double CalculateGaussConstant(int x_diff, int y_diff, double sigma) {
    double coefficient = std::sqrt(sigma * sigma * 2 * M_PI);
    double degree = -1 * (x_diff * x_diff + y_diff * y_diff) / (2 * sigma * sigma);
    return exp(degree) / coefficient;
}

Color SumInHorizontalDirection(const Image &image, int x, int y, double sigma) {
    double c_blue = 0;
    double c_green = 0;
    double c_red = 0;

    for (int x_new = 0; x_new < image.GetWidth(); ++x_new) {
        if (std::abs(x - x_new) <= 3 * sigma) {
            double gauss_const = CalculateGaussConstant(0, std::abs(x - x_new), sigma);

            c_blue += gauss_const * image.GetColor(x_new, y).blue;
            c_green += gauss_const * image.GetColor(x_new, y).green;
            c_red += gauss_const * image.GetColor(x_new, y).red;
        }
    }

    return {.blue = static_cast<uint8_t>(std::clamp(c_blue, 0.0, 255.0)),
            .green = static_cast<uint8_t>(std::clamp(c_green, 0.0, 255.0)),
            .red = static_cast<uint8_t>(std::clamp(c_red, 0.0, 255.0))};
}

Color SumInVerticalDirection(const Image &image, int x, int y, double sigma) {
    double c_blue = 0;
    double c_green = 0;
    double c_red = 0;

    for (int y_new = 0; y_new < image.GetHeight(); ++y_new) {
        if (std::abs(y - y_new) <= 3 * sigma) {
            double gauss_constant = CalculateGaussConstant(std::abs(y - y_new), 0, sigma);

            c_blue += gauss_constant * image.GetColor(x, y_new).blue;
            c_green += gauss_constant * image.GetColor(x, y_new).green;
            c_red += gauss_constant * image.GetColor(x, y_new).red;
        }
    }

    return {.blue = static_cast<uint8_t>(std::clamp(c_blue, 0.0, 255.0)),
            .green = static_cast<uint8_t>(std::clamp(c_green, 0.0, 255.0)),
            .red = static_cast<uint8_t>(std::clamp(c_red, 0.0, 255.0))};
}

}  // namespace

GaussianBlur::GaussianBlur(double sigma) : sigma_(sigma) {}

void GaussianBlur::Apply(Image &image) {
    for (size_t x = 0; x < image.GetHeight(); ++x) {
        for (size_t y = 0; y < image.GetWidth(); ++y) {
            image.GetColor(x, y) = SumInHorizontalDirection(image, x, y, sigma_);
        }
    }

    Image copy_image = image;
    for (size_t x = 0; x < image.GetHeight(); ++x) {
        for (size_t y = 0; y < image.GetWidth(); ++y) {
            image.GetColor(x, y) = SumInVerticalDirection(copy_image, x, y, sigma_);
        }
    }
}
