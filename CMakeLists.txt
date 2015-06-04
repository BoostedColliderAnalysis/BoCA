cmake_minimum_required(VERSION 2.6.0 FATAL_ERROR)

project(Analysis)

# Load some basic macros which are needed later on
include(CMakeFiles/CMakeConfig.cmake)

# set c++ flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -Wextra -pedantic -Wpointer-arith -fPIC -O3")
#  -fno-stack-protector

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

# Libraries
add_subdirectory(source)

# Taggers
add_subdirectory(Bottom)
add_subdirectory(W)
add_subdirectory(Top)
add_subdirectory(HPairTagger)
add_subdirectory(HBottomSumTagger)
add_subdirectory(HDiscriminator)
add_subdirectory(HiggsCpv)
add_subdirectory(HeavyHiggs)
add_subdirectory(TopPartner)
add_subdirectory(HJetProperties)
