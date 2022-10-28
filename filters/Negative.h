#pragma once

#include "FormulaFilter.h"

class Negative : public FormulaFilter {
public:
    Color ApplyFormula(const Color& c) override;
};
