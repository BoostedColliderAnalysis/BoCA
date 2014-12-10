cmake_minimum_required(VERSION 2.6.0 FATAL_ERROR)

project(Mt2 CXX) 











set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Woverloaded-virtual -fno-stack-protector ")
# -Wcast-qual
# -fno-stack-protector

#C set build type to debug
set(CMAKE_BUILD_TYPE Debug)

# Load some basic macros which are needed later on
# include(CMakeFiles/FindROOT.cmake)
# include(CMakeFiles/Findfastjet.cmake)


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
  LINKER_LANGUAGE CXX
)

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


macro(HExecutable HName HSource)
  add_executable(${HName} ${HSource})
  target_link_libraries(${HName} ${LinkLibraries})
endmacro(HExecutable)

set(Directory
  ${ROOT_INCLUDE_DIR}
)
HInclude("${Directory}" SYSTEM)

# set(LinkLibraries
#   ${ROOT_LIBRARIES}
#   ${fastjet_LIBRARIES}
# )














set(Directory
${PROJECT_SOURCE_DIR}
)
HInclude("${Directory}")

set(Mt2Sources
mt2_bisect.cpp
)
HLibrary(Mt2 "${Mt2Sources}" PARENT_SCOPE)

HExecutable(Mt2Example example.cpp)