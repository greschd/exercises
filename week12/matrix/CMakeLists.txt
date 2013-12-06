cmake_minimum_required (VERSION 2.8)
project(matrix)

#Options
option(BUILD_LIB_SHARED "Build the libraries shared." OFF)

if(BUILD_LIB_SHARED)
    set(LIB_TYPE SHARED)
else(BUILD_LIB_SHARED)
    set(LIB_TYPE STATIC)
endif(BUILD_LIB_SHARED)

# setting the library / executables paths
set(LIBRARY_PATH src/lib/)
set(EXECUTABLE_PATH main/)
set(CMAKE_EXE_LINKER_FLAGS)

# FLAGS
add_definitions(-O2 -funroll-loops -std=c++11)

# including directories and adding libraries
include_directories("${PROJECT_SOURCE_DIR}/src/lib/")

# compiling the two versions
add_executable(simple.x ${EXECUTABLE_PATH}simple.cpp)
add_executable(library.x ${EXECUTABLE_PATH}library.cpp)
target_link_libraries(library.x blas)



