#pragma once

#include "Filter.h"

class FormulaFilter : public Filter {
public:
    void Apply(Image& image) override;

protected:
    virtual Color ApplyFormula(const Color& c) = 0;
};
