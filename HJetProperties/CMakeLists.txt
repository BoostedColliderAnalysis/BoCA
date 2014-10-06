# Analysis Library
set(AnalysisSources HAnalysisJetProperties.cpp)
add_library(HAnalysisJetProperties SHARED ${AnalysisSources})
target_link_libraries(HAnalysisJetProperties HBranch HEvent)
set_target_properties(HAnalysisJetProperties PROPERTIES ${LibraryProperties})
install(TARGETS HAnalysisJetProperties DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

set(LinkLibraries
${LinkLibraries}
HAnalysisJetProperties
)

# Analysis Executable
add_executable(HJetProperties main.cpp)
target_link_libraries(HJetProperties ${LinkLibraries})
