#
# Copyright (C) 2015 Jan Hajer
#

cmake_minimum_required(VERSION 2.6.0 FATAL_ERROR)
project(Wimpmass CXX)
message("Project: WimpMass")

include(CMakeFiles/CMakeConfig.cmake)
include(CMakeFiles/FindROOT.cmake)
add_include_path(${ROOT_INCLUDE_DIR})
add_libraries(${ROOT_LIBRARIES})

add_include_path(${PROJECT_SOURCE_DIR}/WIMPMASS/)
add_subdirectory(src)
add_subdirectory(examples)
