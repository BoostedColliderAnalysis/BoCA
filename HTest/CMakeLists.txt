set(IncludeDirectory
${IncludeDirectory}
${PROJECT_SOURCE_DIR}/HTest
)
include_directories(${IncludeDirectory})

# Branch dictionary
set(HBranchSources HBranchTest.cpp)
set(HLinkDefHeader HBranchLinkDef.hh)
set(HDictionarySource HBranchTestDict.cpp)
ROOT_GENERATE_DICTIONARY("${HBranchSources}" "${HLinkDefHeader}" "${HDictionarySource}" "${IncludeDirectory}")

# Branch library
set(HBranchSources ${HDictionarySource})
add_library(HBranchTest SHARED ${HBranchSources})
target_link_libraries(HBranchTest ${LinkLibraries})
set_target_properties(HBranchTest PROPERTIES ${LibraryProperties})
install(TARGETS HBranchTest DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

# Analysis Library
set(AnalysisSources HAnalysisTest.cpp)
add_library(HAnalysisTest SHARED ${AnalysisSources})
target_link_libraries(HAnalysisTest HBranchTest HEvent)
set_target_properties(HAnalysisTest PROPERTIES ${LibraryProperties})
install(TARGETS HAnalysisTest DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

set(LinkLibraries
${LinkLibraries}
HAnalysisTest
)

# Analysis Executable
add_executable(HTest main.cpp)
target_link_libraries(HTest ${LinkLibraries})
