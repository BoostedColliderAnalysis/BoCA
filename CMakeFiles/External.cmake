include(ExternalProject)

ExternalProject_Add(HMt2
URL http://particle.physics.ucdavis.edu/hefti/projects/lib/exe/fetch.php?media=mt2-1.01a.tar.gz
URL_MD5 dd2d167abb23f4146c05fd0962fba6dc
DOWNLOAD_NAME mt2-1.01a.tar.gz
SOURCE_DIR ${CMAKE_SOURCE_DIR}/External/Mt2
BINARY_DIR ${CMAKE_BINARY_DIR}/Mt2
PATCH_COMMAND
   ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/CMakeFiles/Mt2.cmake <SOURCE_DIR>/CMakeLists.txt
&& ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/CMakeFiles/CMakeConfig.cmake <SOURCE_DIR>/CMakeFiles/CMakeConfig.cmake
)

ExternalProject_Add(HWimpMass
URL http://particle.physics.ucdavis.edu/hefti/projects/lib/exe/fetch.php?media=wimpmass-1.00.tar.gz
URL_MD5 1068a6ab41bf52043dd42ce1cd88cbc2
DOWNLOAD_NAME wimpmass-1.00.tar.gz
SOURCE_DIR ${CMAKE_SOURCE_DIR}/External/WimpMass
BINARY_DIR ${CMAKE_BINARY_DIR}/WimpMass
PATCH_COMMAND
   ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/CMakeFiles/CMakeConfig.cmake <SOURCE_DIR>/CMakeFiles/CMakeConfig.cmake
&& ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/CMakeFiles/WimpMass.cmake <SOURCE_DIR>/CMakeLists.txt
&& ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/CMakeFiles/FindROOT.cmake <SOURCE_DIR>/CMakeFiles/FindROOT.cmake
&& ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/CMakeFiles/WimpMassSrc.cmake <SOURCE_DIR>/src/CMakeLists.txt
&& ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/CMakeFiles/WimpMassExamples.cmake <SOURCE_DIR>/examples/CMakeLists.txt
INSTALL_COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/External/WimpMass/examples/sqsq_pythia_events.lhe <BINARY_DIR>/bin/
)

ExternalProject_Get_Property(HWimpMass SOURCE_DIR)
HInclude(${SOURCE_DIR}/WIMPMASS)
HLinkLibraries(${CMAKE_BINARY_DIR}/WimpMass/lib/libWimpMass.so)

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
HInclude(${SOURCE_DIR})
