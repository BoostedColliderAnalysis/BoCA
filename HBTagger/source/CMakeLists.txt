HDictionary(HBranchBTagger HBranchBTagger.cpp ../include/HLinkDefBTagger.hh)

set(
Btaggerlibs
BottomTaggerSimple.cpp
HAnalysisBTagger.cpp
)

HLibrary(HAnalysisBTagger "${Btaggerlibs}")

HExecutable(HBTagger main.cpp)

HLibrary(HMvaBTagger HMvaBTagger.cpp)

HExecutable(HFactoryBTagger HFactory.cpp)

HExecutable(HReaderBTagger HReader.cpp)
