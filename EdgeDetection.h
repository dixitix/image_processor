#pragma once

#include "MatrixFilter.h"

class EdgeDetection : public MatrixFilter {
public:
    EdgeDetection(double threshold);
    Color ApplyMatrix(const Image& image, int x, int y) override;

private:
    double threshold_;
};
