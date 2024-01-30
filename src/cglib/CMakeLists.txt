cmake_minimum_required(VERSION 3.28.1)

project(cglib)

set(CGLIB_SOURCES 
    src/grid/cell.cpp
    src/grid/edge.cpp
    src/grid/grid.cpp
    src/point_adjacency.cpp
    src/scalar.cpp
)

set(CGLIB_HEADERS 
    src/grid/cell.h
    src/grid/edge.h
    src/grid/grid.h
    src/array.h
    src/point_adjacency.h
    src/scalar.h
)

add_library(cglib ${CGLIB_SOURCES})

target_sources(cglib PRIVATE ${CGLIB_HEADERS})

set(Eigen3_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../ext/eigen-3.4.0")

target_include_directories(cglib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${Eigen3_INCLUDE_DIR})

target_include_directories(cglib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})