project(HepTopTagger CXX)

include(CMakeFiles/CMakeConfig.cmake)
include(CMakeFiles/Findfastjet.cmake)
set(LinkLibraries ${fastjet_LIBRARIES})

HInclude(${PROJECT_SOURCE_DIR})
HExecutable(TopTagger example_toptagger.cc)
