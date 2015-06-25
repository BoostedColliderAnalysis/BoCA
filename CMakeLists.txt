<<<<<<< HEAD

# cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
# project(Analysis VERSION 0.1 LANGUAGES CXX)
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

=======
# cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
# project(Analysis VERSION 0.1 LANGUAGES CXX)
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
>>>>>>> 47d0e13470a268c5af9d2a511ab2ecdfa1c1410b
project(Analysis CXX)

# Load some basic macros which are needed later on
include(CMakeFiles/CMakeConfig.cmake)

# set c++ flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -Wextra -pedantic -Wpointer-arith -fPIC -O3")
#  -fno-stack-protector

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

<<<<<<< HEAD
=======
# Taggers
>>>>>>> 47d0e13470a268c5af9d2a511ab2ecdfa1c1410b
add_subdirectory(StandardModel)
add_subdirectory(PairTagger)
add_subdirectory(HBottomSumTagger)
add_subdirectory(HDiscriminator)
add_subdirectory(HiggsCpv)
add_subdirectory(HeavyHiggs)
add_subdirectory(TopPartner)
add_subdirectory(HJetProperties)
