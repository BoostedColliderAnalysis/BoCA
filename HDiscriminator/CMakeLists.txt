# Analysis Library
set(AnalysisSources HAnalysisDiscriminator.cpp)
add_library(HAnalysisDiscriminator SHARED ${AnalysisSources})
target_link_libraries(HAnalysisDiscriminator HBranch HEvent)
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
target_link_libraries(HMvaDiscriminator HMva)
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