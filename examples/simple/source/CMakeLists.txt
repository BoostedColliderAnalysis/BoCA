create_dictionary(BranchSimple Branch.cpp Branch.hh LinkDef.hh include)

set(CutFiles Tagger.cpp Observables.cpp)

create_library(Cut CutFiles)

create_executable(CutAnalysis MainCut.cpp)
