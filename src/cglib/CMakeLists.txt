cmake_minimum_required(VERSION 3.28.1)

project(cglib)

set(CGLIB_SOURCES 
    grid/grid.cpp
    grid/edge.cpp
)

add_library(cglib ${CGLIB_SOURCES})

set(Eigen3_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../ext/eigen-3.4.0")

target_include_directories(cglib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${Eigen3_INCLUDE_DIR})

target_include_directories(cglib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})