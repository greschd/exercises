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
set(EXECUTABLE_PATH simulation/)

# FLAGS
add_definitions(-Wall -std=c++11)

# including directories and adding libraries
include_directories("${PROJECT_SOURCE_DIR}/src/lib/")

add_library(population ${LIB_TYPE} ${LIBRARY_PATH}/population.cpp ${LIBRARY_PATH}/animal.cpp ${LIBRARY_PATH}genome.cpp)
add_library(animal ${LIB_TYPE} ${LIBRARY_PATH}/animal.cpp ${LIBRARY_PATH}genome.cpp)
add_library(genome ${LIB_TYPE} ${LIBRARY_PATH}/genome.cpp)

# compiling the simulation
add_executable(simulation.x ${EXECUTABLE_PATH}simulation.cpp)
target_link_libraries(simulation.x genome animal population)

# plots
add_custom_target(data ALL COMMAND ./simulation.x) # how can I achieve that those are only called when necessary ?
# COMMENT: from the documentation:
# The target has no output file and is ALWAYS CONSIDERED OUT OF DATE even if the commands try to create a file with the name of the target. Use ADD_CUSTOM_COMMAND to generate a file with dependencies.
add_custom_target(plot ALL COMMAND python ../simulation/plot.py)
add_dependencies(data simulation.x)
add_dependencies(plot data)
