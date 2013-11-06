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
set(EXECUTABLE_PATH src/simulation/)

#setting C++11 as standard
add_definitions(-std=c++11)

#including directories and adding libraries
include_directories("${PROJECT_SOURCE_DIR}/src/lib/")

add_library(animal ${LIB_TYPE} ${LIBRARY_PATH}/animal.cpp ${LIBRARY_PATH}genome.cpp)
add_library(genome ${LIB_TYPE} ${LIBRARY_PATH}/genome.cpp)

#compiling the simulation
add_executable(simulation.x ${EXECUTABLE_PATH}simulation.cpp)
target_link_libraries(simulation.x genome animal)

