
HDictionary(HBranchTopTagger HBranchTopTagger.cpp ../include/HLinkDefTopTagger.hh)

set(HTopTaggerLib
HAnalysisTopTagger.cpp
HTopLeptonTagger.cpp
)

HLibrary(HAnalysisTopTagger "${HTopTaggerLib}")

HExecutable(HTopTaggerTest main.cpp)
