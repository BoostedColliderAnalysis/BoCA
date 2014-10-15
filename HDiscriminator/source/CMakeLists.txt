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

set(LinkLibraries ${LinkLibraries} HBranchDiscriminator)

# Jet Library
HLibrary(HJetDiscriminator HJetDiscriminator.cpp)

# Jet Executable
add_executable(HJetDiscriminatorMain HJetDiscriminatorMain.cpp)
target_link_libraries(HJetDiscriminatorMain ${LinkLibraries})

# Analysis Library
HLibrary(HAnalysisDiscriminator HAnalysisDiscriminator.cpp)

# Analysis Executable
add_executable(HDiscriminator main.cpp)
target_link_libraries(HDiscriminator ${LinkLibraries})

# Mva Library
HLibrary(HMvaDiscriminator HMvaDiscriminator.cpp)

# Mva Executable

add_executable(HDiscriminatorFactory HFactory.cpp)
target_link_libraries(HDiscriminatorFactory ${LinkLibraries})

add_executable(HDiscriminatorReader HReader.cpp)
target_link_libraries(HDiscriminatorReader ${LinkLibraries})
