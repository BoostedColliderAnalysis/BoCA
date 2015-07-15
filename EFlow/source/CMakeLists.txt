# HInclude(.)
# HInclude(${PROJECT_SOURCE_DIR}/EFlow/include)

set(PropLib EflowAnalysis.cpp)
HLibrary(EFlow PropLib)

HExecutable(EFlowAnalysis main.cpp)
