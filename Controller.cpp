#include "Controller.h"

#include "filters/Crop.h"
#include "filters/EdgeDetection.h"
#include "filters/GaussianBlur.h"
#include "filters/Grayscale.h"
#include "filters/Negative.h"
#include "filters/Sharpening.h"

#include <iostream>

namespace {

std::string help =
    "Crop (-crop width height), Grayscale (-gs), Negative (-neg), Sharpening (-sharp),"
    "Edge Detection (-edge threshold), Gaussian Blur (-blur sigma)";

Filter* CreateFilter(const std::string& filter_name, const std::vector<std::string>& filter_params) {
    if (filter_name == "-gs") {
        return new Grayscale;
    } else if (filter_name == "-neg") {
        return new Negative;
    } else if (filter_name == "-crop") {
        return new Crop(std::stoi(filter_params[0]), std::stoi(filter_params[1]));
    } else if (filter_name == "-sharp") {
        return new Sharpening;
    } else if (filter_name == "-edge") {
        return new EdgeDetection(std::stod(filter_params[0]));
    } else if (filter_name == "-blur") {
        return new GaussianBlur(std::stod(filter_params[0]));
    } else {
        return new Crop(SIZE_MAX, SIZE_MAX);
    }
}

}  // namespace

std::vector<Filter*> controller::CreateFilters(std::vector<FilterDefinition>& filter_definitions) {
    if (filter_definitions.empty()) {
        filter_definitions.push_back({.name = "-nothing"});
    }

    std::vector<Filter*> filters;

    for (const auto& definition : filter_definitions) {
        filters.push_back(CreateFilter(definition.name, definition.parameters));
    }

    return filters;
}

ParsingResults controller::Parse(int argc, char** argv) {
    std::string input_file = argv[1];
    std::string output_file = argv[2];
    std::vector<FilterDefinition> filter_definitions;

    for (size_t ind = 3; ind < size_t(argc); ++ind) {
        std::string name = argv[ind];
        std::vector<std::string> parameters;

        if (name == "-crop") {
            parameters.push_back(argv[ind + 1]);
            parameters.push_back(argv[ind + 2]);
            ind += 2;
        }

        if (name == "-edge" || name == "-blur") {
            parameters.push_back(argv[ind + 1]);
            ++ind;
        }

        filter_definitions.push_back({.name = name, .parameters = parameters});
    }

    return {.input_file = input_file, .output_file = output_file, .filter_definitions = filter_definitions};
}

void controller::DisplayHelp() {
    std::cout << help;
}
