HDictionary(BottomBranch HBranchBTagger.cpp ../include/HLinkDefBTagger.hh)

set(
Btaggerlibs
BottomTaggerSimple.cpp
AnalysisBottomTagger.cpp
)

HLibrary(HAnalysisBTagger "${Btaggerlibs}")

HExecutable(BottomAnalysis main.cpp)
