create_dictionary(BranchSimple Branch.cpp Branch.hh LinkDef.hh simple)

set(SimpleFiles Tagger.cpp Observables.cpp)

create_library(Simple SimpleFiles)

create_executable(SimpleAnalysis MainSimple.cpp)
