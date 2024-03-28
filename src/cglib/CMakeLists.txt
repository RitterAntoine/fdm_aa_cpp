cmake_minimum_required(VERSION 3.28.1)

project(cglib)

set(CGLIB_SOURCES 
    grid/cell.cpp
    grid/edge.cpp
    grid/grid.cpp
    cycle.cpp
    math_cglib.cpp
    point_adjacency.cpp
    polyline.cpp
    scalar.cpp
    tree_util.cpp
)

add_library(cglib ${CGLIB_SOURCES})

set(Eigen3_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../ext/eigen-3.4.0")

target_include_directories(cglib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR} 
    ${Eigen3_INCLUDE_DIR}
)