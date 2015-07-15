create_dictionary(BranchesHiggsCpv BranchesHiggsCpv.cpp ../include/LinkDefHiggsCpv.hh)

set(LibrarySources
TopSemiPairTagger.cpp
TopLeptonicPairTagger.cpp
SignatureTagger.cpp
EventTagger.cpp
AnalysisHiggsCpv.cpp
)
create_library(HiggsCpvTagger LibrarySources)

create_executable(HiggsCpv ./main.cpp)
