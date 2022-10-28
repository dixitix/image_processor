#include "BMPFile.h"

#include <cmath>
#include <fstream>

namespace {

static const size_t B = 66;
static const size_t M = 77;

static const size_t NUMBER_OF_BYTES_IN_HEADER = 54;
static const size_t NUMBER_OF_BYTES_IN_DIB_HEADER = 40;

static const size_t NUMBER_OF_BYTES_BEFORE_SHAPE = 18;

static const size_t NUMBER_OF_COLOR_PLANES = 1;
static const size_t NUMBER_OF_BITS_PER_PIXEL = 24;

size_t CalculatePadding(size_t width) {
    return (4 - 3 * width % 4) % 4;
}

namespace reading {

uint8_t ReadByte(std::ifstream &input) {
    uint8_t byte;
    input.read(reinterpret_cast<char*>(&byte), 1);
    return byte;
}

int ReadInt(std::ifstream &input) {
    uint32_t value = 0;

    for (size_t ind = 0; ind < 4; ++ind) {
        value += ReadByte(input) << (ind * 8);
    }

    return value;
}

void SkipNBytes(std::ifstream &input, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        reading::ReadByte(input);
    }
}

std::pair<size_t, size_t> GetShapeByReadingHeader(std::ifstream &input) {
    SkipNBytes(input, NUMBER_OF_BYTES_BEFORE_SHAPE);

    size_t width = ReadInt(input);
    size_t height = ReadInt(input);

    SkipNBytes(input, NUMBER_OF_BYTES_IN_HEADER - NUMBER_OF_BYTES_BEFORE_SHAPE - 8);

    return {width, height};
}

Color ReadColor(std::ifstream &input) {
    return {.blue = ReadByte(input), .green = ReadByte(input), .red = ReadByte(input)};
}

void FillImageWithColors(std::ifstream &input, Image& image) {
    size_t padding = CalculatePadding(image.GetWidth());

    for (size_t y = image.GetHeight(); y >= 1; --y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            image.GetColor(x, y - 1) = ReadColor(input);
        }
        SkipNBytes(input, padding);
    }
}

Image ReadImage(std::ifstream &input, std::pair<size_t, size_t> shape) {
    size_t width = shape.first;
    size_t height = shape.second;

    Image image = Image(width, height);

    FillImageWithColors(input, image);

    return image;
}

}  // namespace reading

namespace writing {

void WriteByte(std::ofstream &output, uint8_t byte) {
    output.write(reinterpret_cast<char*>(&byte), 1);
}

void WriteInt(std::ofstream &output, int32_t value) {
    for (size_t ind = 0; ind < 4; ++ind) {
        WriteByte(output, value % 256);
        value /= 256;
    }
}

void WriteValueInTwoBytes(std::ofstream &output, uint16_t value) {
    WriteByte(output, value % 256);
    WriteByte(output, value / 256);
}

void WriteNZeros(std::ofstream &output, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        WriteByte(output, 0);
    }
}

void WriteShape(std::ofstream &output, uint32_t width, uint32_t height) {
    WriteInt(output, width);
    WriteInt(output, height);
}

void WriteHeader(std::ofstream &output, size_t height, size_t width, size_t padding) {
    WriteByte(output, B);
    WriteByte(output, M);

    size_t bitmap_size = (width * 3 + padding) * height;
    WriteInt(output, NUMBER_OF_BYTES_IN_HEADER + bitmap_size);

    WriteInt(output, 0);

    WriteInt(output, NUMBER_OF_BYTES_IN_HEADER);
    WriteInt(output, NUMBER_OF_BYTES_IN_DIB_HEADER);

    WriteShape(output, width, height);

    WriteValueInTwoBytes(output, NUMBER_OF_COLOR_PLANES);
    WriteValueInTwoBytes(output, NUMBER_OF_BITS_PER_PIXEL);

    WriteNZeros(output, 24);
}

void WriteColor(std::ofstream &output, const Color& c) {
    WriteByte(output, c.blue);
    WriteByte(output, c.green);
    WriteByte(output, c.red);
}

void WriteBitMapData(std::ofstream &output, const Image& image, size_t padding) {
    for (size_t y = image.GetHeight(); y >= 1; --y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            WriteColor(output, image.GetColor(x, y - 1));
        }
        WriteNZeros(output, padding);
    }
}

}  // namespace writing

}  // namespace

Image bmp_file::Load(FileName input_file) {
    std::ifstream input(input_file, std::ios::binary);

    std::pair<size_t, size_t> shape = reading::GetShapeByReadingHeader(input);

    return reading::ReadImage(input, shape);
}

void bmp_file::Save(FileName output_file, const Image& image) {
    std::ofstream output(output_file, std::ios::binary);

    size_t padding = CalculatePadding(image.GetWidth());

    writing::WriteHeader(output, image.GetHeight(), image.GetWidth(), padding);

    writing::WriteBitMapData(output, image, padding);
}
