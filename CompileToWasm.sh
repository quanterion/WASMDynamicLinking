#!/bin/bash

emcc -sSIDE_MODULE=1 -sMAIN_MODULE=0 -s EXPORT_ALL=1 -sPROXY_TO_PTHREAD -pthread -sSHARED_MEMORY=1 -Wno-experimental -o Build/libcalc.so Src/calc.cpp
emcc -sMAIN_MODULE=2 -sAUTOLOAD_DYLIBS=0 -sPROXY_TO_PTHREAD -pthread -sSHARED_MEMORY=1 -Wno-experimental -o Build/main.html Build/libcalc.so Src/main.cpp