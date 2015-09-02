#set(CMAKE_SKIP_RPATH OFF)

if(APPLE)
  set(CMAKE_MACOSX_RPATH ON)
endif()

unset(link_libraries CACHE)
unset(include_directories CACHE)

# set library and excecutable destination
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
#set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})



# use, i.e. don't skip the full RPATH for the build tree
#SET(CMAKE_SKIP_BUILD_RPATH  FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
#SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE) 

#SET(CMAKE_INSTALL_RPATH ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
#SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)


# the RPATH to be used when installing, but only if it's not a system directory
#LIST(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} isSystemDir)
#IF("${isSystemDir}" STREQUAL "-1")
#   SET(CMAKE_INSTALL_RPATH ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
#ENDIF("${isSystemDir}" STREQUAL "-1")



# set library versions
set(major_version 0)
set(minor_version 1)
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
endmacro(add_include_path)

macro(create_library library_name library_sources)
  message("Library:      ${library_name} <- ${${library_sources}} ${ARGV2}")
  if(${ARGC} GREATER 2)
    set_source_files_properties(${${library_sources}} PROPERTIES COMPILE_FLAGS ${ARGV2})
  endif(${ARGC} GREATER 2)
  add_library(${library_name} STATIC ${${library_sources}})
  #add_library(${library_name} SHARED ${${library_sources}})
  target_link_libraries(${library_name} ${link_libraries})
  set_target_properties(${library_name} PROPERTIES ${library_properties})
  #set_target_properties(${library_name} PROPERTIES INSTALL_RPATH "@loader_path/../lib")
  install(TARGETS ${library_name} DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
  add_libraries(${library_name})
#  install (TARGETS ${library_name} DESTINATION bin)
#  install (FILES ${library_s DESTINATION include)
endmacro(create_library)


macro(create_ext_library library_name library_sources)
  message("Library:      ${library_name} <- ${${library_sources}} ${ARGV2}")
  if(${ARGC} GREATER 2)
    set_source_files_properties(${${library_sources}} PROPERTIES COMPILE_FLAGS ${ARGV2})
  endif(${ARGC} GREATER 2)
  add_library(${library_name} SHARED ${${library_sources}})
  target_link_libraries(${library_name} ${link_libraries})
  set_target_properties(${library_name} PROPERTIES ${library_properties})
  install(TARGETS ${library_name} DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
  add_libraries(${library_name})
endmacro(create_ext_library)


macro(create_executable executable_name executable_source)
  message("Executable:   ${executable_name} <- ${executable_source}")
  add_executable(${executable_name} ${executable_source})
  target_link_libraries(${executable_name} ${link_libraries})
endmacro(create_executable)

macro(create_dictionary dictionary_name dictionary_source link_def)
  message("Dictionary:   ${dictionary_name} <- ${dictionary_source} & ${link_def}")
  set(dictionary_file ${dictionary_name}Dict.cpp)
  ROOT_GENERATE_DICTIONARY("../source/${dictionary_source}" "${link_def}" "${dictionary_file}" "${include_directories}")
  create_library(${dictionary_name} dictionary_file "-w")
endmacro(create_dictionary)

macro(add_libraries link_library_sources)
  message("Link Library: ${link_library_sources}")
  set(link_libraries
    ${link_libraries}
    ${link_library_sources}
    CACHE INTERNAL link_libraries FORCE
  )
endmacro(add_libraries)
