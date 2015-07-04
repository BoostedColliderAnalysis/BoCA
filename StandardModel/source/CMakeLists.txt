set(TaggerLibraries
AnalysisTagger.cpp
AnalysisTopTagger.cpp
AnalysisHiggsTagger.cpp
AnalysisZTagger.cpp
AnalysisWTagger.cpp
AnalysisBottomTagger.cpp
)

HLibrary(AnalysisTagger TaggerLibraries)

HExecutable(TopAnalysis MainTop.cpp)
HExecutable(HiggsAnalysis MainHiggs.cpp)
HExecutable(ZAnalysis MainZ.cpp)
HExecutable(WAnalysis MainW.cpp)
HExecutable(BottomAnalysis MainBottom.cpp)

