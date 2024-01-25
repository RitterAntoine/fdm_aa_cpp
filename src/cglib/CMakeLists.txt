set(LOCAL_LIBRARY_SOURCES 
    grid/grid.cpp)

add_library(cglib ${LOCAL_LIBRARY_SOURCES})

target_include_directories(cglib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})