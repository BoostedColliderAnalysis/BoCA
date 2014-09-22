# Library
set(AnalysisSources 
HAnalysisHeavyHiggsDelphes.cpp 
HAnalysisHeavyHiggsParton.cpp 
HAnalysisHeavyHiggsPgs.cpp)
add_library(HAnalysisHeavyHiggs SHARED ${AnalysisSources})
target_link_libraries(HAnalysisHeavyHiggs HBranch HEvent)
set_target_properties(HAnalysisHeavyHiggs PROPERTIES ${LibraryProperties})
install(TARGETS HAnalysisHeavyHiggs DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

set(LinkLibraries
${LinkLibraries}
HAnalysisHeavyHiggs
)

# Executable
add_executable(HHeavyHiggsDelphes MainDelphes.cpp)
target_link_libraries(HHeavyHiggsDelphes ${LinkLibraries})

add_executable(HHeavyHiggsParton MainParton.cpp)
target_link_libraries(HHeavyHiggsParton ${LinkLibraries})

add_executable(HHeavyHiggsPgs MainPgs.cpp)
target_link_libraries(HHeavyHiggsPgs ${LinkLibraries})
