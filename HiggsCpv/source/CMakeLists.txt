create_dictionary(BranchesHiggsCpv BranchesHiggsCpv.cpp ../include/LinkDefHiggsCpv.hh)

set(LibrarySources
TopSemiPairTagger.cpp
TopLeptonicPairTagger.cpp
SignatureTagger.cpp
SignatureTTagger.cpp
SignatureLeptonTagger.cpp
SignatureLeptonTTagger.cpp
EventTagger.cpp
EventTTagger.cpp
EventLeptonTTagger.cpp
)
create_library(HiggsCpvTagger LibrarySources)

create_executable(HiggsCpv ./main.cpp)
