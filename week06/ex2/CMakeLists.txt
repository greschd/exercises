cmake_minimum_required (VERSION 2.8)
project(benchmark)

# Options
option(BUILD_LIB_SHARED "Build the libraries shared." ON)

if(BUILD_LIB_SHARED)
    set(LIB_TYPE SHARED)
else(BUILD_LIB_SHARED)
    set(LIB_TYPE STATIC)
endif(BUILD_LIB_SHARED)

# setting the paths where the libraries/executables are
set(LIBRARY_PATH src/libraries/)
set(EXECUTABLE_PATH src/benchmark/)

# Changing the standard to c++11 (necessarily)
add_definitions(-std=c++11)

# including directories and adding libraries
include_directories("${PROJECT_SOURCE_DIR}/src/libraries/")

add_library(timer ${LIB_TYPE} ${LIBRARY_PATH}timer/timer.cpp)
add_library(random ${LIB_TYPE} ${LIBRARY_PATH}random/random.cpp)

# compiling benchmark.x
add_executable(benchmark.x ${EXECUTABLE_PATH}main.cpp)
target_link_libraries(benchmark.x timer random)


