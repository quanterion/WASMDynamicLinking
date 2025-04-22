cmake_minimum_required(VERSION 3.22)

project(WASMDynamicLinking)

add_definitions(-std=c++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-g3 -Oz")


set(BUILD_DIR "../Build")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIR})

# TARGET_SUPPORTS_SHARED_LIBS is normally set to false by the emscripten platform configuration.
# Having the value set to false disables dynamic linking and replaces it with static linking.
# Emscripten supports dynamic linking, so we force enable it anyways
set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS TRUE)
# Shared is required for dynamic linking
add_library(calc SHARED ../Src/calc.cpp)

# overwrite the default suffix, otherwise it will generate a .a file and statically link it anyways
set_target_properties(calc PROPERTIES SUFFIX ".so")
# force shared memory on, this is required so the executable and library can share data
# Wno-experimental disables a warning related to pthreads
set_target_properties(calc PROPERTIES COMPILE_FLAGS "-sSHARED_MEMORY=1 -Wno-experimental")
# Set as side module, only 1 main module is allowed to exist at the same time, however a main module is always required
# Main module is set to false, which should usually also be the default. Just setting explictly to ensure it's not enabled by a global setting.
# Export all functions, this epxorts all functions, classes, structs and enums. You can use EMSCRIPTEN_KEEPALIVE instead, but this way of exporting works different from exporting for other platforms.
# -sPROXY_TO_PTHREAD -pthread is required to allow dlopen to load a library. Otherwise the library has to be auto loaded
set_target_properties(calc PROPERTIES LINK_FLAGS "-sSIDE_MODULE=1 -sMAIN_MODULE=0 -sEXPORT_ALL=1 -sPROXY_TO_PTHREAD -pthread")


add_executable(main ../Src/main.cpp)
# overwrite the default suffix, normally a .js and .wasm file are generated, this generates a test html file as well.
set_target_properties(main PROPERTIES SUFFIX ".html")
# set as main module, this is required in both compile and link flags to allow to find the symbols in a library
# force shared memory on, this is required so the executable and library can share data
set_target_properties(main PROPERTIES COMPILE_FLAGS "-sMAIN_MODULE=2 -sSHARED_MEMORY=1 -Wno-experimental")
# set as main module, this is required in both compile and link flags to allow to find the symbols in a library
# Disable auto loading, this is disabled to allow dynamically loading libraries, if you want to load the libraries while the page is loading, enable auto load
# -sPROXY_TO_PTHREAD -pthread is required to allow dlopen to load a library. Otherwise auto load has to be enabled
set_target_properties(main PROPERTIES LINK_FLAGS "-sMAIN_MODULE=2 -sAUTOLOAD_DYLIBS=0 -sPROXY_TO_PTHREAD -pthread")
 
target_link_libraries(main PUBLIC calc)
