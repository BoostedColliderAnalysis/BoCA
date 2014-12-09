HDictionary(HBranchHeavyHiggs HBranchHeavyHiggs.cpp ../include/HLinkDefHeavyHiggs.hh)

set(AnalysisSources
HAnalysisHeavyHiggsDelphes.cpp
HAnalysisHeavyHiggsParton.cpp
HAnalysisHeavyHiggsPgs.cpp
HAnalysisHeavyHiggsMva.cpp
HLeptonicEventTagger.cpp
HHadronicEventTagger.cpp
HHeavyHiggsEvent.cpp
)
HLibrary(HAnalysisHeavyHiggs "${AnalysisSources}")

HExecutable(HHeavyHiggsDelphes MainDelphes.cpp)
HExecutable(HHeavyHiggsParton MainParton.cpp)
HExecutable(HHeavyHiggsPgs MainPgs.cpp)
HExecutable(HHeavyHiggsMva MainMva.cpp)

HLibrary(HMvaHeavyHiggs HMvaHeavyHiggs.cpp)

HExecutable(HHeavyHiggsFactory MainFactory.cpp)
HExecutable(HHeavyHiggsReader MainReader.cpp)
