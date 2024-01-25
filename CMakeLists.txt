cmake_minimum_required(VERSION 3.28.1)

project(FDM_AA_CPP)

add_executable(FDM_AA_CPP fdm_aa_cpp.cpp)

add_subdirectory(src/cglib)
add_subdirectory(src/ext/eigen-3.4.0)
target_link_libraries(FDM_AA_CPP cglib Eigen3::Eigen)