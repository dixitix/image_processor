#include "Negative.h"

Color Negative::ApplyFormula(const Color &c) {
    return {.blue = static_cast<uint8_t>(255 - c.blue),
            .green = static_cast<uint8_t>(255 - c.green),
            .red = static_cast<uint8_t>(255 - c.red)};
}
