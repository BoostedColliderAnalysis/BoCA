cmake_minimum_required(VERSION 2.6.0 FATAL_ERROR)

project(Analysis)

# Load some basic macros which are needed later on
include(CMakeFiles/CMakeConfig.cmake)
include(CMakeFiles/FindLibConfig.cmake)
include(CMakeFiles/FindROOT.cmake)
include(CMakeFiles/Findfastjet.cmake)
include(CMakeFiles/FindMadGraph.cmake)
include(CMakeFiles/External.cmake)

HInclude(${ROOT_INCLUDE_DIR} SYSTEM)

set(LinkLibraries
  ${LinkLibraries}
  ${LIBCONFIGPP_LIBRARIES}
  ${ROOT_LIBRARIES}
  TMVA
  ${fastjet_LIBRARIES}
)

find_library(
  WimpMassLibrary
  NAMES WimpMass
  HINTS ${CMAKE_BINARY_DIR}/WimpMass/lib
)

set(LinkLibraries
  ${LinkLibraries}
  ${WimpMassLibrary}
)

# Library
HInclude(${PROJECT_SOURCE_DIR}/include)
add_subdirectory(source)
add_dependencies(Multiplets WimpMass)
add_dependencies(Analysis HepTopTagger)

# Tagger
add_subdirectory(Bottom)
add_subdirectory(W)
add_subdirectory(Top)
add_subdirectory(HPairTagger)
add_subdirectory(HBottomSumTagger)
add_subdirectory(HDiscriminator)

# Executables
add_subdirectory(HHiggsCpv)
add_subdirectory(HHeavyHiggs)
add_subdirectory(HJetProperties)
add_subdirectory(HTest)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMakeFiles)
set(DOXYFILE_SOURCE_DIR ${CMAKE_SOURCE_DIR})
set(DOXYFILE_EXCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(DOXYFILE_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(PROJECT_VERSION ${Version})
set(DOXYFILE_GENERATE_LATEX NO)
set(DOXYFILE_LATEX OFF)

# DOXYFILE_EXTRA_SOURCES - Additional source diretories/files for Doxygen to scan. The Paths should be in double quotes and separated by space. e.g.: "${CMAKE_CURRENT_BINARY_DIR}/foo.c" "${CMAKE_CURRENT_BINARY_DIR}/bar/"
# DOXYFILE_LATEX_DIR - Directory relative to DOXYFILE_OUTPUT_DIR where the Doxygen LaTeX output is stored. Defaults to "latex".
# DOXYFILE_HTML_DIR - Directory relative to DOXYFILE_OUTPUT_DIR where the Doxygen html output is stored. Defaults to "html".

#  include(UseDoxygen)
