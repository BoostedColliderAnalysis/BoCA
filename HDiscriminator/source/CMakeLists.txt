set(IncludeDirectory
${IncludeDirectory}
${PROJECT_SOURCE_DIR}/HDiscriminator/source
${PROJECT_SOURCE_DIR}/HDiscriminator/include
)
include_directories(${IncludeDirectory})

# Branch dictionary
set(HBranchSources HBranchDiscriminator.cpp)
set(HLinkDefHeader ../include/HDiscriminatorLinkDef.hh)
set(HDictionarySource HBranchDiscriminatorDict.cpp)
ROOT_GENERATE_DICTIONARY("${HBranchSources}" "${HLinkDefHeader}" "${HDictionarySource}" "${IncludeDirectory}")

# Branch library
set(HBranchSources ${HDictionarySource})
add_library(HBranchDiscriminator SHARED ${HBranchSources})
target_link_libraries(HBranchDiscriminator ${LinkLibraries})
set_target_properties(HBranchDiscriminator PROPERTIES ${LibraryProperties})
install(TARGETS HBranchDiscriminator DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

# Jet Library
set(JetSources HJetDiscriminator.cpp)
add_library(HJetDiscriminator SHARED ${JetSources})
target_link_libraries(HJetDiscriminator HBranchDiscriminator HEvent HBranch)
set_target_properties(HJetDiscriminator PROPERTIES ${LibraryProperties})
install(TARGETS HJetDiscriminator DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

set(LinkLibraries
${LinkLibraries}
HJetDiscriminator
)

# Jet Executable
add_executable(HJetDiscriminatorMain HJetDiscriminatorMain.cpp)
target_link_libraries(HJetDiscriminatorMain ${LinkLibraries})

# Analysis Library
set(AnalysisSources HAnalysisDiscriminator.cpp)
add_library(HAnalysisDiscriminator SHARED ${AnalysisSources})
target_link_libraries(HAnalysisDiscriminator HBranchDiscriminator HEvent HBranch)
set_target_properties(HAnalysisDiscriminator PROPERTIES ${LibraryProperties})
install(TARGETS HAnalysisDiscriminator DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

set(LinkLibraries
${LinkLibraries}
HAnalysisDiscriminator
)

# Analysis Executable
add_executable(HDiscriminator main.cpp)
target_link_libraries(HDiscriminator ${LinkLibraries})

# Mva Library
set(MvaSources HMvaDiscriminator.cpp)
add_library(HMvaDiscriminator SHARED ${MvaSources})
target_link_libraries(HMvaDiscriminator HMva HBranchDiscriminator)
set_target_properties(HMvaDiscriminator PROPERTIES ${LibraryProperties})
install(TARGETS HMvaDiscriminator DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

set(LinkLibraries
${LinkLibraries}
HMvaDiscriminator
)

# Mva Executable

add_executable(HDiscriminatorFactory HFactory.cpp)
target_link_libraries(HDiscriminatorFactory ${LinkLibraries})

add_executable(HDiscriminatorReader HReader.cpp)
target_link_libraries(HDiscriminatorReader ${LinkLibraries})
