#include "Crop.h"

Crop::Crop(size_t width, size_t height) : width_(width), height_(height) {}

void Crop::Apply(Image& image) {
    if (image.GetWidth() < width_) {
        width_ = image.GetWidth();
    }
    if (image.GetHeight() < height_) {
        height_ = image.GetHeight();
    }

    Image copy_image = image;
    image = Image(width_, height_);

    for (size_t y = image.GetHeight(); y >= 1; --y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            image.GetColor(x, y - 1) = copy_image.GetColor(x, y - 1);
        }
    }
}
