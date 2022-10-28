cmake_minimum_required(VERSION 3.17)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(image_processor
        image_processor.cpp
        BMPFile.cpp Controller.cpp filters/Crop.cpp filters/EdgeDetection.cpp filters/FormulaFilter.cpp filters/GaussianBlur.cpp filters/Grayscale.cpp filters/MatrixFilter.cpp filters/Negative.cpp filters/Sharpening.cpp Image.cpp)
