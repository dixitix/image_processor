#include "Grayscale.h"

#include <cmath>

Color Grayscale::ApplyFormula(const Color& c) {
    uint8_t value_of_new_color = std::min<uint8_t>(255, 0.299 * c.red + 0.587 * c.green + 0.114 * c.blue);

    return {.blue = value_of_new_color,
            .green = value_of_new_color,
            .red = value_of_new_color};
}
