#pragma once

#include "Image.h"

#include <string>

using FileName = std::string;

namespace bmp_file {

Image Load(FileName input_file);
void Save(FileName output_file, const Image& image);

}  // namespace bmp_file
