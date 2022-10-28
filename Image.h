#pragma once

#include "Color.h"

#include <vector>

using MatrixOfColors = std::vector<std::vector<Color>>;

class Image {
public:
    Image();
    Image(size_t width, size_t height);

    size_t GetHeight() const;
    size_t GetWidth() const;

    Color& GetColor(size_t x, size_t y);
    const Color& GetColor(size_t x, size_t y) const;

private:
    size_t width_;
    size_t height_;

    MatrixOfColors data_;
};
