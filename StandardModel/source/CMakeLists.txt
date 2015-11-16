
create_dictionary(BranchesSm BranchesSm.cpp ../include/LinkDefSm.hh)

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
)
create_library(SmTagger sm_tagger_sources)

set(TaggerLibraries
AnalysisStandardModel.cpp
AnalysisBottom.cpp
)
create_library(AnalysisTagger TaggerLibraries)

create_executable(BottomAnalysis MainBottom.cpp)
create_executable(WAnalysis MainW.cpp)
create_executable(ZAnalysis MainZ.cpp)
create_executable(HiggsAnalysis MainHiggs.cpp)
create_executable(BosonAnalysis MainBoson.cpp)
create_executable(TopAnalysis MainTop.cpp)
