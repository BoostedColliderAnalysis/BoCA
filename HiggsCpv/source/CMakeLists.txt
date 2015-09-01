create_dictionary(BranchesHiggsCpv BranchesHiggsCpv.cpp ../include/LinkDefHiggsCpv.hh)

set(LibrarySources
TopSemiPairTagger.cpp
TopLeptonicPairTagger.cpp
SignatureTagger.cpp
SignatureTTagger.cpp
SignatureLeptonTagger.cpp
EventTagger.cpp
EventTTagger.cpp
)
create_library(HiggsCpvTagger LibrarySources)

create_executable(HiggsCpv ./main.cpp)
