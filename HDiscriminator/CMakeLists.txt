# Library
set(AnalysisSources ${HDictionarySource} HAnalysis.cpp)
add_library(HAnalysisDiscriminator SHARED ${AnalysisSources})
target_link_libraries(HAnalysisDiscriminator HBranch)

set(LinkLibraries
${LinkLibraries}
HAnalysisDiscriminator
)

# Executable
add_executable(HDiscriminator main.cpp)
target_link_libraries(HDiscriminator ${LinkLibraries})
