set(IncludeDirectory
${IncludeDirectory}
${PROJECT_SOURCE_DIR}/HHeavyHiggs/include
${PROJECT_SOURCE_DIR}/HHeavyHiggs/source
)
include_directories(${IncludeDirectory})

# Branch dictionary
set(HBranchSources HBranchHeavyHiggs.cpp)
set(HLinkDefHeader ../include/HLinkDefHeavyHiggs.hh)
set(HDictionarySource HBranchDictHeavyHiggs.cpp)
ROOT_GENERATE_DICTIONARY("${HBranchSources}" "${HLinkDefHeader}" "${HDictionarySource}" "${IncludeDirectory}")

# Branch library
set(HBranchSources ${HDictionarySource})
add_library(HBranchHeavyHiggs SHARED ${HBranchSources})
target_link_libraries(HBranchHeavyHiggs ${LinkLibraries})
set_target_properties(HBranchHeavyHiggs PROPERTIES ${LibraryProperties})
install(TARGETS HBranchHeavyHiggs DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

# Library
set(AnalysisSources
HAnalysisHeavyHiggsDelphes.cpp
HAnalysisHeavyHiggsParton.cpp
HAnalysisHeavyHiggsPgs.cpp)
add_library(HAnalysisHeavyHiggs SHARED ${AnalysisSources})
target_link_libraries(HAnalysisHeavyHiggs HBranchHeavyHiggs HEvent)
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

# Mva Library
set(MvaSources HMvaHeavyHiggs.cpp)
add_library(HMvaHeavyHiggs SHARED ${MvaSources})
target_link_libraries(HMvaHeavyHiggs HMva HBranchHeavyHiggs)
set_target_properties(HMvaHeavyHiggs PROPERTIES ${LibraryProperties})
install(TARGETS HMvaHeavyHiggs DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

set(LinkLibraries
${LinkLibraries}
HMvaHeavyHiggs
)

# Mva Executable

add_executable(HHeavyHiggsFactory MainFactory.cpp)
target_link_libraries(HHeavyHiggsFactory ${LinkLibraries})

add_executable(HHeavyHiggsReader MainReader.cpp)
target_link_libraries(HHeavyHiggsReader ${LinkLibraries})
