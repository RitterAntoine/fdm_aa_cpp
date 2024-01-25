set(LOCAL_LIBRARY_SOURCES lib/add.cpp lib/subtract.cpp)

add_library(MyLocalLibrary ${LOCAL_LIBRARY_SOURCES})

target_include_directories(MyLocalLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})