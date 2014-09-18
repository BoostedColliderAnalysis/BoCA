# Library
set(AnalysisSources ${HDictionarySource} HAnalysis.cpp)
add_library(HAnalysisHeavyHiggsParton SHARED ${AnalysisSources})
target_link_libraries(HAnalysisHeavyHiggsParton HBranch)

set(LinkLibraries
${LinkLibraries}
HAnalysisHeavyHiggsParton
)

# Executable
add_executable(HHeavyHiggsParton main.cpp)
target_link_libraries(HHeavyHiggsParton ${LinkLibraries})
