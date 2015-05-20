cmake_minimum_required(VERSION 2.6.0 FATAL_ERROR)

project(Analysis)
cmake_policy(SET CMP0038 OLD)

# Load some basic macros which are needed later on
include(CMakeFiles/CMakeConfig.cmake)

# ROOT
include(CMakeFiles/FindROOT.cmake)
HInclude(${ROOT_INCLUDE_DIR})
HLinkLibraries(${ROOT_LIBRARIES})
HLinkLibraries(TMVA)

# FastJet
include(CMakeFiles/Findfastjet.cmake)
HLinkLibraries(${fastjet_LIBRARIES})
HLinkLibraries(Nsubjettiness)

# Download external projects
include(CMakeFiles/External.cmake)

# MadGraph
include(CMakeFiles/FindMadGraph.cmake)

# libConfig
include(CMakeFiles/FindLibConfig.cmake)
HLinkLibraries(${LIBCONFIGPP_LIBRARIES})

# Doxygen
# include(CMakeFiles/UseDoxygen.cmake)

# Library
add_subdirectory(source)

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
