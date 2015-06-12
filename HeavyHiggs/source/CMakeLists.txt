HDictionary(BranchHeavyHiggs Branch.cpp ../include/LinkDefHeavyHiggs.hh)

set(AnalysisSources
Octet44.cpp
HeavyHiggsLeptonicTagger.cpp
HeavyHiggsSemiTagger.cpp
HeavyHiggsTauTagger.cpp
ChargedHiggsSemiTagger.cpp
ChargedHiggsLeptonicTagger.cpp
SignatureNeutralTagger.cpp
SignatureChargedTagger.cpp
EventNeutralTagger.cpp
EventChargedTagger.cpp
EventFusionTagger.cpp
AnalysisNeutral.cpp
AnalysisCharged.cpp
AnalysisFusion.cpp
)
HLibrary(AnalysisHeavyHiggs "${AnalysisSources}")

HExecutable(HeavyHiggsNeutral MainNeutral.cpp)
HExecutable(HeavyHiggsCharged MainCharged.cpp)
HExecutable(HeavyHiggsFusion MainFusion.cpp)
