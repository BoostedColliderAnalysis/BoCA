# - Find ROOT instalation
# This module tries to find the ROOT installation on your system.
# It tries to find the root-config script which gives you all the needed information.
# If the system variable ROOTSYS is set this is straight forward.
# If not the module uses the pathes given in root_config_search_path.
# If you need an other path you should add this path to this varaible.
# The root-config script is then used to detect basically everything else.
# This module defines a number of key variables and macros.

# F.Uhlig@gsi.de(fairroot.gsi.de)
# Jan Hajer

message(STATUS "Looking for Root...")

set(root_config_search_path
    ${SIMPATH}/tools/root/bin
    $ENV{ROOTSYS}/bin
    /usr/bin
   )
set(definitions "")
set(too_old version FALSE)
set(config_executable config_executable-NOTFOUND)

find_program(config_executable
             NAMES root-config
             PATHS ${root_config_search_path}
             NO_DEFAULT_PATH
            )

if(${config_executable} MATCHES "config_executable-NOTFOUND")
  message(FATAL_ERROR
         "ROOT not installed in the searchpath and ROOTSYS is not set.
          Please set ROOTSYS or add the path to your ROOT installation in
          the Macro FindROOT.cmake in the subdirectory cmake/modules.")
else(${config_executable} MATCHES "config_executable-NOTFOUND")
  string(REGEX REPLACE "(^.*)/bin/root-config" "\\1" test ${config_executable})
  set(ENV{ROOTSYS} ${test})
  set(ROOTSYS ${test})
endif(${config_executable} MATCHES "config_executable-NOTFOUND")

if(config_executable)
  set(root_found FALSE)
  exec_program(${config_executable}
               ARGS "--version"
               OUTPUT_VARIABLE version)
  message(STATUS "Looking for Root... - found $ENV{ROOTSYS}/bin/root")
  message(STATUS "Looking for Root... - version ${version} ")

  # we need at least version 5.00/00
  if(NOT min_version)
    set(min_version "5.00/00")
  endif(NOT min_version)

  # now parse the parts of the user given version string into variables
  string(REGEX REPLACE "^([0-9]+)\\.[0-9][0-9]+\\/[0-9][0-9]+" "\\1" req_root_major_vers "${min_version}")
  string(REGEX REPLACE "^[0-9]+\\.([0-9][0-9])+\\/[0-9][0-9]+.*" "\\1" req_root_minor_vers "${min_version}")
  string(REGEX REPLACE "^[0-9]+\\.[0-9][0-9]+\\/([0-9][0-9]+)" "\\1" req_root_patch_vers "${min_version}")

  # and now the version string given by qmake
  string(REGEX REPLACE "^([0-9]+)\\.[0-9][0-9]+\\/[0-9][0-9]+.*" "\\1" found_root_major_vers "${version}")
  string(REGEX REPLACE "^[0-9]+\\.([0-9][0-9])+\\/[0-9][0-9]+.*" "\\1" found_root_minor_vers "${version}")
  string(REGEX REPLACE "^[0-9]+\\.[0-9][0-9]+\\/([0-9][0-9]+).*" "\\1" found_root_patch_vers "${version}")

  if(found_root_major_vers LESS 5)
    message(FATAL_ERROR "Invalid ROOT version \"${ROOTERSION}\", at least major version 4 is required, e.g. \"5.00/00\"")
  endif(found_root_major_vers LESS 5)

  # compute an overall version number which can be compared at once
  math(EXPR req_vers "${req_root_major_vers}*10000 + ${req_root_minor_vers}*100 + ${req_root_patch_vers}")
  math(EXPR found_vers "${found_root_major_vers}*10000 + ${found_root_minor_vers}*100 + ${found_root_patch_vers}")

  if(found_vers LESS req_vers)
    set(root_found FALSE)
    set(too_old version TRUE)
  else(found_vers LESS req_vers)
    set(root_found TRUE)
  endif(found_vers LESS req_vers)
endif(config_executable)

if(root_found)
  # ask root-config for the library dir
  # Set ROOT_LIBRARY_DIR

  exec_program(${config_executable}
               ARGS "--libdir"
               OUTPUT_VARIABLE ROOT_LIBRARY_DIR_TMP)

  if(EXISTS "${ROOT_LIBRARY_DIR_TMP}")
    set(ROOT_LIBRARY_DIR ${ROOT_LIBRARY_DIR_TMP})
  else(EXISTS "${ROOT_LIBRARY_DIR_TMP}")
    message("Warning: config_executable reported ${ROOT_LIBRARY_DIR_TMP} as library path,")
    message("Warning: but ${ROOT_LIBRARY_DIR_TMP} does NOT exist, ROOT must NOT be installed correctly.")
  endif(EXISTS "${ROOT_LIBRARY_DIR_TMP}")

  # ask root-config for the binary dir
  exec_program(${config_executable}
               ARGS "--bindir"
               OUTPUT_VARIABLE root_bins)
  set(ROOT_BINARY_DIR ${root_bins})

  # ask root-config for the include dir
  exec_program(
    ${config_executable}
    ARGS "--incdir"
    OUTPUT_VARIABLE root_headers
    )
  set(ROOT_INCLUDE_DIR ${root_headers})

  # ask root-config for the library varaibles
  exec_program(${config_executable}
    ARGS "--glibs"
    OUTPUT_VARIABLE root_flags)

  set(ROOT_LIBRARIES ${root_flags})

  # Make variables changeble to the advanced user
  mark_as_advanced(ROOT_LIBRARY_DIR ROOT_INCLUDE_DIR definitions)

  # Set ROOT_INCLUDES
  set(ROOT_INCLUDES ${ROOT_INCLUDE_DIR})

  set(LD_LIBRARY_PATH ${LD_LIBRARY_PATH} ${ROOT_LIBRARY_DIR})

  #######################################
  #
  #       Check the executables of ROOT
  #         (rootcint)
  #
  #######################################

  find_program(ROOT_CINT_EXECUTABLE
    NAMES rootcint
    PATHS ${ROOT_BINARY_DIR}
    NO_DEFAULT_PATH
   )
endif(root_found)

#
# Macros for building ROOT dictionary
#
macro(generate_dictionary infiles linkdef_file outfile include_dirs_in)
  foreach(include_dir_in ${include_dirs_in})
    set(include_dirs ${include_dirs} -I${include_dir_in})
  endforeach()

  string(REGEX REPLACE "^(.*)\\.(.*)$" "\\1.h" bla "${outfile}")
  set(outfiles ${outfile} ${bla})

  if(CMAKE_SYSTEM_NAME MATCHES Linux)
    add_custom_command(OUTPUT ${outfiles}
                       COMMAND LD_LIBRARY_PATH=${ROOT_LIBRARY_DIR}
                               ROOTSYS=${ROOTSYS} ${ROOT_CINT_EXECUTABLE}
                       ARGS -f ${outfile} -c -DHAVE_CONFIG_H ${include_dirs} ${infiles} ${linkdef_file}
                       DEPENDS ${infiles} ${linkdef_file})
  else()
    if(CMAKE_SYSTEM_NAME MATCHES Darwin)
      add_custom_command(OUTPUT ${outfiles}
                         COMMAND DYLD_LIBRARY_PATH=${ROOT_LIBRARY_DIR}
                                 ROOTSYS=${ROOTSYS} ${ROOT_CINT_EXECUTABLE}
                         ARGS -f ${outfile} -c -DHAVE_CONFIG_H ${include_dirs} ${infiles} ${linkdef_file}
                         DEPENDS ${infiles} ${linkdef_file})
    endif()
  endif()
endmacro(generate_dictionary)
