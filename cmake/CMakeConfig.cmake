
#
# Copyright (C) 2015 Jan Hajer
#

unSET(link_libraries CACHE)
unSET(include_directories CACHE)

# set library and excecutable destination
SET(CMAKE_INSTALL_LIBDIR ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
#SET(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})
# SET(CMAKE_CXX_STANDARD_REQUIRED on)

if(APPLE)
  SET(CMAKE_MACOSX_RPATH ON)
endif()

# set library versions
SET(major_version 0)
SET(minor_version 3)
SET(patch_version 0)
SET(version ${major_version}.${minor_version}.${patch_version})
SET(library_properties
  ${library_properties}
  VERSION ${version}
  SOVERSION ${major_version}
  SUFFIX .so
  LINKER_LANGUAGE CXX
)

#define macros
macro(print_message text)
  if(${CMAKE_BUILD_TYPE} MATCHES DEBUG)
    message(${text})
  endif()
endmacro()

macro(add_include_path relative_directory)
  get_filename_component(absolute_directory ${relative_directory} ABSOLUTE)
  print_message("Include:      ${absolute_directory}")
  SET(include_directories
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
  target_compile_features(${name} PRIVATE cxx_decltype_auto cxx_user_literals)
  install(TARGETS ${name} DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
  add_libraries(${name})
endmacro()

macro(create_executable name source)
  print_message("Executable:   ${name} <- ${source}")
  add_executable(${name} ${source})
  target_link_libraries(${name} ${link_libraries})
  target_compile_features(${name} PRIVATE cxx_decltype_auto)
endmacro()

macro(create_dictionary name sources headers link_defs include_dir)
  print_message("Dictionary:   ${name} <- ${sources}, ${headers} & ${link_defs} | ${include_dir} ${ARGV5} ${ARGV6} ")
  SET(link_defs_2 "")
  SET(headers_2 "")
  if(${ARGC} GREATER 6)
    foreach(link_def ${link_defs})
      LIST(APPEND link_defs_2 ${CMAKE_CURRENT_LIST_DIR}/../../../${include_dir}/${ARGV5}/${ARGV6}/${link_def})
    endforeach()
    foreach(header ${headers})
      LIST(APPEND headers_2 ${CMAKE_CURRENT_LIST_DIR}/../../../${include_dir}/${ARGV5}/${ARGV6}/${header})
    endforeach()
  elseif(${ARGC} GREATER 5)
    foreach(link_def ${link_defs})
      LIST(APPEND link_defs_2  ${CMAKE_CURRENT_LIST_DIR}/../../${include_dir}/${ARGV5}/${link_def})
    endforeach()
    foreach(header ${headers})
      LIST(APPEND headers_2   ${CMAKE_CURRENT_LIST_DIR}/../../${include_dir}/${ARGV5}/${header})
    endforeach()
  else()
    foreach(link_def ${link_defs})
      LIST(APPEND link_defs_2 ${CMAKE_CURRENT_LIST_DIR}/../${include_dir}/${link_def})
    endforeach()
    foreach(header ${headers})
      LIST(APPEND headers_2 ${CMAKE_CURRENT_LIST_DIR}/../${include_dir}/${header})
    endforeach()
  endif()
  SET(dictionary ${name}Dict)
  ROOT_GENERATE_DICTIONARY(${dictionary} ${headers_2} LINKDEF ${link_defs_2})
  SET(Sources ${sources} ${dictionary}.cxx)
  create_library(${name} Sources "-w")
  SET(pcm "${CMAKE_CURRENT_BINARY_DIR}/${name}Dict_rdict.pcm")
  add_custom_command(
    TARGET ${name}
    PRE_LINK
    COMMAND ${CMAKE_COMMAND} -E copy ${pcm} ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
    COMMENT "Copy: ${pcm} to ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}"
  )
endmacro()

macro(add_libraries source)
  print_message("Link Library: ${source}")
  SET(link_libraries
    ${link_libraries}
    ${source}
    CACHE INTERNAL link_libraries FORCE
  )
endmacro()

macro(add_example folder)
  SET(temp_directories ${include_directories})
  add_subdirectory(${folder})
  SET(include_directories
    ${temp_directories}
    CACHE INTERNAL include_directories FORCE
  )
endmacro()
