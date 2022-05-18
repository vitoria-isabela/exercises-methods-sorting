
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/include/config.h) 



file(GLOB source_files src/*.cc include/*.h)
add_library(siga ${source_files})
target_include_directories(siga PUBLIC ${PROJECT_SOURCE_DIR}/include)