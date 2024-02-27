cmake_minimum_required(VERSION 3.28.1)

project(cglib)

set(CGLIB_SOURCES 
    grid/cell.cpp
    grid/edge.cpp
    grid/grid.cpp
    cycle.cpp
    math_cglib.cpp
    point_adjacency.cpp
    scalar.cpp
    tree_util.cpp
)

set(CGLIB_HEADERS 
    grid/cell.h
    grid/edge.h
    grid/grid.h
    array.h
    cycle.h
    math_cglib.h
    point_adjacency.h
    scalar.h
    tree_util.h
)

add_library(cglib ${CGLIB_SOURCES})

target_sources(cglib PRIVATE ${CGLIB_HEADERS})

set(Eigen3_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../ext/eigen-3.4.0")

target_include_directories(cglib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${Eigen3_INCLUDE_DIR})

target_include_directories(cglib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})