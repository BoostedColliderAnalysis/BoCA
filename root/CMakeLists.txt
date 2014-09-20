# generate dictionary
set(HBranchSources HBranch.cpp)
set(HLinkDefHeader HLinkDef.hh)
set(HDictionarySource ${CMAKE_CURRENT_BINARY_DIR}/HBranchDict.cpp) 
ROOT_GENERATE_DICTIONARY("${HBranchSources}" "${HLinkDefHeader}" "${HDictionarySource}" "${IncludeDirectory}")

# generate library
set(HBranchSources ${HDictionarySource})
add_library(HBranch SHARED ${HBranchSources})
target_link_libraries(HBranch ${LinkLibraries})
set_target_properties(HBranch PROPERTIES ${LibraryProperties})
install(TARGETS HBranch DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
