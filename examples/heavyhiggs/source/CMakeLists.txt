
add_subdirectory(branch)
add_subdirectory(tagger)
add_subdirectory(analysis)

set(VarSources
CutVariables.cpp
)
create_library(HeavyHiggsVar VarSources)

create_executable(PairTagger MainPair.cpp)
create_executable(HeavyHiggsNeutral MainNeutral.cpp)
create_executable(HeavyHiggsCharged MainCharged.cpp)
create_executable(HeavyHiggsFusion MainFusion.cpp)
create_executable(HeavyHiggsNeutralFourTop MainNeutralFourTop.cpp)
create_executable(HeavyHiggsCut MainHeavyHiggsCut.cpp)
create_executable(HeavyHiggsCutNeutral MainCutNeutral.cpp)
# create_executable(HeavyHiggsPlot MainPlot.cpp)
