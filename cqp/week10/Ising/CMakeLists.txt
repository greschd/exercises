cmake_minimum_required (VERSION 2.6)
project(mc_potts)

#=================== compiler & flags ===================
#~ SET(CMAKE_CXX_COMPILER "gcc-4.8" CACHE STRING "the compiler")
SET(CMACRO "")
SET(CMAKE_CXX_FLAGS " -Wall -std=c++11 -O3 -pedantic -fno-tree-vectorize ")
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${CMACRO})

#=================== set paths ===================
set(SRC "${PROJECT_SOURCE_DIR}/src")
set(EXAMPLE "${PROJECT_SOURCE_DIR}/example")

#=================== set options ===================
OPTION(BUILD_EXAMPLE "build all the examples" ON)

#=================== custom stuff ===================
macro(add_default_test)
    set(name ${ARGV0})
    add_test(${name} ${name})
endmacro(add_default_test)

#=================== write config files ===================
configure_file(
    "${SRC}/conf.hpp.in"
    "${SRC}/conf.hpp"
    )
    
configure_file(
    "${SRC}/../addons_python/build_dir.py.in"
    "${SRC}/../addons_python/build_dir.py"
    )
    
#=================== include directories ===================
include_directories("${SRC}")

#=================== added subdirs ===================
#~ add_subdirectory("")

enable_testing()

if(BUILD_EXAMPLE)
    add_subdirectory("examples")
endif(BUILD_EXAMPLE)
