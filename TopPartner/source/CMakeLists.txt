create_dictionary(BranchTopPartner BranchesTopPartner.cpp ../include/LinkDefTopPartner.hh)

set(AnalysisSources
TopPartnerHadronicTagger.cpp
TopPartnerLeptonicTagger.cpp
HiggsPairTagger.cpp
TopPartnerPairTagger.cpp
TopPartnerHiggsPairTagger.cpp
TopPartnerTopPairTagger.cpp
SignatureTagger.cpp
SignatureSingleTagger.cpp
Septet.cpp
Nonet.cpp
Decuplet.cpp
Quattuordecuplet.cpp
EventSingleTagger.cpp
EventPairTagger.cpp
EventEffectiveTagger.cpp
)
create_library(AnalysisTopPartner AnalysisSources)

create_executable(TopPartnerSingle MainSingle.cpp)
create_executable(TopPartnerPair MainPair.cpp)
create_executable(TopPartnerEffective MainEffective.cpp)
