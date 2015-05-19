project(WIMPMASS)

include(CMakeFiles/CMakeConfig.cmake)

include(CMakeFiles/FindROOT.cmake)
HInclude(${ROOT_INCLUDE_DIR})
set(LinkLibraries ${ROOT_LIBRARIES})

HInclude(${PROJECT_SOURCE_DIR}/WIMPMASS/)
add_subdirectory(src)
add_subdirectory(examples)
