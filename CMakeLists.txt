# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.28.1)

# Name of the project
project(FDM_AA_CPP)

# Set the C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add Eigen library located in src/ext/eigen-3.4.0 as a subdirectory
# EXCLUDE_FROM_ALL prevents it from being built by default
add_subdirectory(src/ext/eigen-3.4.0 EXCLUDE_FROM_ALL)

# Add cglib library located in src/cglib as a subdirectory
# EXCLUDE_FROM_ALL prevents it from being built by default
add_subdirectory(src/cglib EXCLUDE_FROM_ALL)

# Define the executable for this project
add_executable(FDM_AA_CPP fdm_aa_cpp.cpp)
add_executable(Cycle_Creator tools/cycle_creator.cpp)
add_executable(Demonstration tools/Demonstration.cpp)
add_executable(Performance_tester tools/Performance_tester.cpp)

# Link Eigen library to the executables
target_link_libraries(FDM_AA_CPP Eigen3::Eigen)
target_link_libraries(Cycle_Creator Eigen3::Eigen)
target_link_libraries(Demonstration Eigen3::Eigen)
target_link_libraries(Performance_tester Eigen3::Eigen)

# Link cglib library to the executables
target_link_libraries(FDM_AA_CPP cglib)
target_link_libraries(Cycle_Creator cglib)
target_link_libraries(Demonstration cglib)
target_link_libraries(Performance_tester cglib)

# Add include directories for cglib
# This line should ideally be in the CMakeLists.txt of cglib
target_include_directories(cglib
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Include FetchContent module to download and build dependencies
include(FetchContent)

# Declare googletest as a content to be fetched
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.10.0.tar.gz
)

# Check if googletest has been fetched, if not, fetch it
FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# Enable testing functionality in CMake
enable_testing()

# Add tests subdirectory which contains test source files
add_subdirectory(tests)