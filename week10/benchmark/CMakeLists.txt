cmake_minimum_required (VERSION 2.8)
project(benchmark)

#Options
option(BUILD_LIB_SHARED "Build the libraries shared." ON)

if(BUILD_LIB_SHARED)
    set(LIB_TYPE SHARED)
else(BUILD_LIB_SHARED)
    set(LIB_TYPE STATIC)
endif(BUILD_LIB_SHARED)

# setting the library / executables paths
set(LIBRARY_PATH src/lib/)
set(EXECUTABLE_PATH main/)

# FLAGS
add_definitions(-Wall -std=c++11)

# including directories and adding libraries
include_directories("${PROJECT_SOURCE_DIR}/src/lib/")

# compiling the simulation
add_executable(benchmark.x ${EXECUTABLE_PATH}benchmark.cpp)

