# Check if cmake has the required version
cmake_minimum_required(VERSION 2.6.0 FATAL_ERROR)

# Set name of our project to "Event".
# Has to be done after check of cmake version since this is a new feature
project(HAnalysis)

# set c++ flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Woverloaded-virtual -fno-stack-protector ")
# -Wcast-qual
# -fno-stack-protector

#C set build type to debug
set(CMAKE_BUILD_TYPE Debug)

# Load some basic macros which are needed later on
include(FindROOT.cmake)
include(Findfastjet.cmake)
# find_package(Doxygen)

# set path to dependencies
set(MadGraphDir ~/Development/MadGraph)
set(ExRootDir ${MadGraphDir}/ExRootAnalysis)
set(DelphesDir ${MadGraphDir}/Delphes)

# find external libraries
find_library(
  ExRootLibrary
  NAMES ExRootAnalysis
  HINTS ${ExRootDir}/lib
)

find_library(
  DelphesLibrary
  NAMES Delphes
  HINTS ${DelphesDir}
)

# set library and excecutable destination
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# set library versions
set(MajorVersion 0)
set(MinorVersion 0)
set(PatchVersion 0)
set(Version ${MajorVersion}.${MinorVersion}.${PatchVersion})
set(LibraryProperties
  ${LibraryProperties}
  VERSION ${Version}
  SOVERSION ${MajorVersion}
  SUFFIX .so
)

# set(IncludeDirectory ${IncludeDirectory} ${PROJECT_SOURCE_DIR}/include)

# define macros
macro(HInclude HDirectory)
set(IncludeDirectory
  ${IncludeDirectory}
  ${HDirectory}
)
#   list(APPEND ${IncludeDirectory} ${HDirectory})
  include_directories(${ARGV1} ${IncludeDirectory})
endmacro(HInclude)

macro(HLibrary HName HSource)
  add_library(${HName} SHARED ${HSource})
  target_link_libraries(${HName} ${LinkLibraries})
  set_target_properties(${HName} PROPERTIES ${LibraryProperties})
  install(TARGETS ${HName} DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
  set(LinkLibraries ${LinkLibraries} ${HName})
#   list(APPEND ${LinkLibraries} ${HName})
  set(LinkLibraries ${LinkLibraries} ${ARGV2})
endmacro(HLibrary)

macro(HDictionary HName HSource HLinkDef)
  set(HDictionary ${HName}Dict.cpp)
  ROOT_GENERATE_DICTIONARY("${HSource}" "${HLinkDef}" "${HDictionary}" "${IncludeDirectory}")
  HLibrary(${HName} ${HDictionary} ${ARGV3})
endmacro(HDictionary)

macro(HExecutable HName HSource)
  add_executable(${HName} ${HSource})
  target_link_libraries(${HName} ${LinkLibraries})
endmacro(HExecutable)

set(Directory
  ${ROOT_INCLUDE_DIR}
  ${ExRootDir}
  ${DelphesDir}
  ${PROJECT_SOURCE_DIR}/external/WIMPMASS/WIMPMASS
)
HInclude("${Directory}" SYSTEM)

# Library
HInclude(${PROJECT_SOURCE_DIR}/include)

set(LinkLibraries
  ${ROOT_LIBRARIES}
  TMVA
  ${fastjet_LIBRARIES}
  ${DelphesLibrary}
  ${ExRootLibrary}
  ${Topology}
)

add_subdirectory(external)
add_subdirectory(source)

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
