cmake_minimum_required(VERSION 2.6.0 FATAL_ERROR)
project(Mt2 CXX)
message("Project: Mt2")

include(CMakeFiles/CMakeConfig.cmake)

HInclude(${PROJECT_SOURCE_DIR})
HLibrary(Mt2 mt2_bisect.cpp)
HExecutable(Mt2Example example.cpp)
