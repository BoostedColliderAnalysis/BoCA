#
# Copyright (C) 2015 Jan Hajer
#

unset(link_libraries CACHE)
unset(include_directories CACHE)

# set library and excecutable destination
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
#set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})

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

macro(create_library library_name library_sources)
  message("Library:      ${library_name} <- ${${library_sources}} ${ARGV2}")
  if(${ARGC} GREATER 2)
    set_source_files_properties(${${library_sources}} PROPERTIES COMPILE_FLAGS ${ARGV2})
  endif(${ARGC} GREATER 2)
  if(APPLE)
    add_library(${library_name} STATIC ${${library_sources}})
  else()
    add_library(${library_name} SHARED ${${library_sources}})
  endif()
  target_link_libraries(${library_name} ${link_libraries})
  set_target_properties(${library_name} PROPERTIES ${library_properties})
  install(TARGETS ${library_name} DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
  add_libraries(${library_name})
endmacro()

macro(create_executable executable_name executable_source)
  message("Executable:   ${executable_name} <- ${executable_source}")
  add_executable(${executable_name} ${executable_source})
  target_link_libraries(${executable_name} ${link_libraries})
endmacro()

macro(create_dictionary dictionary_name dictionary_source link_def)
  message("Dictionary:   ${dictionary_name} <- ${dictionary_source} & ${link_def} | ${ARGV3}")
  set(dictionary_file ${dictionary_name}Dict.cpp)
  if(${ARGC} GREATER 3)
    set(path ../../source/${ARGV3}/${dictionary_source})
  else()
    set(path ../source/${dictionary_source})
  endif()
  ROOT_GENERATE_DICTIONARY("${path}" "${link_def}" "${dictionary_file}" "${include_directories}")
  create_library(${dictionary_name} dictionary_file "-w")
  add_custom_command(
    TARGET ${dictionary_name}
    PRE_LINK
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/${dictionary_name}Dict_rdict.pcm ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
    COMMENT "Copy: ${CMAKE_CURRENT_BINARY_DIR}/${dictionary_name}Dict_rdict.pcm to ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}"
  )
endmacro()

macro(add_libraries link_library_sources)
  message("Link Library: ${link_library_sources}")
  set(link_libraries
    ${link_libraries}
    ${link_library_sources}
    CACHE INTERNAL link_libraries FORCE
  )
endmacro()
