set(IncludeDirectory
${IncludeDirectory}
${PROJECT_SOURCE_DIR}/HTest
)
include_directories(${IncludeDirectory})

HDictionary(HBranchTest HBranchTest.cpp HBranchLinkDef.hh)

HLibrary(HAnalysisTest HAnalysisTest.cpp)

HExecutable(HTest main.cpp)
