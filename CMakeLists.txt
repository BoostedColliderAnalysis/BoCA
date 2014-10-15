# Check if cmake has the required version
cmake_minimum_required(VERSION 2.6.0 FATAL_ERROR)

# Set name of our project to "Event".
# Has to be done after check of cmake version since this is a new feature
project(HAnalysis)

# set c++ flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wno-long-long -pedantic -g")

#C set build type to debug
set(CMAKE_BUILD_TYPE Debug)

# Load some basic macros which are needed later on
include(FindROOT.cmake)
include(Findfastjet.cmake)

# set path to dependencies
set(MadGraphDir "~/Development/MadGraph")
set(ExRootDir "${MadGraphDir}/ExRootAnalysis")
set(DelphesDir "${MadGraphDir}/Delphes")

# find external libraries
find_library(ExRootLibrary
    NAMES ExRootAnalysis
    HINTS "${ExRootDir}/lib"
)

find_library(DelphesLibrary
    NAMES Delphes
    HINTS "${DelphesDir}"
)

# set library and excecutable destination
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# set library versions
set(MajorVersion 0)
set(MinorVersion 0)
set(PatchVersion 0)
set(Version "${MajorVersion}.${MinorVersion}.${PatchVersion}")
set(LibraryProperties ${LibraryProperties}
    VERSION "${Version}"
    SOVERSION "${MajorVersion}"
    SUFFIX ".so"
)

# Libraries
set(IncludeDirectory ${IncludeDirectory}
${ROOT_INCLUDE_DIR}
${PROJECT_SOURCE_DIR}/include
${ExRootDir}
${DelphesDir}
)
include_directories(${IncludeDirectory})

set(LinkLibraries 
${ROOT_LIBRARIES}
${fastjet_LIBRARIES}
${DelphesLibrary}
${ExRootLibrary}
)

add_subdirectory(ExRootAnalysis)
add_subdirectory(classes)
add_subdirectory(source)

set(LinkLibraries
${LinkLibraries}
HObject
HBranch
HEvent
HAnalysis
HMva
)

add_subdirectory(HDiscriminator)
add_subdirectory(HHeavyHiggs)
add_subdirectory(HJetProperties)
add_subdirectory(HTest)
