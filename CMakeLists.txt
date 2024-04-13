cmake_minimum_required (VERSION 3.28.0)

project(zpeslib VERSION 1.0.0)

# Thirdparty libraries
add_subdirectory(thirdparty/zlib)

# zpeslib library
add_library(${PROJECT_NAME} STATIC "zpeslib.cpp" "zpeslib.h")
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC zlib)

# Installation of zpeslib
install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_SOURCE_DIR}/out/install/zpeslib/lib)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/zpeslib.h DESTINATION ${CMAKE_SOURCE_DIR}/out/install/zpeslib/include)
install(TARGETS zlib RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/out/install/zpeslib/bin)
