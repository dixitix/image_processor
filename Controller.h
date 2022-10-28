#pragma once

#include "filters/Filter.h"

#include <string>

struct FilterDefinition {
    std::string name;
    std::vector<std::string> parameters;
};

struct ParsingResults {
    std::string input_file;
    std::string output_file;
    std::vector<FilterDefinition> filter_definitions;
};

namespace controller {

ParsingResults Parse(int argc, char** argv);
std::vector<Filter*> CreateFilters(std::vector<FilterDefinition>& filter_definitions);
void DisplayHelp();

}  // namespace controller
