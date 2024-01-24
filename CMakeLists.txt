cmake_minimum_required(VERSION "3.11")

project("FDM_AA_CPP")

include(FetchContent)
include(CTest)

FetchContent_Declare(
  libsl
  GIT_REPOSITORY https://github.com/sylefeb/LibSL.git
  GIT_TAG        master
)

FetchContent_MakeAvailable(libsl)

add_definitions(-DSRC_PATH=\"${CMAKE_CURRENT_SOURCE_DIR}/\")

add_executable("${PROJECT_NAME}" "main.cpp")
TARGET_LINK_LIBRARIES("${PROJECT_NAME}" LibSL LibSL_gl)

add_executable(GridTest "tests/GridTest.cpp")
TARGET_LINK_LIBRARIES(GridTest LibSL LibSL_gl)

add_executable(EndpointsTest "tests/EndpointsTest.cpp")
TARGET_LINK_LIBRARIES(EndpointsTest LibSL LibSL_gl)

add_test(NAME GridTest COMMAND GridTest)
add_test(NAME EndpointsTest COMMAND EndpointsTest)

install(TARGETS "${PROJECT_NAME}" DESTINATION bin)
install(FILES "main.cpp" DESTINATION src)