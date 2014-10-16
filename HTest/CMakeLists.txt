set(IncludeDirectory
${IncludeDirectory}
${PROJECT_SOURCE_DIR}/HTest
${PROJECT_SOURCE_DIR}/include
)
include_directories(${IncludeDirectory})

HDictionary(HBranchTest HBranchTest.cpp HBranchLinkDef.hh)

HLibrary(HAnalysisTest HAnalysisTest.cpp)

HExecutable(HTest main.cpp)
