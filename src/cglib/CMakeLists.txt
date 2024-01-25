cmake_minimum_required(VERSION 3.28.1)

project(cglib)

# List all the source files for the cglib library
set(CGLIB_SOURCES 
    grid/grid.cpp
    # Add other source files as needed
)

add_library(cglib ${CGLIB_SOURCES})

# Set the path to the Eigen headers
set(Eigen3_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../ext/eigen-3.4.0")

# Include the Eigen headers in your project
target_include_directories(cglib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${Eigen3_INCLUDE_DIR})

# Add the cglib headers to the include path
target_include_directories(cglib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})