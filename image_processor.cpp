#include "BMPFile.h"
#include "Controller.h"

int main(int argc, char** argv) {
    if (argc < 3) {
        controller::DisplayHelp();
    } else {
        ParsingResults parsing_results = controller::Parse(argc, argv);

        Image image = bmp_file::Load(parsing_results.input_file);

        auto filters = controller::CreateFilters(parsing_results.filter_definitions);

        for (auto filter : filters) {
            filter->Apply(image);
        }

        bmp_file::Save(parsing_results.output_file, image);

        for (auto filter : filters) {
            delete filter;
        }
    }
}
