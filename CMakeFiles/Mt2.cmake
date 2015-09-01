#
# Copyright (C) 2015 Jan Hajer
#

cmake_minimum_required(VERSION 2.6.0 FATAL_ERROR)
project(Mt2 CXX)
message("Project: Mt2")

include(CMakeFiles/CMakeConfig.cmake)

add_include_path(${PROJECT_SOURCE_DIR})
set(Mt2Lib mt2_bisect.cpp)
create_library(Mt2 Mt2Lib)
create_executable(Mt2Example example.cpp)
