#include "FormulaFilter.h"

void FormulaFilter::Apply(Image& image) {
    Image copy_image = image;

    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            image.GetColor(x, y) = ApplyFormula(copy_image.GetColor(x, y));
        }
    }
}
