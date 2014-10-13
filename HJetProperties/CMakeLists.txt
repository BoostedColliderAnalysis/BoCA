set(IncludeDirectory
${IncludeDirectory}
${PROJECT_SOURCE_DIR}/HJetProperties
)
include_directories(${IncludeDirectory})

# Branch dictionary
set(HBranchSources HJetPropertiesBranch.cpp)
set(HLinkDefHeader HJetPropertiesLinkDef.hh)
set(HDictionarySource HBranchDictJetProperties.cpp)
ROOT_GENERATE_DICTIONARY("${HBranchSources}" "${HLinkDefHeader}" "${HDictionarySource}" "${IncludeDirectory}")

# Branch library
set(HBranchSources ${HDictionarySource})
add_library(HBranchJetProperties SHARED ${HBranchSources})
target_link_libraries(HBranchJetProperties ${LinkLibraries})
set_target_properties(HBranchJetProperties PROPERTIES ${LibraryProperties})
install(TARGETS HBranchJetProperties DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

# Analysis Library
set(AnalysisSources HAnalysisJetProperties.cpp)
add_library(HAnalysisJetProperties SHARED ${AnalysisSources})
target_link_libraries(HAnalysisJetProperties HBranchJetProperties HEvent)
set_target_properties(HAnalysisJetProperties PROPERTIES ${LibraryProperties})
install(TARGETS HAnalysisJetProperties DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

set(LinkLibraries
${LinkLibraries}
HAnalysisJetProperties
)

# Analysis Executable
add_executable(HJetProperties main.cpp)
target_link_libraries(HJetProperties ${LinkLibraries})
