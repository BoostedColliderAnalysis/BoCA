#
# Copyright (C) 2015-2016 Jan Hajer
#

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(BoCA CXX)

include(CMakeFiles/CMakeConfig.cmake)
# find_package(Boost 1.43)
find_package(Boost 1.43 COMPONENTS system filesystem REQUIRED)
add_include_path(${Boost_INCLUDE_DIRS})
add_libraries(
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
)

# set build type to debug
if( NOT CMAKE_BUILD_TYPE )
set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE )
endif()

# set c++ flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -fPIC")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -Wall -Wextra -pedantic -Wpointer-arith -Wold-style-cast -Wno-unknown-pragmas -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

# use ccache if installed
find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)

# ROOT
include(CMakeFiles/FindROOT.cmake)
add_include_path(${ROOT_INCLUDE_DIR})
add_libraries("${ROOT_LIBRARIES}")
add_libraries(TMVA)
add_libraries(TreePlayer)
# add_libraries(MathMore)

# FastJet
include(CMakeFiles/Findfastjet.cmake)
# add_include_path(${fastjet_INCLUDE_DIRS})
add_libraries(${fastjet_LIBRARIES})
add_libraries(fastjettools)
add_libraries(Nsubjettiness)


# Doxygen
# if(CMAKE_BUILD_TYPE MATCHES "Release")
set(DO_DOXYGEN 0)
if(DO_DOXYGEN MATCHES 1)
include(CMakeFiles/UseDoxygen.cmake)
endif()

# Libraries
add_subdirectory(source)

add_subdirectory(StandardModel)
# add_subdirectory(HiggsCpv)
add_subdirectory(HeavyHiggs)
add_subdirectory(TopPartner)

