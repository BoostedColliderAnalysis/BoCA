HDictionary(HBranchHeavyHiggs HBranchHeavyHiggs.cpp ../include/HLinkDefHeavyHiggs.hh)

set(AnalysisSources
HAnalysisHeavyHiggsDelphes.cpp
HAnalysisHeavyHiggsParton.cpp
HAnalysisHeavyHiggsPgs.cpp
HAnalysisHeavyHiggsMva.cpp
HAnalysisChargedHiggsMva.cpp
HEventLeptonicTagger.cpp
HEventHadronicTagger.cpp
HEventSemiTagger.cpp
HChargedSemiTagger.cpp
HChargedSemi2Tagger.cpp
HChargedHadronicTagger.cpp
HOctet.cpp
HOctet44.cpp
)
HLibrary(HAnalysisHeavyHiggs "${AnalysisSources}")

HExecutable(HHeavyHiggsDelphes MainDelphes.cpp)
HExecutable(HHeavyHiggsParton MainParton.cpp)
HExecutable(HHeavyHiggsPgs MainPgs.cpp)
HExecutable(HHeavyHiggsMva MainMva.cpp)
HExecutable(HHeavyHiggsCharged MainCharged.cpp)

HLibrary(HMvaHeavyHiggs HMvaHeavyHiggs.cpp)

HExecutable(HHeavyHiggsFactory MainFactory.cpp)
HExecutable(HHeavyHiggsReader MainReader.cpp)
