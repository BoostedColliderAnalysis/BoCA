#
# Copyright (C) 2015 Jan Hajer
#

unset(link_libraries CACHE)
unset(include_directories CACHE)

# set library and excecutable destination
set(CMAKE_INSTALL_LIBDIR ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
#set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})
# set(CMAKE_CXX_STANDARD_REQUIRED on)

if(APPLE)
  set(CMAKE_MACOSX_RPATH ON)
endif()

# set library versions
set(major_version 0)
set(minor_version 3)
set(patch_version 0)
set(version ${major_version}.${minor_version}.${patch_version})
set(library_properties
  ${library_properties}
  VERSION ${version}
  SOVERSION ${major_version}
  SUFFIX .so
  LINKER_LANGUAGE CXX
)

#define macros
macro(add_include_path relative_directory)
  get_filename_component(absolute_directory ${relative_directory} ABSOLUTE)
  message("Include:      ${absolute_directory}")
  set(include_directories
    ${include_directories}
    ${absolute_directory}
    CACHE INTERNAL include_directories FORCE
  )
  include_directories(${ARGV1} ${include_directories})
endmacro()

macro(create_library name source)
  message("Library:      ${name} <- ${${source}} ${ARGV2}")
  if(${ARGC} GREATER 2)
    set_source_files_properties(${${source}} PROPERTIES COMPILE_FLAGS ${ARGV2})
  endif(${ARGC} GREATER 2)
  if(APPLE)
    add_library(${name} STATIC ${${source}})
  else()
    add_library(${name} SHARED ${${source}})
  endif()
  target_link_libraries(${name} ${link_libraries})
  set_target_properties(${name} PROPERTIES ${library_properties})
  target_compile_features(${name} PRIVATE cxx_decltype_auto)
  install(TARGETS ${name} DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
  add_libraries(${name})
endmacro()

macro(create_executable name source)
  message("Executable:   ${name} <- ${source}")
  add_executable(${name} ${source})
  target_link_libraries(${name} ${link_libraries})
  target_compile_features(${name} PRIVATE cxx_decltype_auto)
endmacro()

macro(create_dictionary name source header link_def)
  message("Dictionary:   ${name} <- ${source}, ${header} & ${link_def} | ${ARGV4}")
  if(${ARGC} GREATER 4)
    set(link_def2 ../../include/${ARGV4}/${link_def})
    set(header2 ../../include/${ARGV4}/${header})
    include_directories(../../include/${ARGV4})
  else()
    set(header2 ../include/${header})
    set(link_def2 ../include/${link_def})
#     include_directories(../include/)
  endif()
  set(dictionary ${name}Dict)
  ROOT_GENERATE_DICTIONARY(${dictionary} ${header2} LINKDEF ${link_def2})
  set(Sources ${source} ${dictionary}.cxx)
  create_library(${name} Sources "-w")
  add_custom_command(
    TARGET ${name}
    PRE_LINK
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/${name}Dict_rdict.pcm ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
    COMMENT "Copy: ${CMAKE_CURRENT_BINARY_DIR}/${name}Dict_rdict.pcm to ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}"
  )
endmacro()

macro(add_libraries source)
  message("Link Library: ${source}")
  set(link_libraries
    ${link_libraries}
    ${source}
    CACHE INTERNAL link_libraries FORCE
  )
endmacro()
