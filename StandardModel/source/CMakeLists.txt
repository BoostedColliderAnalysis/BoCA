set(TaggerLibraries
AnalysisStandardModel.cpp
AnalysisBottom.cpp
AnalysisW.cpp
AnalysisZ.cpp
AnalysisHiggs.cpp
AnalysisBoson.cpp
AnalysisTop.cpp
)

HLibrary(AnalysisTagger TaggerLibraries)

HExecutable(BottomAnalysis MainBottom.cpp)
HExecutable(WAnalysis MainW.cpp)
HExecutable(ZAnalysis MainZ.cpp)
HExecutable(HiggsAnalysis MainHiggs.cpp)
HExecutable(BosonAnalysis MainBoson.cpp)
HExecutable(TopAnalysis MainTop.cpp)
