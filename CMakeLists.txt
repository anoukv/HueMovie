project(avgColors)
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

find_package(OpenCV REQUIRED)
# Project Executable
add_executable (main main.cpp)
target_link_libraries(main ${OpenCV_LIBS})