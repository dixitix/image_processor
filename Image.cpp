#include "Image.h"

Image::Image() : Image(0, 0) {}

Image::Image(size_t width, size_t height)
    : width_(width), height_(height), data_(MatrixOfColors(height, std::vector<Color>(width))) {
}

size_t Image::GetHeight() const {
    return height_;
}

size_t Image::GetWidth() const {
    return width_;
}

Color& Image::GetColor(size_t x, size_t y) {
    return data_[y][x];
}

const Color& Image::GetColor(size_t x, size_t y) const {
    return data_.at(y).at(x);
}
