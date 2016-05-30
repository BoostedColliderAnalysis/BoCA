add_subdirectory(branch)
add_subdirectory(tagger)


set(TaggerLibraries
AnalysisTop.cpp
AnalysisStandardModel.cpp
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

