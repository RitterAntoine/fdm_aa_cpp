cmake_minimum_required(VERSION 3.28.1)

project(FDM_AA_CPP)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Eigen
add_subdirectory(src/ext/eigen-3.4.0 EXCLUDE_FROM_ALL)
add_subdirectory(src/cglib EXCLUDE_FROM_ALL)

add_executable(FDM_AA_CPP fdm_aa_cpp.cpp)

target_link_libraries(FDM_AA_CPP Eigen3::Eigen)
target_link_libraries(FDM_AA_CPP cglib)

# Add Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.10.0.tar.gz
)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# Enable testing functionality
enable_testing()

# Add test subdirectory
add_subdirectory(tests)