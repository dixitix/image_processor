#pragma once

#include "Filter.h"

class GaussianBlur : public Filter {
public:
    GaussianBlur(double sigma);
    void Apply(Image& image) override;

private:
    double sigma_;
};
