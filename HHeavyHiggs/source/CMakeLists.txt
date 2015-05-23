HDictionary(BranchHeavyHiggs Branch.cpp ../include/LinkDef.hh)

set(AnalysisSources
# HAnalysisHeavyHiggsDelphes.cpp
# HAnalysisHeavyHiggsParton.cpp
# HAnalysisHeavyHiggsPgs.cpp
HAnalysisHeavyHiggsMva.cpp
HAnalysisHeavyHiggsTt.cpp
HAnalysisChargedHiggsMva.cpp
# HAnalysisTau.cpp
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

HExecutable(HHeavyHiggsMva MainNeutral.cpp)
HExecutable(HHeavyHiggsCharged MainCharged.cpp)
HExecutable(HHeavyHiggsTt MainTt.cpp)
