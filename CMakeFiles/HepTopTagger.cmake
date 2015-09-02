cmake_minimum_required(VERSION 2.6.0 FATAL_ERROR)
project(HepTopTagger CXX)
message("Project: HepTopTagger")

include(CMakeFiles/CMakeConfig.cmake)
include(CMakeFiles/Findfastjet.cmake)
add_include_path(${fastjet_INCLUDE_DIRS})
add_libraries(${fastjet_LIBRARIES})

add_include_path(${PROJECT_SOURCE_DIR})
create_executable(TopTagger example_toptagger.cc)
