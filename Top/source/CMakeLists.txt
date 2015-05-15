
HDictionary(HBranchTopTagger HBranchTopTagger.cpp ../include/HLinkDefTopTagger.hh)

set(HTopTaggerLib
AnalysisTopTagger.cpp
HTopLeptonTagger.cpp
HTopHadronTagger.cpp
)

HLibrary(AnalysisTopTagger "${HTopTaggerLib}")

HExecutable(TopAnalysis main.cpp)
