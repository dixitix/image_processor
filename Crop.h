#pragma once

#include "Filter.h"

class Crop : public Filter {
public:
    Crop(size_t width, size_t height);
    void Apply(Image& image) override;

private:
    size_t width_;
    size_t height_;
};
