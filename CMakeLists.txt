cmake_minimum_required(VERSION 3.28.1)

project(FDM_AA_CPP)

add_executable(FDM_AA_CPP src/main/fdm_aa_cpp.cpp)

add_subdirectory(src/library)

target_link_libraries(FDM_AA_CPP MyLocalLibrary)