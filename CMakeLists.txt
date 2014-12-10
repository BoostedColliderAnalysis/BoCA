# Check if cmake has the required version
cmake_minimum_required(VERSION 2.6.0 FATAL_ERROR)

# Set name of our project to "Event".
# Has to be done after check of cmake version since this is a new feature
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
# && ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/CMakeFiles/FindROOT.cmake <SOURCE_DIR>/CMakeFiles/FindROOT.cmake
# && ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/CMakeFiles/Findfastjet.cmake <SOURCE_DIR>/CMakeFiles/Findfastjet.cmake
# && ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/CMakeFiles/CMakeConfig.cmake <SOURCE_DIR>/CMakeFiles/CMakeConfig.txt
# && ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/CMakeFiles/WimpMassSrc.cmake <SOURCE_DIR>/src/CMakeLists.txt
# && ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/CMakeFiles/WimpMassExamples.cmake <SOURCE_DIR>/examples/CMakeLists.txt
# INSTALL_COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/External/WimpMass/examples/sqsq_pythia_events.lhe <BINARY_DIR>/bin/
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

# ExternalProject_Get_Property(HWimpMass install_dir)
# include_directories(${install_dir}/include)
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

# find_library(
#   HepTopTaggerLibrary
#   NAMES HepTopTagger
#   HINTS ${CMAKE_BINARY_DIR}/HepTopTagger/lib
# )
set(LinkLibraries
  ${LinkLibraries}
  ${WimpMassLibrary}
)

# Library
HInclude(${PROJECT_SOURCE_DIR}/include)
add_subdirectory(source)
add_dependencies(HContainer WimpMass)
add_dependencies(HAnalysis HepTopTagger)

# Tagger
add_subdirectory(HBTagger)
# find_library(
#   BTaggerLibrary
#   NAMES HMvaBTagger
#   HINTS ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
# )
# set(LinkLibraries ${LinkLibraries} ${BTaggerLibrary})
add_subdirectory(HTopTagger)
add_subdirectory(HDiscriminator)

# Executables
add_subdirectory(HHiggsCpv)
add_subdirectory(HHeavyHiggs)
add_subdirectory(HJetProperties)
add_subdirectory(HTest)















# set(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" ON)
#
# IF(BUILD_DOCUMENTATION)
#
# MESSAGE(${CMAKE_CURRENT_SOURCE_DIR})
#
# FIND_PACKAGE(Doxygen)
#   IF(NOT DOXYGEN_FOUND)
#     MESSAGE(FATAL_ERROR
#       "Doxygen is needed to build the documentation.")
#   ENDIF()
#
#   SET( doxyfile_in          ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in     )
#   SET( doxyfile             ${PROJECT_BINARY_DIR}/Doxyfile              )
#   SET( doxy_html_index_file ${CMAKE_CURRENT_BINARY_DIR}/html/index.html )
#   SET( doxy_output_root     ${CMAKE_CURRENT_BINARY_DIR}                 ) # Pasted into Doxyfile.in
#   SET( doxy_input           ${CMAKE_CURRENT_SOURCE_DIR}                  ) # Pasted into Doxyfile.in
#   SET( doxy_extra_files     ${CMAKE_CURRENT_SOURCE_DIR}/mainpage.dox    ) # Pasted into Doxyfile.in
#
#   CONFIGURE_FILE( ${doxyfile_in} ${doxyfile} @ONLY )
#
#   ADD_CUSTOM_COMMAND( OUTPUT ${doxy_html_index_file}
#                       COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
#                       # The following should be ${doxyfile} only but it
#                       # will break the dependency.
#                       # The optimal solution would be creating a
#                       # custom_command for ${doxyfile} generation
#                       # but I still have to figure out how...
#                       MAIN_DEPENDENCY ${doxyfile} ${doxyfile_in}
#                       DEPENDS ${doxy_extra_files}
#                       COMMENT "Generating HTML documentation")
#
#   ADD_CUSTOM_TARGET( doc ALL DEPENDS ${doxy_html_index_file} )
#
#   INSTALL( DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION share/doc )
# ENDIF()
