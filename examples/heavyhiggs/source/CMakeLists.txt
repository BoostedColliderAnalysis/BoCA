
add_subdirectory(branch)
add_subdirectory(tagger)

set(AnalysisSources
AnalysisPair.cpp
AnalysisHeavyHiggs.cpp
CutVariables.cpp
)
create_library(AnalysisHeavyHiggs AnalysisSources)

create_executable(PairTagger MainPair.cpp)
create_executable(HeavyHiggsNeutral MainNeutral.cpp)
create_executable(HeavyHiggsCharged MainCharged.cpp)
create_executable(HeavyHiggsFusion MainFusion.cpp)
create_executable(HeavyHiggsNeutralFourTop MainNeutralFourTop.cpp)
create_executable(HeavyHiggsCut MainCut.cpp)
create_executable(HeavyHiggsCutNeutral MainCutNeutral.cpp)
# create_executable(HeavyHiggsPlot MainPlot.cpp)
