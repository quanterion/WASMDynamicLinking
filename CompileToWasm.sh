#!/bin/bash

# Set as side module, need exactly 1 main module, the other modules should be side modules
# Export all functions, this epxorts all functions, classes, structs and enums. You can use EMSCRIPTEN_KEEPALIVE instead, but this way of exporting works different from exporting for other platforms.
# -sPROXY_TO_PTHREAD -pthread is required to allow dlopen to load a library. Otherwise the library has to be auto loaded
# force shared memory on, this is required so the executable and library can share data
# Wno-experimental disables a warning related to pthreads
emcc -sSIDE_MODULE=1 -sMAIN_MODULE=0 -s EXPORT_ALL=1 -sPROXY_TO_PTHREAD -pthread -sSHARED_MEMORY=1 -Wno-experimental -g -o Build/libcalc.so Src/calc.cpp

# set as main module, this is required to allow to the linker to find the symbols in a library
# Disable auto loading, this is disabled to allow dynamically loading libraries, if you want to load the libraries while the page is loading, enable auto load
# force shared memory on, this is required so the executable and library can share data
# Wno-experimental disables a warning related to pthreads
emcc -sMAIN_MODULE=2 -sAUTOLOAD_DYLIBS=0 -sPROXY_TO_PTHREAD -pthread -sSHARED_MEMORY=1 -Wno-experimental -g -o Build/main.html Build/libcalc.so Src/main.cpp