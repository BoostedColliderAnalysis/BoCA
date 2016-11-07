#
# Copyright (C) 2015-2016 Jan Hajer
#

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(BoCA CXX)

find_program(iwyu_path NAMES include-what-you-use iwyu)
if(!iwyu_path)
  message("'Include what You Use' is not available.")
endif()

include(${CMAKE_SOURCE_DIR}/cmake/CMakeConfig.cmake)

# Testing
option(BUILD_TESTING "Build testing" OFF)
if(BUILD_TESTING)
  enable_testing()
  find_package(Boost 1.56 COMPONENTS unit_test_framework REQUIRED)
  add_libraries(${Boost_LIBRARIES})
else()
  find_package(Boost 1.56)
endif()
add_include_path(${Boost_INCLUDE_DIRS} SYSTEM)

# set build type
if( NOT CMAKE_BUILD_TYPE )
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE )
endif()

# set c++ flags
SET(CMAKE_C_FLAGS "-std=c11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -pedantic -Wold-style-cast -Wno-unknown-pragmas")
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fext-numeric-literals -D_GLIBCXX_USE_CXX11_ABI=0")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-language-extension-token")
endif()
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast")

option(PORTABLE "Create computer architecture independent code" OFF)
if(NOT PORTABLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -mtune=native")
endif()

# use ccache if installed
find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
else ()
  message("CCache is not available.")
endif()

# use gold linker if installed
option(USE_LD_GOLD "Use GNU gold linker" ON)
if (USE_LD_GOLD)
  execute_process(COMMAND ${CMAKE_CXX_COMPILER} -fuse-ld=gold -Wl,--version ERROR_QUIET OUTPUT_VARIABLE LD_VERSION)
  if ("${LD_VERSION}" MATCHES "GNU gold" AND "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fuse-ld=gold")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fuse-ld=gold")
  else ()
    message("GNU gold linker is not available, using the default system linker.")
  endif ()
endif ()

# FastJet
include(${CMAKE_SOURCE_DIR}/cmake/Findfastjet.cmake)
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
option(DO_DOXYGEN "Create Doxygen documentation" OFF)
if(DO_DOXYGEN)
  include(${CMAKE_SOURCE_DIR}/cmake/UseDoxygen.cmake)
  file(GLOB svg_files ${CMAKE_SOURCE_DIR}/doc/images/*.svg)
  configure_file(${svg_files} ${CMAKE_BINARY_DIR}/doc/ COPYONLY)
endif()

add_include_path(${PROJECT_SOURCE_DIR})

# external sources
add_subdirectory(external)

# BoCA sources
add_subdirectory(source)

# application examples
add_subdirectory(examples)

# tests
add_subdirectory(external/wimpmass/test)
add_subdirectory(test)
