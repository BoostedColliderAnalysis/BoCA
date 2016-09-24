
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

set(compile_features cxx_return_type_deduction cxx_user_literals)

#define macros
macro(print_message text)
#   if(${CMAKE_BUILD_TYPE} MATCHES DEBUG)
    message(${text})
#   endif()
endmacro()

macro(add_include_path relative_directory)
  get_filename_component(absolute_directory ${relative_directory} ABSOLUTE)
  print_message("Include:      ${absolute_directory}")
  set(include_directories
    ${include_directories}
    ${absolute_directory}
    CACHE INTERNAL include_directories FORCE
  )
  include_directories(${ARGV1} ${include_directories})
endmacro()

macro(create_library name source)
  print_message("Library:      ${name} <- ${${source}} ${ARGV2}")
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
  target_compile_features(${name} PRIVATE ${compile_features})
  if(${CMAKE_BUILD_TYPE} MATCHES DEBUG AND iwyu_path)
    set_property(TARGET ${name} PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
  endif()
  install(TARGETS ${name} DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
  add_libraries(${name})
endmacro()

macro(create_executable name source)
  print_message("Executable:   ${name} <- ${source}")
  add_executable(${name} ${source})
  target_link_libraries(${name} ${link_libraries})
  target_compile_features(${name} PRIVATE ${compile_features})
  if(${CMAKE_BUILD_TYPE} MATCHES DEBUG AND iwyu_path)
    set_property(TARGET ${name} PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
  endif()
endmacro()

macro(create_dictionary name sources headers link_defs include_dir)
  print_message("Dictionary:   ${name} <- ${sources}, ${headers} & ${link_defs} | ${include_dir} ${ARGV5} ${ARGV6} ")
  set(link_defs_2 "")
  set(headers_2 "")
  if(${ARGC} GREATER 6)
    foreach(link_def ${link_defs})
      list(APPEND link_defs_2 ${CMAKE_CURRENT_LIST_DIR}/../../../${include_dir}/${ARGV5}/${ARGV6}/${link_def})
    endforeach()
    foreach(header ${headers})
      list(APPEND headers_2 ${CMAKE_CURRENT_LIST_DIR}/../../../${include_dir}/${ARGV5}/${ARGV6}/${header})
    endforeach()
  elseif(${ARGC} GREATER 5)
    foreach(link_def ${link_defs})
      list(APPEND link_defs_2  ${CMAKE_CURRENT_LIST_DIR}/../../${include_dir}/${ARGV5}/${link_def})
    endforeach()
    foreach(header ${headers})
      list(APPEND headers_2   ${CMAKE_CURRENT_LIST_DIR}/../../${include_dir}/${ARGV5}/${header})
    endforeach()
  else()
    foreach(link_def ${link_defs})
      list(APPEND link_defs_2 ${CMAKE_CURRENT_LIST_DIR}/../${include_dir}/${link_def})
    endforeach()
    foreach(header ${headers})
      list(APPEND headers_2 ${CMAKE_CURRENT_LIST_DIR}/../${include_dir}/${header})
    endforeach()
  endif()
  set(dictionary ${name}Dict)
  ROOT_GENERATE_DICTIONARY(${dictionary} ${headers_2} LINKDEF ${link_defs_2})
  set(Sources ${sources} ${dictionary}.cxx)
  create_library(${name} Sources "-w")
  SET(pcm "${CMAKE_CURRENT_BINARY_DIR}/${name}Dict_rdict.pcm")
  if(APPLE)
  add_custom_command(
    TARGET ${name}
    PRE_LINK
    COMMAND ${CMAKE_COMMAND} -E copy ${pcm} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    COMMENT "Copy: ${pcm} to ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
  )
  else()
  add_custom_command(
    TARGET ${name}
    PRE_LINK
    COMMAND ${CMAKE_COMMAND} -E copy ${pcm} ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
    COMMENT "Copy: ${pcm} to ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}"
  )
  endif()
endmacro()

macro(add_libraries source)
  print_message("Link Library: ${source}")
  set(link_libraries
    ${link_libraries}
    ${source}
    CACHE INTERNAL link_libraries FORCE
  )
endmacro()

macro(add_example folder)
  set(temp_directories ${include_directories})
  add_subdirectory(${folder})
  set(include_directories
    ${temp_directories}
    CACHE INTERNAL include_directories FORCE
  )
endmacro()
