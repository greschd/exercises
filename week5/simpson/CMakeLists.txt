cmake_minimum_required (VERSION 2.8)
project(simpson)

include_directories("${PROJECT_SOURCE_DIR}/src")
add_executable(simpson.x src/main.cpp src/simpson.cpp)

