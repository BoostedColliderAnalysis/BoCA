cmake_minimum_required(VERSION 2.6.0 FATAL_ERROR)
project(HepTopTagger CXX)
message("Project: HepTopTagger")

include(CMakeFiles/CMakeConfig.cmake)
include(CMakeFiles/Findfastjet.cmake)
HLinkLibraries(${fastjet_LIBRARIES})

HInclude(${PROJECT_SOURCE_DIR})
HExecutable(TopTagger example_toptagger.cc)
