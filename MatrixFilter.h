#pragma once

#include "Filter.h"

class MatrixFilter : public Filter {
public:
    void Apply(Image& image) override;

protected:
    virtual Color ApplyMatrix(const Image& image, int x, int y) = 0;
};
