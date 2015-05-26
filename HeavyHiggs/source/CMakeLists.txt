HDictionary(BranchHeavyHiggs Branch.cpp ../include/LinkDefHeavyHiggs.hh)

set(AnalysisSources
Octet62.cpp
Octet44.cpp
SignatureNeutralTagger.cpp
SignatureChargedTagger.cpp
MultipletEvent.cpp
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
# HExecutable(HeavyHiggsFusion MainFusion.cpp)
