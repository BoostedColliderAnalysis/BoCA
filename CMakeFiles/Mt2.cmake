project(Mt2 CXX)

include(CMakeFiles/CMakeConfig.cmake)

HInclude(${PROJECT_SOURCE_DIR})
HLibrary(Mt2 mt2_bisect.cpp PARENT_SCOPE)
HExecutable(Mt2Example example.cpp)
