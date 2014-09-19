# Analysis Library
set(AnalysisSources HAnalysis.cpp)
add_library(HAnalysisDiscriminator SHARED ${AnalysisSources})
target_link_libraries(HAnalysisDiscriminator HBranch HEvent)
set_target_properties(HAnalysisDiscriminator PROPERTIES ${LibraryProperties})
install(TARGETS HAnalysisDiscriminator DESTINATION ${LIBRARY_OUTPUT_DIRECTORY})

set(LinkLibraries
${LinkLibraries}
HAnalysisDiscriminator
)

# Analysis Executable
add_executable(HDiscriminator main.cpp)
target_link_libraries(HDiscriminator ${LinkLibraries})

# Mva Library
set(MvaSources HMva.cpp)
add_library(HMva SHARED ${MvaSources})
target_link_libraries(HMva HMvaBase)

set(LinkLibraries
${LinkLibraries}
HMva
)

# Mva Executable

add_executable(HDiscriminatorFactory HFactory.cpp)
target_link_libraries(HDiscriminatorFactory ${LinkLibraries})
set_target_properties(HDiscriminatorFactory PROPERTIES ${LibraryProperties})
install(TARGETS HDiscriminatorFactory DESTINATION ${LIBRARY_OUTPUT_DIRECTORY})

add_executable(HDiscriminatorReader HReader.cpp)
target_link_libraries(HDiscriminatorReader ${LinkLibraries})
set_target_properties(HDiscriminatorFactory PROPERTIES ${LibraryProperties})
install(TARGETS HDiscriminatorFactory DESTINATION ${LIBRARY_OUTPUT_DIRECTORY})