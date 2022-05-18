
cmake_minimum_required(VERSION 3.14)
project(dcc012-lab2-sort1)

option(CLASSROOM "Enable classroom build" OFF)
include_directories(${PROJECT_SOURCE_DIR}/siga/include)


enable_testing()
add_subdirectory(siga)
add_subdirectory(tests)

