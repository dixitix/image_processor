#pragma once

#include "../Image.h"

class Filter {
public:
    virtual void Apply(Image& image) = 0;
    virtual ~Filter() = default;
};
