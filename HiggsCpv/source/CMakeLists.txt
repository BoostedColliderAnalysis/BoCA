create_dictionary(BranchesHiggsCpv BranchesHiggsCpv.cpp BranchesHiggsCpv.hh LinkDefHiggsCpv.hh)

set(LibrarySources
TopSemiPairTagger.cpp
TopLeptonicPairTagger.cpp
SignatureTagger.cpp
SignatureTTagger.cpp
SignatureLeptonTagger.cpp
SignatureLeptonTTagger.cpp
GlobalTagger.cpp
EventTTagger.cpp
EventLeptonTTagger.cpp
)
create_library(HiggsCpvTagger LibrarySources)

create_executable(HiggsCpv ./main.cpp)
