#
# Copyright (C) 2015-2016 Jan Hajer
#

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(BoCA CXX)

include(CMakeFiles/CMakeConfig.cmake)
find_package(Boost 1.43)
# find_package(Boost 1.43 COMPONENTS system filesystem REQUIRED)
add_include_path(${Boost_INCLUDE_DIRS})
# add_libraries(
#   ${Boost_FILESYSTEM_LIBRARY}
#   ${Boost_SYSTEM_LIBRARY}
# )

# set build type
if( NOT CMAKE_BUILD_TYPE )
set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE )
endif()

# set c++ flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -fPIC -D_GLIBCXX_USE_CXX11_ABI=0")
 set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fext-numeric-literals")
# -fext-numeric-literals
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -Wall -Wextra -pedantic -Wpointer-arith -Wold-style-cast -Wno-unknown-pragmas -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -Wall -Wextra -pedantic -Wpointer-arith -Wold-style-cast -Wno-unknown-pragmas")

# use ccache if installed
find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
  else ()
    message("CCache is not available.")
endif(CCACHE_FOUND)

# use gold linker if installed
option(USE_LD_GOLD "Use GNU gold linker" ON)
if (USE_LD_GOLD)
  execute_process(COMMAND ${CMAKE_CXX_COMPILER} -fuse-ld=gold -Wl,--version ERROR_QUIET OUTPUT_VARIABLE LD_VERSION)
  if ("${LD_VERSION}" MATCHES "GNU gold")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fuse-ld=gold")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fuse-ld=gold")
  else ()
    message("GNU gold linker is not available, using the default system linker.")
  endif ()
endif ()

# FastJet
include(CMakeFiles/Findfastjet.cmake)
add_libraries(${fastjet_LIBRARIES})
add_libraries(fastjettools)
add_libraries(Nsubjettiness)

# ROOT
find_package(ROOT REQUIRED COMPONENTS Core RIO TMVA Physics Hist Tree TreePlayer)
set(ROOT_CXX_FLAGS "${ROOT_CXX_FLAGS} ${CMAKE_CXX_FLAGS}")
include(${ROOT_USE_FILE})
add_libraries("${ROOT_LIBRARIES}")
add_libraries(TMVA)
add_libraries(MathMore)

# Doxygen
set(DO_DOXYGEN FALSE)
if(DO_DOXYGEN MATCHES TRUE)
include(CMakeFiles/UseDoxygen.cmake)
endif()

# Libraries
add_subdirectory(source)
add_subdirectory(examples)

