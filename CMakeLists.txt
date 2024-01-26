cmake_minimum_required(VERSION 3.28.1)

project(FDM_AA_CPP)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

# Eigen
add_subdirectory(src/ext/eigen-3.4.0)
add_subdirectory(src/cglib)

add_executable(FDM_AA_CPP fdm_aa_cpp.cpp)

target_link_libraries(FDM_AA_CPP Eigen3::Eigen)
target_link_libraries(FDM_AA_CPP cglib)