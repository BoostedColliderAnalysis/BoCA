cmake_minimum_required(VERSION 2.6.0 FATAL_ERROR)

project(HAnalysis)

include(CMakeFiles/CMakeConfig.cmake)

include(ExternalProject)

ExternalProject_Add(
HMt2
URL http://particle.physics.ucdavis.edu/hefti/projects/lib/exe/fetch.php?media=mt2-1.01a.tar.gz
URL_MD5 dd2d167abb23f4146c05fd0962fba6dc
DOWNLOAD_NAME mt2-1.01a.tar.gz
SOURCE_DIR ${CMAKE_SOURCE_DIR}/External/Mt2
BINARY_DIR ${CMAKE_BINARY_DIR}/Mt2
PATCH_COMMAND
${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/CMakeFiles/Mt2.cmake <SOURCE_DIR>/CMakeLists.txt
)

ExternalProject_Add(
HWimpMass
URL http://particle.physics.ucdavis.edu/hefti/projects/lib/exe/fetch.php?media=wimpmass-1.00.tar.gz
URL_MD5 1068a6ab41bf52043dd42ce1cd88cbc2
DOWNLOAD_NAME wimpmass-1.00.tar.gz
SOURCE_DIR ${CMAKE_SOURCE_DIR}/External/WimpMass
BINARY_DIR ${CMAKE_BINARY_DIR}/WimpMass
PATCH_COMMAND
${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/CMakeFiles/WimpMass.cmake <SOURCE_DIR>/CMakeLists.txt
&& ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/CMakeFiles/FindROOT.cmake <SOURCE_DIR>/CMakeFiles/FindROOT.cmake
&& ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/CMakeFiles/Findfastjet.cmake <SOURCE_DIR>/CMakeFiles/Findfastjet.cmake
&& ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/CMakeFiles/CMakeConfig.cmake <SOURCE_DIR>/CMakeFiles/CMakeConfig.txt
&& ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/CMakeFiles/WimpMassSrc.cmake <SOURCE_DIR>/src/CMakeLists.txt
&& ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/CMakeFiles/WimpMassExamples.cmake <SOURCE_DIR>/examples/CMakeLists.txt
INSTALL_COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/External/WimpMass/examples/sqsq_pythia_events.lhe <BINARY_DIR>/bin/
)

ExternalProject_Get_Property(HWimpMass install_dir)
include_directories(${install_dir}/include)
# add_dependencies(project_b_exe HWimpMass)
# target_link_libraries(project_b_exe ${install_dir}/lib/alib.lib)

ExternalProject_Add(
HepTopTagger
URL
http://www.thphys.uni-heidelberg.de/~plehn/includes/heptoptagger/heptop_v1.0.tar.gz
URL_MD5 a92b1eaa8b009d32a3f5cc34b627d4d2
SOURCE_DIR  ${CMAKE_SOURCE_DIR}/External/HepTopTagger
BINARY_DIR ${CMAKE_BINARY_DIR}/HepTopTagger
PATCH_COMMAND
${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/CMakeFiles/HepTopTagger.cmake <SOURCE_DIR>/CMakeLists.txt
&& ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/CMakeFiles/FindROOT.cmake <SOURCE_DIR>/CMakeFiles/FindROOT.cmake
&& ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/CMakeFiles/Findfastjet.cmake <SOURCE_DIR>/CMakeFiles/Findfastjet.cmake
&& ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/CMakeFiles/CMakeConfig.cmake <SOURCE_DIR>/CMakeFiles/CMakeConfig.cmake
&& patch <SOURCE_DIR>/example_toptagger.cc < ${CMAKE_SOURCE_DIR}/CMakeFiles/TopTaggerPatch.diff
INSTALL_COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/External/HepTopTagger/sample_event.dat <BINARY_DIR>/bin/
)


ExternalProject_Get_Property(HepTopTagger install_dir)
include_directories(${install_dir}/include)

set(Directory
  External/WimpMass/WIMPMASS/
  External/HepTopTagger/
)
HInclude("${Directory}" SYSTEM)

find_library(
  WimpMassLibrary
  NAMES WimpMass
  HINTS ${CMAKE_BINARY_DIR}/WimpMass/lib
)
# add_dependencies(WimpMassLibrary WimpMass)

set(LinkLibraries
  ${LinkLibraries}
  ${WimpMassLibrary}
)

# Library
HInclude(${PROJECT_SOURCE_DIR}/include)
add_subdirectory(source)
add_dependencies(Multiplets WimpMass)
add_dependencies(HAnalysis HepTopTagger)

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

#  DOXYFILE_EXTRA_SOURCES - Additional source diretories/files for Doxygen to scan.
#       The Paths should be in double quotes and separated by space. e.g.:
#        "${CMAKE_CURRENT_BINARY_DIR}/foo.c" "${CMAKE_CURRENT_BINARY_DIR}/bar/"
#  DOXYFILE_LATEX_DIR - Directory relative to DOXYFILE_OUTPUT_DIR where
#       the Doxygen LaTeX output is stored. Defaults to "latex".
#  DOXYFILE_HTML_DIR - Directory relative to DOXYFILE_OUTPUT_DIR where
#       the Doxygen html output is stored. Defaults to "html".
#



#  include(UseDoxygen)
