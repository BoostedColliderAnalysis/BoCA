cmake_minimum_required(VERSION 2.6.0 FATAL_ERROR)
project(Mt2 CXX)
message("Project: Mt2")

include(CMakeFiles/CMakeConfig.cmake)

HInclude(${PROJECT_SOURCE_DIR})
set(Mt2Lib mt2_bisect.cpp)
HLibrary(Mt2 Mt2Lib)
HExecutable(Mt2Example example.cpp)
