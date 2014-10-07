# Analysis Library
set(AnalysisSources HAnalysisTest.cpp)
add_library(HAnalysisTest SHARED ${AnalysisSources})
target_link_libraries(HAnalysisTest HBranch HEvent)
set_target_properties(HAnalysisTest PROPERTIES ${LibraryProperties})
install(TARGETS HAnalysisTest DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

set(LinkLibraries
${LinkLibraries}
HAnalysisTest
)

# Analysis Executable
add_executable(HTest main.cpp)
target_link_libraries(HTest ${LinkLibraries})
