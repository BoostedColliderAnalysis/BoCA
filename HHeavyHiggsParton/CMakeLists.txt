# Library
set(AnalysisSources HAnalysisHeavyHiggsParton.cpp)
add_library(HAnalysisHeavyHiggsParton SHARED ${AnalysisSources})
target_link_libraries(HAnalysisHeavyHiggsParton HBranch HEvent)
set_target_properties(HAnalysisHeavyHiggsParton PROPERTIES ${LibraryProperties})
install(TARGETS HAnalysisHeavyHiggsParton DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

set(LinkLibraries
${LinkLibraries}
HAnalysisHeavyHiggsParton
)

# Executable
add_executable(HHeavyHiggsParton main.cpp)
target_link_libraries(HHeavyHiggsParton ${LinkLibraries})
