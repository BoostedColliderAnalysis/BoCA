#
# Copyright (C) 2015 Jan Hajer
#

include(ExternalProject)

ExternalProject_Add(HepTopTagger
URL http://www.thphys.uni-heidelberg.de/~plehn/includes/heptoptagger/heptop_v1.0.tar.gz
URL_MD5 a92b1eaa8b009d32a3f5cc34b627d4d2
SOURCE_DIR  ${CMAKE_SOURCE_DIR}/External/HepTopTagger
BINARY_DIR ${CMAKE_BINARY_DIR}/HepTopTagger
PATCH_COMMAND
   ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/CMakeFiles/CMakeConfig.cmake <SOURCE_DIR>/CMakeFiles/CMakeConfig.cmake
&& ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/CMakeFiles/HepTopTagger.cmake <SOURCE_DIR>/CMakeLists.txt
&& ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/CMakeFiles/Findfastjet.cmake <SOURCE_DIR>/CMakeFiles/Findfastjet.cmake
&& patch <SOURCE_DIR>/example_toptagger.cc < ${CMAKE_SOURCE_DIR}/CMakeFiles/TopTaggerPatch.diff
INSTALL_COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/External/HepTopTagger/sample_event.dat <BINARY_DIR>/bin/
)
ExternalProject_Get_Property(HepTopTagger SOURCE_DIR)
add_include_path(${SOURCE_DIR})
