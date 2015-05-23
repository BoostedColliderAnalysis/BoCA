HDictionary(HBranchHeavyHiggs HBranchHeavyHiggs.cpp ../include/HLinkDefHeavyHiggs.hh)

set(AnalysisSources
HAnalysisHeavyHiggsDelphes.cpp
HAnalysisHeavyHiggsParton.cpp
HAnalysisHeavyHiggsPgs.cpp
HAnalysisHeavyHiggsMva.cpp
HAnalysisHeavyHiggsTt.cpp
HAnalysisChargedHiggsMva.cpp
HAnalysisTau.cpp
HEventLeptonicTagger.cpp
HEventHadronicTagger.cpp
HEventSemiTagger.cpp
HChargedSignatureSemiTagger.cpp
HSignatureSemiTagger.cpp
HChargedEventSemiTagger.cpp
HChargedHadronicTagger.cpp
Octet62.cpp
Octet44.cpp
MultipletEvent.cpp
SextetEvent.cpp
HEventTtSemiTagger.cpp
)
HLibrary(HAnalysisHeavyHiggs "${AnalysisSources}")

HExecutable(HHeavyHiggsDelphes MainDelphes.cpp)
HExecutable(HHeavyHiggsParton MainParton.cpp)
HExecutable(HHeavyHiggsPgs MainPgs.cpp)
HExecutable(HHeavyHiggsMva MainMva.cpp)
HExecutable(HHeavyHiggsTt MainTt.cpp)
HExecutable(HHeavyHiggsCharged MainCharged.cpp)
HExecutable(HHeavyHiggsTau MainTau.cpp)

HLibrary(HMvaHeavyHiggs HMvaHeavyHiggs.cpp)

HExecutable(HHeavyHiggsFactory MainFactory.cpp)
HExecutable(HHeavyHiggsReader MainReader.cpp)
