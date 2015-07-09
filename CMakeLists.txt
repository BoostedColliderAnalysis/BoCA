
# cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
# project(Analysis VERSION 0.1 LANGUAGES CXX)
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(Analysis CXX)

# Load some basic macros which are needed later on
include(CMakeFiles/CMakeConfig.cmake)


if( NOT CMAKE_BUILD_TYPE )
set( CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE )
endif()

# set c++ flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -Wall -Wextra -pedantic -Wpointer-arith")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

# target_compile_features(foo
# PUBLIC
# cxx_auto_type
# cxx_range_for
# PRIVATE
# cxx_variadic_templates
# )

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

add_subdirectory(StandardModel)
add_subdirectory(PairTagger)
add_subdirectory(HBottomSumTagger)
add_subdirectory(HDiscriminator)
add_subdirectory(HiggsCpv)
add_subdirectory(HeavyHiggs)
add_subdirectory(TopPartner)
add_subdirectory(HJetProperties)

