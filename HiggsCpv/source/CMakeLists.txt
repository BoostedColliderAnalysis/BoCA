HDictionary(BranchesHiggsCpv BranchesHiggsCpv.cpp ../include/LinkDefHiggsCpv.hh)

set(LibrarySources
TopSemiPairTagger.cpp
TopLeptonicPairTagger.cpp
SignatureTagger.cpp
EventTagger.cpp
AnalysisHiggs.cpp
)
HLibrary(HiggsCpvTagger LibrarySources)

HExecutable(HiggsCpv ./main.cpp)
