
set(AnalysisSources
HEventBottomTagger.cpp
HAnalysisBottomSumTagger.cpp
)
create_library(HAnalysisBottomSumTagger AnalysisSources)

create_executable(HBottomSumTagger main.cpp)
