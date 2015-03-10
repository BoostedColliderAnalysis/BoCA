
set(AnalysisSources
HEventBottomTagger.cpp
HAnalysisBottomSumTagger.cpp
)
HLibrary(HAnalysisBottomSumTagger "${AnalysisSources}")

HExecutable(HBottomSumTagger main.cpp)
