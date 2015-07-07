set(TaggerLibraries
AnalysisStandardModel.cpp
AnalysisBottomTagger.cpp
AnalysisWTagger.cpp
AnalysisZTagger.cpp
AnalysisHiggsTagger.cpp
AnalysisBosonTagger.cpp
AnalysisTopTagger.cpp
)

HLibrary(AnalysisTagger TaggerLibraries)

HExecutable(BottomAnalysis MainBottom.cpp)
HExecutable(WAnalysis MainW.cpp)
HExecutable(ZAnalysis MainZ.cpp)
HExecutable(HiggsAnalysis MainHiggs.cpp)
HExecutable(BosonAnalysis MainBoson.cpp)
HExecutable(TopAnalysis MainTop.cpp)
