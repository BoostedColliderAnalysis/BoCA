cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(Analysis CXX)

# Load some basic macros which are needed later on
include(CMakeFiles/CMakeConfig.cmake)

# set build type to debug
# if( NOT CMAKE_BUILD_TYPE )
set( CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE )
# endif()

# set c++ flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -g")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -Wall -Wextra -pedantic -Wpointer-arith -Wold-style-cast")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

# ROOT
include(CMakeFiles/FindROOT.cmake)
add_include_path(${ROOT_INCLUDE_DIR})
add_libraries(${ROOT_LIBRARIES})
add_libraries(TMVA)

# FastJet
include(CMakeFiles/Findfastjet.cmake)
add_libraries(${fastjet_LIBRARIES})
add_libraries(Nsubjettiness)

# Download external projects
include(CMakeFiles/External.cmake)

# MadGraph
include(CMakeFiles/FindMadGraph.cmake)

# libConfig
include(CMakeFiles/FindLibConfig.cmake)
add_libraries(${LIBCONFIGPP_LIBRARIES})

# Doxygen
# include(CMakeFiles/UseDoxygen.cmake)

# Libraries
add_subdirectory(source)

add_subdirectory(StandardModel)
add_subdirectory(PairTagger)
add_subdirectory(HBottomSumTagger)
add_subdirectory(HiggsCpv)
add_subdirectory(HeavyHiggs)
add_subdirectory(TopPartner)
