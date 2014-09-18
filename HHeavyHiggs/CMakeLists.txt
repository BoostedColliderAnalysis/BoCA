# Library
set(AnalysisSources ${HDictionarySource} HAnalysis.cpp)
add_library(HAnalysisHeavyHiggs SHARED ${AnalysisSources})
target_link_libraries(HAnalysisHeavyHiggs HBranch)
set_target_properties(HAnalysisHeavyHiggs PROPERTIES ${LibraryProperties})
install(TARGETS HAnalysisHeavyHiggs DESTINATION ${LIBRARY_OUTPUT_DIRECTORY})

set(LinkLibraries
${LinkLibraries}
HAnalysisHeavyHiggs
)

# Executable
add_executable(HHeavyHiggs main.cpp)
target_link_libraries(HHeavyHiggs ${LinkLibraries})
