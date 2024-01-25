cmake_minimum_required(VERSION 3.28.1)

project(FDM_AA_CPP)

add_executable(FDM_AA_CPP src/main/fdm_aa_cpp.cpp)

set(LOCAL_LIBRARY_SOURCES src/library/add.cpp src/library/subtract.cpp)

add_library(MyLocalLibrary ${LOCAL_LIBRARY_SOURCES})

target_include_directories(MyLocalLibrary PUBLIC src/library)

target_link_libraries(FDM_AA_CPP MyLocalLibrary)