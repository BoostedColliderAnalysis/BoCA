# set c++ flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -Wextra -pedantic -Wpointer-arith -fno-stack-protector -O3 -fPIC")
# -Wcast-qual -Woverloaded-virtual
# -fno-stack-protector
# -g -rdynamic-Wshadow

# set build type to debug
set(CMAKE_BUILD_TYPE Debug)


SET(CMAKE_INSTALL_PREFIX ~)

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

macro(HDictionary HName HSource HLinkDef)
  set(HDictionary ${HName}Dict.cpp)
  ROOT_GENERATE_DICTIONARY("${HSource}" "${HLinkDef}" "${HDictionary}" "${IncludeDirectory}")
  HLibrary(${HName} ${HDictionary} ${ARGV3})
endmacro(HDictionary)
