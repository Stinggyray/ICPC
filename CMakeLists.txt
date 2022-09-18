cmake_minimum_required(VERSION 3.23)
project(ICPC)

set(CMAKE_CXX_STANDARD 17)

# Get every cpp file in the src directory
file(GLOB_RECURSE CPPFILES "src/*.cpp")
# for each cpp file found...
foreach(file ${CPPFILES})
    # extract just the file name and extension
    get_filename_component(fname ${file} NAME)
    message(STATUS "Adding target for ${fname}")
    # add target for just that file
    add_executable(run_${fname} ${file})
endforeach()