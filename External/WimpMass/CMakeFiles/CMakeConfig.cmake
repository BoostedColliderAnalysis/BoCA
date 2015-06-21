# set build type to debug
# set(CMAKE_BUILD_TYPE Debug)

# set(CMAKE_INSTALL_PREFIX ~)
unset(LinkLibraries CACHE)
# set library and excecutable destination
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# set library versions
set(MajorVersion 0)
set(MinorVersion 1)
set(PatchVersion 0)
set(Version ${MajorVersion}.${MinorVersion}.${PatchVersion})
set(LibraryProperties
  ${LibraryProperties}
  VERSION ${Version}
  SOVERSION ${MajorVersion}
  SUFFIX .so
  LINKER_LANGUAGE CXX
)

#define macros
macro(HInclude include_directory)
  message("Include:      ${include_directory}")
  set(IncludeDirectory
    ${IncludeDirectory}
    ${include_directory}
    CACHE INTERNAL IncludeDirectory FORCE
  )
  include_directories(${ARGV1} ${IncludeDirectory})
endmacro(HInclude)

macro(HLibrary library_name library_source)
  message("Library:      ${library_name} <- ${${library_source}} ${ARGV2}")
  add_library(${library_name} SHARED ${${library_source}})
  target_link_libraries(${library_name} ${LinkLibraries})
  set_target_properties(${library_name} PROPERTIES ${LibraryProperties})
  install(TARGETS ${library_name} DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
  HLinkLibraries(${library_name})
#   HLinkLibraries(${ARGV2})
endmacro(HLibrary)

macro(HExecutable executable_name executable_source)
  message("Executable:   ${executable_name} <- ${executable_source}")
  add_executable(${executable_name} ${executable_source})
  target_link_libraries(${executable_name} ${LinkLibraries})
endmacro(HExecutable)

macro(HDictionary dictionary_name dictionary_source link_def)
  message("Dictionary:   ${dictionary_name} <- ${dictionary_source} & ${link_def}")
  set(HDictionary ${dictionary_name}Dict.cpp)
  ROOT_GENERATE_DICTIONARY("${dictionary_source}" "${link_def}" "${HDictionary}" "${IncludeDirectory}")
  HLibrary(${dictionary_name} HDictionary ${ARGV3})
endmacro(HDictionary)

macro(HLinkLibraries link_library_source)
  message("Link Library: ${link_library_source}")
  set(LinkLibraries
  ${LinkLibraries}
  ${link_library_source}
  CACHE INTERNAL LinkLibraries FORCE
)
endmacro(HLinkLibraries)
