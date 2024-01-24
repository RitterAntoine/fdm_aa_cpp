cmake_minimum_required(VERSION "3.11")

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

project("FDM_AA_CPP")

OPTION(FDM_AA_CPP_FLOAT_AS_DOUBLE "Use 64-bit floats" OFF)

if(FDM_AA_CPP_FLOAT_AS_DOUBLE)
    add_definitions(-D FDM_AA_CPP_FLOAT_AS_DOUBLE)
endif()

find_package(Sanitizers)

###########################################################################
# LibSL

set(LIBSL_BUILD_STATIC_LIBS ON CACHE BOOL " " FORCE)
set(LIBSL_BUILD_SHARED_LIBS OFF CACHE BOOL " " FORCE)
add_subdirectory(src/ext/LibSL)

set(LIBSL_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/ext/LibSL")
set(LIBSL_LIBRARY "LibSL")
set_property(TARGET LibSL PROPERTY FOLDER "ext")
include_directories(src/ext/LibSL/src/LibSL)


###########################################################################
# On to the project

set(FDM_AA_CPP_CORE_SOURCE
  src/core/grid/edge.cpp
  src/core/grid/grid.cpp
)

set(FDM_AA_CPP_CORE_HEADERS
  src/core/grid/edge.h
  src/core/grid/grid.h
)

include_directories(src)
include_directories(src/core)

# Visual Studio source forlders

source_group(core REGULAR_EXPRESSION src/core/.*)
source_group(ext REGULAR_EXPRESSION src/ext/.*)

###########################################################################
# fdm_aa_cpp libraries and executables

add_library(fdm_aa_cpp_core STATIC ${FDM_AA_CPP_CORE_SOURCE} ${FDM_AA_CPP_CORE_HEADERS})

if(WIN32)
  set_target_properties(fdm_aa_cpp_core PROPERTIES OUTPUT_NAME "lib_fdm_aa_cpp")
endif()

set(ALL_FDM_AA_CPP_LIBS
  fdm_aa_cpp_core
  LibSL
)


###########################################################################
# Main executable

add_executable(fdm_aa_cpp_exe src/main/fdm_aa_cpp.cpp)

set_target_properties(fdm_aa_cpp_exe PROPERTIES OUTPUT_NAME "fdm_aa_cpp")
target_link_libraries(fdm_aa_cpp_exe ${ALL_FDM_AA_CPP_LIBS})

###########################################################################
# Tests

#TO DO

###########################################################################
# Install

install(TARGETS fdm_aa_cpp_exe DESTINATION bin)

install(TARGETS fdm_aa_cpp_core DESTINATION lib)