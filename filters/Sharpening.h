#pragma once

#include "MatrixFilter.h"

class Sharpening : public MatrixFilter {
public:
    Color ApplyMatrix(const Image& image, int x, int y) override;
};
