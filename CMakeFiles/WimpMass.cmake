cmake_minimum_required(VERSION 2.6.0 FATAL_ERROR)
project(WIMPMASS CXX)
message("Project: WimpMass")

include(CMakeFiles/CMakeConfig.cmake)
include(CMakeFiles/FindROOT.cmake)
HInclude(${ROOT_INCLUDE_DIR})
HLinkLibraries(${ROOT_LIBRARIES})

HInclude(${PROJECT_SOURCE_DIR}/WIMPMASS/)
add_subdirectory(src)
add_subdirectory(examples)
