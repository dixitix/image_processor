#pragma once

#include "FormulaFilter.h"

class Grayscale : public FormulaFilter {
public:
    Color ApplyFormula(const Color& c) override;
};
