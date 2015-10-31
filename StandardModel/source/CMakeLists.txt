set(TaggerLibraries
AnalysisStandardModel.cpp
AnalysisBottom.cpp
)

create_library(AnalysisTagger TaggerLibraries)

create_executable(BottomAnalysis MainBottom.cpp)
# create_executable(WAnalysis MainW.cpp)
# create_executable(ZAnalysis MainZ.cpp)
# create_executable(HiggsAnalysis MainHiggs.cpp)
# create_executable(BosonAnalysis MainBoson.cpp)
# create_executable(TopAnalysis MainTop.cpp)
