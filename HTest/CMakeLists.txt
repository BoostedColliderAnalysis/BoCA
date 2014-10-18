HInclude(${PROJECT_SOURCE_DIR}/HTest)

HDictionary(HBranchTest HBranchTest.cpp HBranchLinkDef.hh)

HLibrary(HAnalysisTest HAnalysisTest.cpp)

HExecutable(HTest main.cpp)
