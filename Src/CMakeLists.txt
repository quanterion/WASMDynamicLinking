cmake_minimum_required(VERSION 3.22)

project(WASMDynamicLinking)

add_definitions(-std=c++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_DIR "../Build")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIR})

set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS TRUE)
add_library(calc SHARED ../Src/calc.cpp)

set_target_properties(calc PROPERTIES SUFFIX ".so")
set_target_properties(calc PROPERTIES COMPILE_FLAGS "-sSHARED_MEMORY=1 -Wno-experimental")
set_target_properties(calc PROPERTIES LINK_FLAGS "-sSIDE_MODULE=1 -sMAIN_MODULE=0 -sEXPORT_ALL=1 -sPROXY_TO_PTHREAD -pthread")


add_executable(main ../Src/main.cpp)
set_target_properties(main PROPERTIES SUFFIX ".html")
set_target_properties(main PROPERTIES COMPILE_FLAGS "-sMAIN_MODULE=2 -sSHARED_MEMORY=1 -Wno-experimental")
set_target_properties(main PROPERTIES LINK_FLAGS "-sMAIN_MODULE=2 -sAUTOLOAD_DYLIBS=0 -sPROXY_TO_PTHREAD -pthread")
 
target_link_libraries(main PUBLIC calc)
