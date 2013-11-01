cmake_minimum_required (VERSION 2.8)
project(penna)

#Options
option(BUILD_LIB_SHARED "Build the libraries shared." ON)

if(BUILD_LIB_SHARED)
    set(LIB_TYPE SHARED)
else(BUILD_LIB_SHARED)
    set(LIB_TYPE STATIC)
endif(BUILD_LIB_SHARED)

# setting the library / executables paths
set(LIBRARY_PATH src/lib/)
set(EXECUTABLE_PATH src/testers/)

#setting C++11 as standard
add_definitions(-std=c++11)

#including directories and adding libraries
include_directories("${PROJECT_SOURCE_DIR}/src/lib/")

add_library(animal ${LIB_TYPE} ${LIBRARY_PATH}/animal.cpp)
add_library(genome ${LIB_TYPE} ${LIBRARY_PATH}/genome.cpp)

#compiling the two testing functions
add_executable(genome_test.x ${EXECUTABLE_PATH}genome_test.cpp)
target_link_libraries(genome_test.x genome)

#~ add_executable(animal_test.x ${EXECUTABLE_PATH}animal_test.cpp)
#~ target_link_libraries(animal_test.x genome animal)

