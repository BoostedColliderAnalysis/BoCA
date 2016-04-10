
create_dictionary(BranchesSm BranchesSm.cpp BranchesSm.hh LinkDefSm.hh)

set(sm_tagger_sources
TauTagger.cpp
BottomTagger.cpp
BosonTagger.cpp
WHadronicTagger.cpp
WLeptonicTagger.cpp
ZHadronicTagger.cpp
HiggsTagger.cpp
TopHadronicTagger.cpp
TopLeptonicTagger.cpp
TruthLevel.cpp
# TruthVariables.cpp
)
create_library(SmTagger sm_tagger_sources)

set(TaggerLibraries
AnalysisStandardModel.cpp
AnalysisBottom.cpp
)
create_library(AnalysisTagger TaggerLibraries)


set(hep_tagger_source
TopHadronicHep.cpp
TopHadronicHep2.cpp
)
create_library(HepTagger hep_tagger_source)

create_executable(BottomAnalysis MainBottom.cpp)
create_executable(WAnalysis MainW.cpp)
create_executable(ZAnalysis MainZ.cpp)
create_executable(HiggsAnalysis MainHiggs.cpp)
create_executable(BosonAnalysis MainBoson.cpp)
create_executable(TopAnalysis MainTop.cpp)
create_executable(TruthAnalysis MainTruth.cpp)

