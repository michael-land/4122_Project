#!/bin/bash
cmake CMakeLists.txt
make
rm cmake_install.cmake CMakeCache.txt CpackConfig.make CPackSourceConfig.cmake CTestTestfile.cmake DartConfiguration.tcl
