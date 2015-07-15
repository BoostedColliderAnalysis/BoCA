create_dictionary(BranchTopPartner BranchesTopPartner.cpp ../include/LinkDefTopPartner.hh)

set(AnalysisSources
TopPartnerHadronicTagger.cpp
TopPartnerLeptonicTagger.cpp
HiggsPairTagger.cpp
TopPartnerPairTagger.cpp
TopPartnerHiggsPairTagger.cpp
SignatureTagger.cpp
SignatureSingleTagger.cpp
Septet.cpp
Nonet.cpp
Decuplet.cpp
Quattuordecuplet.cpp
EventTagger.cpp
EventSingleTagger.cpp
)
create_library(AnalysisTopPartner AnalysisSources)

create_executable(TopPartner main.cpp)
